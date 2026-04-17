#include "server.h"

#define SERVER_LISTEN_PORT 9999

Server::Server(QObject* parent) : QObject(parent) {
  // 1.创建 TCP 服务器
  m_server = new QTcpServer(this);
  m_clentSocketList = new QList<QTcpSocket*>();

  // 2.连接信号 处理新连接
  connect(m_server, &QTcpServer::newConnection, this, &Server::onNewConnection);

  // 3.开始监听 9999 端口
  if(m_server->listen(QHostAddress::Any, SERVER_LISTEN_PORT)){
    qDebug() << "服务端已启动，监听端口: " << SERVER_LISTEN_PORT;
  } else {
    qWarning() << "服务端启动失败: " << m_server->errorString();
  }
}


void Server::onNewConnection() {
  // 获取新连接
  QTcpSocket *clientSocket = m_server->nextPendingConnection();
  qDebug() << "客户端已连接: " << clientSocket->peerAddress().toString();

  // 分配ID，保存到列表和MAP
  int id = m_nextId++;
  m_clentSocketList->append(clientSocket);
  m_clientMap[clientSocket] = id;
  m_clientNameMap[clientSocket] = QString("用户%1").arg(id);


  // 有数据时触发 onReadyRead
  connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
  // 断开时打印日志
  connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onDisconnected);
}

void Server::onReadyRead() {
  // 读取全部数据
  QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
  if(!socket) return;

  QByteArray data = socket->readAll();
  QString msg = QString::fromUtf8(data).trimmed();
  QString name = m_clientNameMap[socket];

  qDebug() << "收到来自" << name << "的消息:" << msg;

  // 返回同样的数据
  socket->write(data);
  qDebug() << "return: " << data;
}

void Server::onDisconnected() {
  QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
  if(!socket) return;

  QString name = m_clientNameMap[socket];
  qDebug() << name << "断开连接";

  // 从列表中移除
  m_clentSocketList->removeOne(socket);
  m_clientMap.remove(socket);
  m_clientNameMap.remove(socket);

  socket->deleteLater();
}
