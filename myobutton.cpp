#include "myobutton.h"
#include <QPainter>

MyoButton::MyoButton(int type)
{
    setMaximumSize(100,100);
    setMinimumSize(100,100);
    resize(100,100);
    this->type = type;
}

void MyoButton::paintEvent(QPaintEvent *pEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(QColor(r,g,b),1,Qt::SolidLine,Qt::FlatCap,Qt::MiterJoin);
    painter.setPen(pen);

    QBrush brush(QColor(r,g,b,a), Qt::SolidPattern);
    painter.setBrush(brush);

    painter.drawPolygon(points[type],4);
}

void MyoButton::setColor(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void MyoButton::setLevel(int a)
{
    this->a = a;
    update();
}
