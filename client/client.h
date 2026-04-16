#pragma once

#include <QTcpSocket>
#include <QObject>

class Client : public QObject {
  Q_OBJECT
public:
  explicit Client(QObject *parent = nullptr);
  void sendMessage(QString &msg);
private slots:
  void onConnected();
  void onReadyRead();
private:
  QTcpSocket *m_socket;
};