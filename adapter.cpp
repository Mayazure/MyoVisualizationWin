#include "adapter.h"
#include <QDebug>

Adapter::Adapter(QObject *parent):QThread(parent)
{
    dc = new DataCollector(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(checkBattery()));
    timer->start(3000);
}

void Adapter::updateConsole(QString data)
{
    emit requestUpdateConsole(data);
}

void Adapter::updateTotalNum(int label)
{
    switch(label){
    case 0:
        emgNum++;
        emit requestUpdateTotalNum(QString::number(emgNum),0);
        break;
    case 1:
        gyrNum++;
        emit requestUpdateTotalNum(QString::number(gyrNum),1);
        break;
    case 2:
        accNum++;
        emit requestUpdateTotalNum(QString::number(accNum),2);
        break;
    case 3:
        oriNum++;
        emit requestUpdateTotalNum(QString::number(oriNum),3);
        break;
    case 4:
        oreNum++;
        emit requestUpdateTotalNum(QString::number(oreNum),4);
        break;
    }
}

void Adapter::updateBattery(int level)
{
    emit(requestUpdateBattery(level));
}

void Adapter::updateGraph(int index, int* emg, int a,int b,int c, int d, int e, int f,int g, int h)
{
    //    qDebug()<<emg[0];
    emit requestUpdateGraph(index, emg, a,b,c,d,e,f,g,h);
}

void Adapter::setPath(QString filePath, QString fileName)
{
    this->filePath = filePath;
    this->fileName = fileName;
}

QString Adapter::getFilePath()
{
    return filePath;
}

QString Adapter::getFileName()
{
    return fileName;
}

void Adapter::pingMyo()
{
    if(START){
        myo->vibrate(myo->VibrationType::vibrationMedium);
    }
}

void Adapter::checkBattery()
{
    if(START){
        myo->requestBatteryLevel();
    }
}

volatile void Adapter::setRunningFlag(bool flag)
{
    this->threadRun = flag;
}

volatile void Adapter::setLoggingFlag(bool flag)
{
    this->dc->setLoggingFlag(flag);
    if(flag){
        updateConsole("Recording: " + dc->getEvent());
    }
    else{
        updateConsole("Recording paused.");
    }
}

volatile void Adapter::setStart(bool flag)
{
    START = flag;
}

void Adapter::setEvent(QString event)
{
    this->dc->setEvent(event);
}

void Adapter::run()
{
    try {

        myo::Hub hub("com.undercoveryeti.myo-data-capture");
        //        hub = new myo::Hub("com.undercoveryeti.myo-data-capture");

        emit requestUpdateConsole("Attempting to find a Myo...");

        //        myo::Myo* myo = hub.waitForMyo(10000);
        myo = hub.waitForMyo(10000);

        // If waitForMyo() returned a null pointer, we failed to find a Myo, so exit with an error message.
        if (!myo) {
            throw std::runtime_error("Unable to find a Myo!");
            emit requestUpdateConsole("Unable to find a Myo!");
        }

        // We've found a Myo.
        emit requestUpdateConsole("Connected to a Myo armband.");

        // Next we enable EMG streaming on the found Myo.
        myo->setStreamEmg(myo::Myo::streamEmgEnabled);
        myo->requestBatteryLevel();

        // Next we construct an instance of our DeviceListener, so that we can register it with the Hub.
        //        DataCollector collector;

        // Hub::addListener() takes the address of any object whose class inherits from DeviceListener, and will cause
        // Hub::run() to send events to all registered device listeners.
        hub.addListener(dc);

        // Finally we enter our main loop.

        while (threadRun) {
            // In each iteration of our main loop, we run the Myo event loop for a set number of milliseconds.
            // In this case, we wish to update our display 50 times a second, so we run for 1000/20 milliseconds.
            hub.run(1);
        }

        emit requestUpdateConsole("Recording stopped.");

        // If a standard exception occurred, we print out its message and exit.
    } catch (const std::exception& e) {
        emit requestUpdateConsole(e.what());
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Press enter to continue.";
        std::cin.ignore();
        return;
    }
}
