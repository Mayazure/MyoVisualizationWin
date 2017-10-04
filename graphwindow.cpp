#include "graphwindow.h"
#include "ui_graphwindow.h"
#include <QtAlgorithms>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    QDateTime time(QDateTime::currentDateTime());
    QString timeString = time.toString("yyyy-MM-dd");
    QString title = "Myo Control Graph - "+timeString;
    setWindowTitle(title);

    plots.clear();
    plots.append(ui->customePlot);
    plots.append(ui->customePlot1);
    plots.append(ui->customePlot2);
    plots.append(ui->customePlot3);
    plots.append(ui->customePlot4);
    plots.append(ui->customePlot5);
    plots.append(ui->customePlot6);
    plots.append(ui->customePlot7);

//    plotsHigh.clear();
//    plotsHigh.append(ui->customePlot8);
//    plotsHigh.append(ui->customePlot9);
//    plotsHigh.append(ui->customePlot10);
//    plotsHigh.append(ui->customePlot11);
//    plotsHigh.append(ui->customePlot12);
//    plotsHigh.append(ui->customePlot13);
//    plotsHigh.append(ui->customePlot14);
//    plotsHigh.append(ui->customePlot15);

    setupRealtimeData(plots);
//    setupRealtimeData(plotsHigh);

    for(int i=0;i<8;i++){
        AVG[i] = 0;
    }

    podwindowi = new podwindow();
    podwindowi->setMaximumSize(400,400);
//    podwindowi->show();
    ui->generalGraphLayout->addWidget(podwindowi);
//    scatterWindow = new ScatterWindow();
//    scatterWindow->show();
}

Form::~Form()
{
    delete ui;
}

void Form::setupRealtimeData(QList<QCustomPlot*> plots)
{
    /*
    customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->legend->setFont(font);
    */

    //    QSharedPointer<QCPAxisTickerDateTime> timeTicker(new QCPAxisTickerDateTime);
    //    QSharedPointer<QCPAxisTickerFixed> timeTicker(new QCPAxisTickerFixed);
    //    timeTicker->setDateTimeFormat("hh:mm:ss:zzzz");
    //    timeTicker->setTickStep(1.0);

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s:%z");
    timeTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssReadability);
    timeTicker->setTickCount(10);

    for(int i=0;i<8;i++){
        plots.at(i)->addGraph();
        plots.at(i)->graph(0)->setPen(QPen(Qt::blue));
        plots.at(i)->graph(0)->setName("Line"+i);

        plots.at(i)->xAxis->setTicker(timeTicker);
        plots.at(i)->axisRect()->setupFullAxesBox();
        plots.at(i)->yAxis->setRange(-130, 130);

        plots.at(i)->setBackground(QBrush(QColor(60,60,60)));
        plots.at(i)->axisRect()->setBackground(QBrush(QColor(60,60,60)));

        plots.at(i)->yAxis->setTickLabelColor(QColor(255,255,255));
        plots.at(i)->xAxis->setTickLabelColor(QColor(255,255,255));

        connect(plots.at(i)->xAxis, SIGNAL(rangeChanged(QCPRange)), plots.at(i)->xAxis2, SLOT(setRange(QCPRange)));
        connect(plots.at(i)->yAxis, SIGNAL(rangeChanged(QCPRange)), plots.at(i)->yAxis2, SLOT(setRange(QCPRange)));
    }

}

void Form::realtimeDataSlot(int index, int* emgData, int a,int b,int c, int d, int e, int f,int g, int h)
{
    if(!reploting){
        return;
    }

    int emg[8]={a,b,c,d,e,f,g,h};

    if(inamount<20){
        inamount++;
        for(int i=0;i<8;i++){
            AVG[i] = AVG[i]+qAbs((double)emg[i]/(double)inamount);
        }
    }
    else{
        podwindowi->updatePods(AVG,8);
        inamount = 0;
        for(int i=0;i<8;i++){
            AVG[i] = 0;
        }
    }

    QTime time(QTime::currentTime());
    double key = time.msecsSinceStartOfDay()/1000.0;

//    if(index==0){
        for(int i=0;i<8;i++){
            plots.at(i)->graph(0)->addData(key,emg[i]);
            plots.at(i)->xAxis->setRange(key,4,Qt::AlignRight);
        }
//    }
//    else{
//        for(int i=0;i<8;i++){
//            plotsHigh.at(i)->graph(0)->addData(key,emg[i]);
//            plotsHigh.at(i)->xAxis->setRange(key,4,Qt::AlignRight);
//        }
//    }


    if(count == 4){
        for(int i=0;i<8;i++){
            plots.at(i)->replot();
//            plotsHigh.at(i)->replot();
        }
        count = 0;
    }
    else{
        count ++;
    }
}

void Form::showGraph(int n)
{
    if(n==8){
        for(int i=0;i<8;i++){
            plots.at(i)->show();
        }
    }
    else{
        plots.at(n)->show();
        for(int i=0;i<8;i++){
            if(i!=n){
                plots.at(i)->hide();
            }
        }
    }

}

void Form::on_showAll_clicked()
{
    showGraph(8);
}

void Form::on_showA_clicked()
{
    showGraph(0);
}

void Form::on_showB_clicked()
{
    showGraph(1);
}

void Form::on_showC_clicked()
{
    showGraph(2);
}

void Form::on_showD_clicked()
{
    showGraph(3);
}

void Form::on_showE_clicked()
{
    showGraph(4);
}

void Form::on_showF_clicked()
{
    showGraph(5);
}

void Form::on_showG_clicked()
{
    showGraph(6);
}

void Form::on_showH_clicked()
{
    showGraph(7);
}

void Form::on_showPause_clicked()
{
    if(reploting){
        reploting = false;
        ui->showPause->setText("Start");
    }
    else{
        reploting = true;
        ui->showPause->setText("Pause");
    }
}
