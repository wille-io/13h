#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


class Widget : public QWidget
{
  Q_OBJECT

public:
  explicit Widget(const QString &path, QWidget *parent = 0);
  ~Widget();

  void drawImage(const QString &filename);

protected:
  void paintEvent(QPaintEvent *event);

private:
  QByteArray mImage;
  int mFrame;
};

#endif // WIDGET_H
