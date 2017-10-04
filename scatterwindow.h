#ifndef SCATTERWINDOW_H
#define SCATTERWINDOW_H

#include <QWidget>
#include "scatterdatamodifier.h"

namespace Ui {
class ScatterWindow;
}

class ScatterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScatterWindow(QWidget *parent = 0);
    ~ScatterWindow();

    void addData(float x, float y, float z);

private:
    Ui::ScatterWindow *ui;
    ScatterDataModifier *modifier;
};

#endif // SCATTERWINDOW_H
