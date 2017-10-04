#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adapter.h"
#include "graphwindow.h"
#include "podwindow.h"

class Adapter;
class Form;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonBse1_clicked();
    void on_buttonBse2_clicked();
    void on_buttonBse3_clicked();
    void on_buttonBse4_clicked();
    void on_buttonFreeNon_clicked();
    void on_buttonMotorNon_clicked();
    void on_buttonMotorFull_clicked();
    void on_buttonCityFull_clicked();

private:
    Ui::MainWindow *ui;
    void setEventState(QString state);
    void setEventName(QString name);
    Adapter *adapter;
    Form *form;
    podwindow *podwindowi;

private slots:
    void updateConsole(QString data);
    void updateTotalNum(QString num, int label);
    void updateBattery(int level);
    void on_buttonStart_clicked();
    void on_buttonEnd_clicked();
    void on_buttonCtrStart_clicked();
    void on_buttonCtrStop_clicked();
    void on_buttonHighNon_clicked();
    void on_buttonHighFull_clicked();
    void on_buttonPause_clicked();
    void on_buttonBse5_clicked();
    void on_buttonBse6_clicked();
    void on_buttonBse7_clicked();
    void on_buttonBse8_clicked();
    void on_graphButton_clicked();
    void on_buttonTest_clicked();
    void on_buttonCtrPing_clicked();
    void on_buttonExtra_clicked();
};

#endif // MAINWINDOW_H
