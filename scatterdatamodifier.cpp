/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Data Visualization module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "scatterdatamodifier.h"
#include <QtDataVisualization/qscatterdataproxy.h>
#include <QtDataVisualization/qvalue3daxis.h>
#include <QtDataVisualization/q3dscene.h>
#include <QtDataVisualization/q3dcamera.h>
#include <QtDataVisualization/qscatter3dseries.h>
#include <QtDataVisualization/q3dtheme.h>
#include <QtCore/qmath.h>
#include <QtWidgets/QComboBox>
#include <iostream>

using namespace std;

using namespace QtDataVisualization;

#define PI 3.1415926

const int numberOfItems = 3600;
const float curveDivider = 3.0f;
const int lowerNumberOfItems = 1900;
const float lowerCurveDivider = 0.75f;

ScatterDataModifier::ScatterDataModifier(Q3DScatter *scatter)
    : m_graph(scatter),
      m_fontSize(40.0f),
      m_style(QAbstract3DSeries::MeshSphere),
      m_smooth(true),
      m_itemCount(lowerNumberOfItems),
      m_curveDivider(lowerCurveDivider),
      i_count(0)
{
    //! [0]
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(m_fontSize);
    m_graph->activeTheme()->setFont(font);
    m_graph->setShadowQuality(QAbstract3DGraph::ShadowQualitySoftLow);
    m_graph->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPresetFront);
    //! [0]

    //! [2]
    QScatterDataProxy *proxy = new QScatterDataProxy;
    QScatter3DSeries *series = new QScatter3DSeries(proxy);
    series->setItemLabelFormat(QStringLiteral("@xTitle: @xLabel @yTitle: @yLabel @zTitle: @zLabel"));
    series->setMeshSmooth(m_smooth);
    m_graph->addSeries(series);
    //! [2]

    //! [3]
    addData();
    //! [3]
}

ScatterDataModifier::~ScatterDataModifier()
{
    delete m_graph;
}

void ScatterDataModifier::addData()
{
    // Configure the axes according to the data
    //! [4]
    m_graph->axisX()->setTitle("X");
    m_graph->axisY()->setTitle("Y");
    m_graph->axisZ()->setTitle("Z");
    //! [4]

    //! [5]
    dataArray = new QScatterDataArray;
    dataArray->resize(m_itemCount);
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    //! [5]

    // set 8 points in the corner to fix axis
    ptrToDataArray->setPosition(QVector3D(32.0f, 16.0f, 32.0f));
    ptrToDataArray++;
    ptrToDataArray->setPosition(QVector3D(-32.0f, 16.0f, 32.0f));
    ptrToDataArray++;
    ptrToDataArray->setPosition(QVector3D(32.0f, -16.0f, 32.0f));
    ptrToDataArray++;
    ptrToDataArray->setPosition(QVector3D(32.0f, 16.0f, -32.0f));
    ptrToDataArray++;
    ptrToDataArray->setPosition(QVector3D(-32.0f, -16.0f, 32.0f));
    ptrToDataArray++;
    ptrToDataArray->setPosition(QVector3D(-32.0f, 16.0f, -32.0f));
    ptrToDataArray++;
    ptrToDataArray->setPosition(QVector3D(32.0f, -16.0f, -32.0f));
    ptrToDataArray++;
    ptrToDataArray->setPosition(QVector3D(-32.0f, -16.0f, -32.0f));
    ptrToDataArray++;

    //! [6]
    // draw the column points to (0, 0, 10)
    total_point = 0;
    for (float z = 0.0f; z <= 10.5f; z += 0.5f){
        for (float theta = 0.0f; theta < PI / 2 + PI / 10; theta += PI / 10, total_point += 4){
            float y = 1 * qCos(theta);
            ptrToDataArray->setPosition(QVector3D(sqrt(1.0f - y * y), y, z));
            ptrToDataArray++;
            ptrToDataArray->setPosition(QVector3D(-sqrt(1.0f - y * y), y, z));
            ptrToDataArray++;

            y = -y;
            ptrToDataArray->setPosition(QVector3D(sqrt(1.0f - y * y), y, z));
            ptrToDataArray++;
            ptrToDataArray->setPosition(QVector3D(-sqrt(1.0f - y * y), y, z));
            ptrToDataArray++;
        }
    }
    //! [6]

    for (float z = 11.0f; z <= 15.0f; z += 0.5f){
        float denominator = (15.0f - z) * 6.0f;
        for (float theta = 0.0f; theta < PI / 2 + PI / denominator; theta += PI / denominator, total_point += 4){
            float y = sqrt(2.0f / 5.0f * (15.0f - z) * (15.0f - z)) * qCos(theta);
            ptrToDataArray->setPosition(QVector3D(sqrt(2.0f / 5.0f * (15.0f - z) * (15.0f - z) - y * y), y, z));
            ptrToDataArray++;
            ptrToDataArray->setPosition(QVector3D(-sqrt(2.0f / 5.0f * (15.0f - z) * (15.0f - z) - y * y), y, z));
            ptrToDataArray++;

            y = -y;
            ptrToDataArray->setPosition(QVector3D(sqrt(2.0f / 5.0f * (15.0f - z) * (15.0f - z) - y * y), y, z));
            ptrToDataArray++;
            ptrToDataArray->setPosition(QVector3D(-sqrt(2.0f / 5.0f * (15.0f - z) * (15.0f - z) - y * y), y, z));
            ptrToDataArray++;
        }
    }

    // record the initial corrdinates of the column for rotating later
    zero_coordinates.resize(total_point + 1);
    ptrToDataArray =  &dataArray->first();
    ptrToDataArray += 8;
    for(int i = 0; i < total_point; i++, ptrToDataArray++){
        zero_coordinates[i].setX(ptrToDataArray->x());
        zero_coordinates[i].setY(ptrToDataArray->y());
        zero_coordinates[i].setZ(ptrToDataArray->z());
    }

    //! [7]
    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
    m_graph->seriesList().at(0)->setItemSize(0.05f);
    //! [7]
}

// The key function, rotating column by rotete matrix, the new column direction are always rotated from (0, 0, 10)
void ScatterDataModifier::armMoving(float x_axis, float y_axis, float z_axis)
{
//    i_count++;          // the line of file
    QScatterDataItem *ptrToDataArray = &dataArray->first();
    ptrToDataArray += 8;

    // get the unit rotation axis, also the nomal vector of the plane that construct by origin and rotating dots
    float nv_a = y_init * z_axis - y_axis * z_init;
    float nv_b = -x_init * z_axis + x_axis * z_init;
    float nv_c = x_init * y_axis - x_axis * y_init;
    float len = sqrt(nv_a * nv_a + nv_b * nv_b + nv_c * nv_c);
    float unit_nv_a = nv_a / len;
    float unit_nv_b = nv_b / len;
    float unit_nv_c = nv_c / len;

    // get the cos and sin of rotating angle
    float mult_vector = x_axis * x_init + y_axis * y_init
            + z_axis * z_init;

    float mult_len_vector = sqrt(x_axis * x_axis + y_axis * y_axis
                                 + z_axis * z_axis)
            * sqrt(x_init * x_init + y_init * y_init
                   + z_init * z_init);

    float cosA = mult_vector / mult_len_vector;
    float sinA = 1.0f - cosA * cosA;

    // calculate rotating matrix
    QMatrix4x4 A1(unit_nv_a * unit_nv_a, unit_nv_a * unit_nv_b, unit_nv_a * unit_nv_c, 0,
                  unit_nv_b * unit_nv_a, unit_nv_b * unit_nv_b, unit_nv_b * unit_nv_c, 0,
                  unit_nv_c * unit_nv_a, unit_nv_c * unit_nv_b, unit_nv_c * unit_nv_c, 0,
                  0, 0, 0, 1);
    QMatrix4x4 A2(0, -unit_nv_c, unit_nv_b, 0,
                  unit_nv_c, 0, -unit_nv_a, 0,
                  -unit_nv_b, unit_nv_a, 0, 0,
                  0, 0, 0, 1);
    QMatrix4x4 I(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);
    QMatrix4x4 Rotate = A1 + cosA * (I - A1) + sinA * A2;
    Rotate = Rotate.transposed();

    // get the new coordinates of column
    for(int i = 0; i < total_point; i++, ptrToDataArray++){
        QVector4D coordinates(zero_coordinates[i]);
        coordinates = coordinates * Rotate;
        ptrToDataArray->setPosition(QVector3D(coordinates.x(), coordinates.y(), coordinates.z()));
    }

    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);

    // the file is end
//    if(i_count == file_count){
//        timer->stop();
//    }

}

//void ScatterDataModifier::setTime()
//{
//    timer=new QTimer();
//    int speed = 20;
//    timer->setInterval(speed);
//    timer->start();
//    connect(timer,SIGNAL(timeout()),this,SLOT(armMoving()));
//}

//void ScatterDataModifier::setAxis(float *x_axis, float *y_axis, float *z_axis)
//{
//    this->x_axis = x_axis;
//    this->y_axis = y_axis;
//    this->z_axis = z_axis;
//}

void ScatterDataModifier::setFileCount(int count)
{
    file_count = count;
}

//! [8]
void ScatterDataModifier::changeStyle(int style)
{
    QComboBox *comboBox = qobject_cast<QComboBox *>(sender());
    if (comboBox) {
        m_style = QAbstract3DSeries::Mesh(comboBox->itemData(style).toInt());
        if (m_graph->seriesList().size())
            m_graph->seriesList().at(0)->setMesh(m_style);
    }
}

void ScatterDataModifier::setSmoothDots(int smooth)
{
    m_smooth = bool(smooth);
    QScatter3DSeries *series = m_graph->seriesList().at(0);
    series->setMeshSmooth(m_smooth);
}

void ScatterDataModifier::changeTheme(int theme)
{
    Q3DTheme *currentTheme = m_graph->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(theme));
    emit backgroundEnabledChanged(currentTheme->isBackgroundEnabled());
    emit gridEnabledChanged(currentTheme->isGridEnabled());
    emit fontChanged(currentTheme->font());
}

void ScatterDataModifier::changePresetCamera()
{
    static int preset = Q3DCamera::CameraPresetFrontLow;

    m_graph->scene()->activeCamera()->setCameraPreset((Q3DCamera::CameraPreset)preset);

    if (++preset > Q3DCamera::CameraPresetDirectlyBelow)
        preset = Q3DCamera::CameraPresetFrontLow;
}

void ScatterDataModifier::changeLabelStyle()
{
    m_graph->activeTheme()->setLabelBackgroundEnabled(!m_graph->activeTheme()->isLabelBackgroundEnabled());
}

void ScatterDataModifier::changeFont(const QFont &font)
{
    QFont newFont = font;
    newFont.setPointSizeF(m_fontSize);
    m_graph->activeTheme()->setFont(newFont);
}

void ScatterDataModifier::shadowQualityUpdatedByVisual(QAbstract3DGraph::ShadowQuality sq)
{
    int quality = int(sq);
    emit shadowQualityChanged(quality); // connected to a checkbox in main.cpp
}

void ScatterDataModifier::changeShadowQuality(int quality)
{
    QAbstract3DGraph::ShadowQuality sq = QAbstract3DGraph::ShadowQuality(quality);
    m_graph->setShadowQuality(sq);
}

void ScatterDataModifier::setBackgroundEnabled(int enabled)
{
    m_graph->activeTheme()->setBackgroundEnabled((bool)enabled);
}

void ScatterDataModifier::setGridEnabled(int enabled)
{
    m_graph->activeTheme()->setGridEnabled((bool)enabled);
}
//! [8]

void ScatterDataModifier::toggleItemCount()
{
    if (m_itemCount == numberOfItems) {
        m_itemCount = lowerNumberOfItems;
        m_curveDivider = lowerCurveDivider;
    } else {
        m_itemCount = numberOfItems;
        m_curveDivider = curveDivider;
    }
    m_graph->seriesList().at(0)->dataProxy()->resetArray(0);
    addData();
}

QVector3D ScatterDataModifier::randVector()
{
    return QVector3D(
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f,
                (float)(rand() % 100) / 100.0f - (float)(rand() % 100) / 100.0f,
                (float)(rand() % 100) / 2.0f - (float)(rand() % 100) / 2.0f);
}

void ScatterDataModifier::setInitValue(float x, float y, float z)
{
    this->x_init = x;
    this->y_init = y;
    this->z_init = z;
}
