#include <QCoreApplication>
#include "client.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  QString msg = "msg";

  Client c;
  c.sendMessage(msg);
  
  return app.exec();
}