#include "gesturewindow.h"
#include "ui_gesturewindow.h"

GestureWindow::GestureWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GestureWindow)
{
    ui->setupUi(this);
    ui->gestureLabel->setAlignment(Qt::AlignCenter);
}

GestureWindow::~GestureWindow()
{
    delete ui;
}

void GestureWindow::setGestureLabel(QString gesture)
{
    ui->gestureLabel->setText(gesture);
}
