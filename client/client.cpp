#include "client.h"

#define SERVER_LISTEN_PORT 9999 

Client::Client(QObject *parent) : QObject(parent) {
  // 1.创建 socket
  m_socket = new QTcpSocket(this);

  // 2.绑定信号槽
  connect(m_socket, &QTcpSocket::connected, this, &Client::onConnected);
  connect(m_socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);

  // 3.连接到服务端
  qDebug() << "正在连接服务端...";
  m_socket->connectToHost("127.0.0.1", SERVER_LISTEN_PORT);
}

void Client::onConnected() {
  qDebug() << "连接服务端成功";
}

void Client::sendMessage(QString &msg) {
  m_socket->write(msg.toUtf8());
}

void Client::onReadyRead() {
  QByteArray data = m_socket->readAll();
  qDebug() << "收到服务器返回结果: " << QString(data);
}
