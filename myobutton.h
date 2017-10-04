#ifndef MYOBUTTON_H
#define MYOBUTTON_H

#include "QPushButton"

static const QPointF points[6][4] = {
    {
        QPointF(0,0),
        QPointF(100,0),
        QPointF(100,20),
        QPointF(0,20)
    },
    {
        QPointF(0,80),
        QPointF(100,80),
        QPointF(100,100),
        QPointF(0,100)
    },
    {
        QPointF(0,0),
        QPointF(20,0),
        QPointF(20,100),
        QPointF(0,100)
    },
    {
        QPointF(80,0),
        QPointF(100,0),
        QPointF(100,100),
        QPointF(80,100)
    },
    {
        QPointF(7.568,21.712),
        QPointF(21.712,7.568),
        QPointF(92.432,78.289),
        QPointF(78.289,92.432)
    },
    {
        QPointF(78.289,7.568),
        QPointF(92.432,21.712),
        QPointF(21.712,92.432),
        QPointF(7.568,78.289)
    }
};

class MyoButton : public QPushButton
{
public:
    MyoButton(int type);
    void paintEvent(QPaintEvent* pEvent);
    void setColor(int r, int g, int b);
    void setLevel(int a);

private:
    int r = 0;
    int g = 176;
    int b = 240;
    int a = 0;

    int type = 0;
};

#endif // MYOBUTTON_H
