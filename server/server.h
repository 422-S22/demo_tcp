#pragma once

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject{
public:
  explicit Server(QObject *parent = nullptr);
private slots:
  void onNewConnection(); // 有新的客户端连接
  void onReadyRead();     // 有数据可读时触发
private:
  QTcpServer *m_server;
  QTcpSocket *m_clientSocket = nullptr;
};

