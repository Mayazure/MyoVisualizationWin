#ifndef GESTUREWINDOW_H
#define GESTUREWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class GestureWindow;
}

class GestureWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GestureWindow(QWidget *parent = 0);
    ~GestureWindow();
    void setGestureLabel(QString gesture);

private:
    Ui::GestureWindow *ui;
};

#endif // GESTUREWINDOW_H
