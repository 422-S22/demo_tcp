#include "server.h"

#define SERVER_LISTEN_PORT 9999

Server::Server(QObject* parent) : QObject(parent) {
  // 1.创建 TCP 服务器
  m_server = new QTcpServer(this);

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
  m_clientSocket = m_server->nextPendingConnection();
  qDebug() << "客户端已连接: " << m_clientSocket->peerAddress().toString();

  // 有数据时触发 onReadyRead
  connect(m_clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);

  // 断开时打印日志
  connect(m_clientSocket, &QTcpSocket::disconnected, [this](){
    qDebug() << "客户端已断开";
  });
}

void Server::onReadyRead() {
  // 读取全部数据
  QByteArray data = m_clientSocket->readAll();
  qDebug() << "服务器收到数据: " << QString(data);

  // 返回同样的数据
  m_clientSocket->write(data);
  qDebug() << "return: " << data;
}