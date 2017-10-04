#include "scatterwindow.h"
#include "ui_scatterwindow.h"

#include <QMessageBox>

ScatterWindow::ScatterWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScatterWindow)
{
    ui->setupUi(this);
    graph = new Q3DScatter();
    container = QWidget::createWindowContainer(graph);

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
    }

    ui->mainLayout->addWidget(container);

    graph->axisX()->setTitle("X");
    graph->axisY()->setTitle("Y");
    graph->axisZ()->setTitle("Z");
}

ScatterWindow::~ScatterWindow()
{
    delete ui;
}
