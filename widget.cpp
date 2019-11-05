#include "widget.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QTimer>
//#include <QDir>
#include <QDebug>


Widget::Widget(const QString &path, QWidget *parent)
  : QWidget(parent)
  , mFrame(0)
{
  setGeometry(x(), y(), 320, 200);

  QTimer *t = new QTimer(this);

  drawImage(path + "/frame_" + QString::number(mFrame++) + ".13h");

  connect(t, &QTimer::timeout,
          this, [this, path]()
  {
    drawImage(path + "/frame_" + QString::number(mFrame++) + ".13h");
  });

  t->setInterval(40);
  t->start();
}


Widget::~Widget()
{

}


void Widget::drawImage(const QString &filename)
{
  QFile f(filename);

  if (!f.open(QFile::ReadOnly))
  {
    puts("cannot open file");
    qWarning() << "file" << f.fileName();
    abort();
  }

  mImage = f.readAll();

  if (mImage.size() != 320*200)
  {
    qWarning() << "image not in 320x200x8 VGA format - is" << mImage.size() << "-" << filename;
    return;
  }

  //qWarning() << "1: frame" << mFrame;

  update();
}


#define SW 320
#define SH 200


void Widget::paintEvent(QPaintEvent *)
{
  QPainter p(this);
  p.save();

  for (int y = 0; y < SH; y++)
  {
    for (int x = 0; x < SW; x++)
    {
      uint8_t pixel = mImage.at((y * SW) + x);

      // mask color bits & stretch from 8 bits to 256 bits
      uint8_t r = ((pixel & 0xC0) >> 6) * 32;
      uint8_t g = ((pixel & 0x38) >> 4) * 32;
      uint8_t b = (pixel & 0x07) * 32;

      QColor c(r, g, b);
      p.setPen(c);

      p.drawPoint(x, y);
    }
  }

  p.restore();

  //qWarning() << "2: frame" << mFrame;
}
