#ifndef ADAPTER_H
#define ADAPTER_H

#include <QThread>
#include <QString>
#include <QTimer>

#include "myo/myo.hpp"
#include "datacollector.h"

class DataCollector;

class Adapter : public QThread
{
    Q_OBJECT

public:
    explicit Adapter(QObject *parent = 0);

    volatile void setRunningFlag(bool flag);
    volatile void setLoggingFlag(bool flag);
    volatile void setStart(bool flag);
    void setEvent(QString event);

    void updateConsole(QString data);
    void updateTotalNum(int label);
    void updateBattery(int level);
    void updateGraph(int index, int* emg, int a,int b,int c, int d, int e, int f,int g, int h);
    void updateGyro(float x, float y, float z);

    void setPath(QString filePath, QString fileName);
    QString getFilePath();
    QString getFileName();

    void pingMyo();

protected:
    void run();

private:
    volatile bool START = false;
    volatile bool threadRun = false;
    QString filePath;
    QString fileName;
    int emgNum = 0;
    int gyrNum = 0;
    int accNum = 0;
    int oriNum = 0;
    int oreNum = 0;
    DataCollector *dc;
    QTimer *timer;

    myo::Myo* myo;

signals:
    void requestUpdateConsole(QString data);
    void requestUpdateBattery(int level);
    void requestUpdateTotalNum(QString num, int label);
    void requestUpdateGraph(int index, int*, int a,int b,int c, int d, int e, int f,int g, int h);
    void requestUpdateGyro(float x, float y, float z);

private slots:
    void checkBattery();
};

#endif // ADAPTER_H
