/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
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

#include "widget.h"
#include "xyseriesiodevice.h"
#include "ui_audiorecorder.h"

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioInput>

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QTimer>

#include <QtWidgets/QVBoxLayout>

QT_CHARTS_USE_NAMESPACE

Widget::Widget(const QAudioDeviceInfo &deviceInfo, QWidget *parent) :
    QWidget(parent),
    m_chart(new QChart),
    m_series(new QLineSeries)
{

    QChartView *chartView = new QChartView(m_chart);
    chartView->setMinimumSize(600, 300); // changer la taille de l'audio record
    m_chart->addSeries(m_series);
    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, XYSeriesIODevice::sampleCount);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(-1, 1);
    axisY->setTitleText("Audio level");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    m_chart->legend()->hide();
    //m_chart->setTitle(XYSeriesIODevice::getMax());

   // QLabel *test = new QLabel;
   // test->setText()
    //test->setTitleText("Audio level");



    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(chartView);

    QAudioFormat formatAudio;
    formatAudio.setSampleRate(8000);
    formatAudio.setChannelCount(1);
    formatAudio.setSampleSize(8);
    formatAudio.setCodec("audio/pcm");
    formatAudio.setByteOrder(QAudioFormat::LittleEndian);
    formatAudio.setSampleType(QAudioFormat::UnSignedInt);

    m_audioInput = new QAudioInput(deviceInfo, formatAudio, this);
    m_device = new XYSeriesIODevice(m_series, this);
    m_device->open(QIODevice::WriteOnly); //écrire sur l'affichage

    m_audioInput->start(m_device); // demarre en utilisant les données donné par la sortie de l'input
    //TIMER
    QTimer *t = new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(UpdateTitle()));
    t->start(200);
}

void Widget::setStart(){
    this->m_audioInput->start();
}

void Widget::setPause(){
    this->m_audioInput->suspend();
}

void Widget::setStop(){
    this->m_audioInput->stop();
}

void Widget::UpdateTitle(){
    QString Max=m_device->getMax();
    QString Min=m_device->getMin();
    QString Moyenne=m_device->getMoyenne();
    m_chart->setTitle("Le maximum : "+Max+", le minimum : "+Min+", la moyenne : "+ Moyenne);
}

Widget::~Widget()
{
    m_audioInput->stop();
    m_device->close();

}
