#include "scatterwindow.h"
#include "ui_scatterwindow.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>
#include <QtGui/QFontDatabase>
#include <QTextStream>
#include <iostream>
#include <Q3DScatter>
#include <QtDataVisualization/q3dscatter.h>

#include "scatterdatamodifier.h"

using namespace QtDataVisualization;

ScatterWindow::ScatterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScatterWindow)
{
    ui->setupUi(this);

    Q3DScatter *graph = new Q3DScatter();

    QWidget *container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return;
    }


    this->setMinimumSize(400,400);

    QSize screenSize = graph->screen()->size();
//    container->setMinimumSize(QSize(screenSize.width() / 30, screenSize.height() / 20));
    container->setMinimumSize(400,400);
//    container->setMaximumSize(400,400);
//    container->setMaximumSize(QSize(screenSize.width() / 3, screenSize.height() / 2));
//    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    container->setFocusPolicy(Qt::StrongFocus);

//    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    this->setWindowTitle(QStringLiteral("The gyro direction"));

    modifier = new ScatterDataModifier(graph);
    modifier->setInitValue(0,0,10);
//    connect(this,SIGNAL(addData(float,float,float)),modifier,SLOT(armMoving(float,float,float)));
}

ScatterWindow::~ScatterWindow()
{
    delete ui;
}

void ScatterWindow::addData(float x, float y, float z)
{
    modifier->armMoving(x,y,z);
}
