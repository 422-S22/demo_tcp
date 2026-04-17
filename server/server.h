#pragma once

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject{
public:
  explicit Server(QObject *parent = nullptr);
private slots:
  void onNewConnection(); // 有新的客户端连接
  void onReadyRead();     // 有数据可读时触发
  void onDisconnected();  // 有客户端断开连接时触发
private:
  QTcpServer                  *m_server;
  QList<QTcpSocket*>          *m_clentSocketList  = nullptr;
  QMap<QTcpSocket*, int>      m_clientMap;      // socket - id
  QMap<QTcpSocket*, QString>  m_clientNameMap;  // socket - name
  int                         m_nextId            = 1;
};

