#include "widget.h"

#include <QApplication>
#include <QFile>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Widget w(a.arguments().at(1));
  w.show();

  return a.exec();
}
