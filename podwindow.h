#ifndef PODWINDOW_H
#define PODWINDOW_H

#include <QWidget>
#include <QToolButton>
#include "myobutton.h"

struct podsPropertie{
    int angle = 0;
    int l1 = 0;
    int l2 = 0;
};

namespace Ui {
class podwindow;
}

class podwindow : public QWidget
{
    Q_OBJECT

public:
    explicit podwindow(QWidget *parent = 0);
    ~podwindow();

    void updatePods(double* pods, int len);

private:
    Ui::podwindow *ui;
    QList<QToolButton*> pods;
    MyoButton* myobutton;
    QList<MyoButton*> ePods;
    podsPropertie podsPro[8];

    void initPods();
    //    void initPodsPro();

private slots:
    void button0_clicked();
};

#endif // PODWINDOW_H
