#include "podwindow.h"
#include "ui_podwindow.h"
#include <QPalette>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

podwindow::podwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::podwindow)
{
    ui->setupUi(this);

    initPods();
    ui->gridLayout->addWidget(ePods.at(0),2,1,Qt::AlignCenter);
    ui->gridLayout->addWidget(ePods.at(1),2,2,Qt::AlignCenter);
    ui->gridLayout->addWidget(ePods.at(2),1,2,Qt::AlignCenter);
    ui->gridLayout->addWidget(ePods.at(3),0,2,Qt::AlignCenter);
    ui->gridLayout->addWidget(ePods.at(4),0,1,Qt::AlignCenter);
    ui->gridLayout->addWidget(ePods.at(5),0,0,Qt::AlignCenter);
    ui->gridLayout->addWidget(ePods.at(6),1,0,Qt::AlignCenter);
    ui->gridLayout->addWidget(ePods.at(7),2,0,Qt::AlignCenter);

    gestureLabel = new QLabel("*");
    ui->gridLayout->addWidget(gestureLabel,1,1,Qt::AlignCenter);
//    openfile();

    //    connect(ePods.at(0),SIGNAL(clicked(bool)),this,SLOT(button0_clicked()));
}

podwindow::~podwindow()
{
    delete ui;
}

void podwindow::updatePods(double *podsvalue, int len)
{
    double avgL = 0;
    double avgR = 0;
    for(int i=0;i<len;i++){
        //        double value = 0.0133*podsvalue[i]*podsvalue[i]-0.531*podsvalue[i]+0.518;
        //        qDebug()<<podsvalue[i];
        double value = podsvalue[i];
        if(value>255){
            value = 255;
        }
        else if(value<0){
            value = 0;
        }

        ePods.at(i)->setLevel((int)value);
        ePods.at(i)->update();

        if(i==4||i==5){
            avgR+=podsvalue[i];
        }
        else if(i==6||i==7||i==8){
            avgL+=podsvalue[i];
        }
    }
    avgL = avgL/3;
    avgR = avgR/3;
    int th = 8;
    QString currentDirect;
    if(avgL-avgR>th){
        currentDirect = "L";
    }
    else if(avgR-avgL>th){
        currentDirect = "R";
    }
    else{
        currentDirect = "M";
    }
    gestureLabel->setText(currentDirect);
    if(currentDirect!=direct){
        direct = currentDirect;
//        writeToFile();
    }
}

void podwindow::initPods()
{
    //    for(int i=0;i<8;i++){
    //        int type = 0;
    //        switch(i){
    //        case 0:
    //            type = 0;
    //            break;
    //        case 1:
    //            type = 4;
    //            break;
    //        case 2:
    //            type = 3;
    //            break;
    //        case 3:
    //            type = 5;
    //            break;
    //        case 4:
    //            type = 1;
    //            break;
    //        case 5:
    //            type = 4;
    //            break;
    //        case 6:
    //            type = 2;
    //            break;
    //        case 7:
    //            type = 5;
    //            break;
    //        }

    for(int i=0;i<8;i++){
        int type = 0;
        switch(i){
        case 0:
            type = 1;
            break;
        case 1:
            type = 5;
            break;
        case 2:
            type = 3;
            break;
        case 3:
            type = 4;
            break;
        case 4:
            type = 0;
            break;
        case 5:
            type = 5;
            break;
        case 6:
            type = 2;
            break;
        case 7:
            type = 4;
            break;
        }

        MyoButton* myobutton = new MyoButton(type);
        ePods.append(myobutton);
    }
}

void podwindow::writeToFile(QString line)
{
    QTextStream out(file);
    out<<line<<"\n";
}

void podwindow::openfile()
{
    QString path = "C:/Users/Mayazure/Desktop/moon/MyoGesture/1.txt";
    file = new  QFile(path);
    if(!file->open(QIODevice::ReadWrite | QIODevice::Text)){
        QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
    }
}

void podwindow::button0_clicked()
{
    //    ui->widget->hide();
}
