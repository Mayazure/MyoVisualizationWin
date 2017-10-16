#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QWidget>
#include "qcustomplot.h"
#include "podwindow.h"
#include "scatterwindow.h"
#include "fileadapter.h"

class FileAdapter;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void setupRealtimeData(QList<QCustomPlot*> plots);

public slots:
    void realtimeDataSlot(int index, int*, int a,int b,int c, int d, int e, int f,int g, int h);
    void updateGyro(float, float, float);

private slots:

    void on_showAll_clicked();
    void on_showA_clicked();
    void on_showB_clicked();
    void on_showC_clicked();
    void on_showD_clicked();
    void on_showE_clicked();
    void on_showF_clicked();
    void on_showG_clicked();
    void on_showH_clicked();
    void on_showPause_clicked();

    void on_showLoad_clicked();

private:
    Ui::Form *ui;
    int count = 0;
    bool reploting = true;
    QList<QCustomPlot*> plots;
    QList<QCustomPlot*> plotsHigh;

    int inamount = 0;
    int gyroamount = 0;
    double AVG[8];
    podwindow *podwindowi;
    ScatterWindow *scatterWindow;

    float x_axis = 0;
    float y_axis = 0;
    float z_axis = 0;

    void showGraph(int n);
    FileAdapter *fa;
};

#endif // GRAPHWINDOW_H
