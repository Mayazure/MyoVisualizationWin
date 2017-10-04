#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDesktopServices"
#include <QDateTime>
#include "qtextstream.h"
#include "Qtextstream"
#include <QFile>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowIcon(QIcon("icon.ico"));
    QString dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/MyoRecording";
    ui->loggingDirectory->setText(dir);
    adapter = new Adapter();
    connect(adapter,SIGNAL(requestUpdateConsole(QString)),this,SLOT(updateConsole(QString)));
    connect(adapter,SIGNAL(requestUpdateTotalNum(QString,int)),this,SLOT(updateTotalNum(QString,int)));
    connect(adapter,SIGNAL(requestUpdateBattery(int)),this,SLOT(updateBattery(int)));
    //    adapter->test();
    form = new Form();
    connect(adapter,SIGNAL(requestUpdateGraph(int, int*,int,int,int,int,int,int,int,int)),form,SLOT(realtimeDataSlot(int, int*,int,int,int,int,int,int,int,int)));
//    form->show();
}

void MainWindow::updateConsole(QString data)
{
    QDateTime time = QDateTime::currentDateTime();
    QString timef = time.toString("yyyy-MM-dd hh:mm:ss");
    QString appending = timef+"> "+data;
    if(data.endsWith("stopped.")){
        appending += " Total Records: ";
        appending += "EMG:" + ui->emgNumber->text();
        appending += ";GYR:" + ui->gyrNumber->text();
        appending += ";ACC:" + ui->accNumber->text();
        appending += ";ORI:" + ui->oriNumber->text();
        appending += ";ORE:" + ui->oreNumber->text();
        ui->emgNumber->setText("0");
        ui->gyrNumber->setText("0");
        ui->accNumber->setText("0");
        ui->oriNumber->setText("0");
        ui->oreNumber->setText("0");
    }
    ui->console->append(appending);
}

void MainWindow::updateTotalNum(QString num, int label)
{
    switch(label){
    case 0:
        ui->emgNumber->setText(num);
        break;
    case 1:
        ui->gyrNumber->setText(num);
        break;
    case 2:
        ui->accNumber->setText(num);
        break;
    case 3:
        ui->oriNumber->setText(num);
        break;
    case 4:
        ui->oreNumber->setText(num);
        break;
    }
}

void MainWindow::updateBattery(int level)
{
    QPalette pe;
    if(level<=20){
        pe.setColor(QPalette::WindowText,Qt::red);
    }
    else{
        pe.setColor(QPalette::WindowText,Qt::black);
    }
    ui->batteryLabel->setPalette(pe);
    this->ui->batteryLabel->setText("Battery: "+QString::number(level)+"%");
}

//void MainWindow::updateGraph(int data)
//{
//    this->graphAdapter->addData(data);
//}

MainWindow::~MainWindow()
{
    adapter->setRunningFlag(false);
    delete ui;
    delete adapter;
}

void MainWindow::setEventState(QString state)
{
    ui->eventState->setText(state);
}

void MainWindow::setEventName(QString name)
{
    ui->eventName->setText(name);
}

void MainWindow::on_buttonBse1_clicked()
{
    setEventName("baseline1");
    setEventState("ready");
}

void MainWindow::on_buttonBse2_clicked()
{
    setEventName("baseline2");
    setEventState("ready");
}

void MainWindow::on_buttonBse3_clicked()
{
    setEventName("baseline3");
    setEventState("ready");
}

void MainWindow::on_buttonBse4_clicked()
{
    setEventName("baseline4");
    setEventState("ready");
}

void MainWindow::on_buttonBse5_clicked()
{
    setEventName("baseline5");
    setEventState("ready");
}

void MainWindow::on_buttonBse6_clicked()
{
    setEventName("baseline6");
    setEventState("ready");
}

void MainWindow::on_buttonBse7_clicked()
{
    setEventName("baseline7");
    setEventState("ready");
}

void MainWindow::on_buttonBse8_clicked()
{
    setEventName("baseline8");
    setEventState("ready");
}

void MainWindow::on_buttonTest_clicked()
{
    setEventName("test");
    setEventState("ready");
}

void MainWindow::on_buttonFreeNon_clicked()
{
    setEventName("free-non");
    setEventState("ready");
}

void MainWindow::on_buttonMotorNon_clicked()
{
    setEventName("Motorway-non");
    setEventState("ready");
}

void MainWindow::on_buttonMotorFull_clicked()
{
    setEventName("Motorway-full");
    setEventState("ready");
}

void MainWindow::on_buttonHighNon_clicked()
{
    setEventName("Highway-non");
    setEventState("ready");
}

void MainWindow::on_buttonHighFull_clicked()
{
    setEventName("Highway-full");
    setEventState("ready");
}

void MainWindow::on_buttonCityFull_clicked()
{
    setEventName("Free-full");
    setEventState("ready");
}

void MainWindow::on_buttonExtra_clicked()
{
    setEventName("Extra");
    setEventState("ready");
}

void MainWindow::on_buttonStart_clicked()
{
    QString newEvent = ui->eventName->text();
    if(newEvent == "" ||newEvent == nullptr){
        updateConsole("No event specified! Recording paused.");
    }
    else{
        setEventState("record");
        this->adapter->setEvent(newEvent);
        this->adapter->setLoggingFlag(true);
    }

}

void MainWindow::on_buttonEnd_clicked()
{
    this->adapter->setLoggingFlag(false);
    setEventState("ready");
}

void MainWindow::on_buttonCtrStart_clicked()
{
    this->adapter->setRunningFlag(true);
    this->adapter->setStart(true);
    this->adapter->start();
}

void MainWindow::on_buttonCtrStop_clicked()
{
    this->adapter->setRunningFlag(false);
    this->adapter->setStart(false);
//    this->graphAdapter->close();
}

void MainWindow::on_buttonPause_clicked()
{
    QString fileName = adapter->getFilePath()+"/"+"log-"+adapter->getFileName()+".txt";
    QString str = ui->console->toPlainText();
    QFile file(fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream in(&file);
    in<<str;
    file.close();
}



void MainWindow::on_graphButton_clicked()
{
    if(form->isHidden()){
        form->show();
    }
    else{
        form->hide();
    }
}

void MainWindow::on_buttonCtrPing_clicked()
{
    adapter->pingMyo();
}


