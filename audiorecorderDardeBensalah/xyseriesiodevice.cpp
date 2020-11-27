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

#include "xyseriesiodevice.h"
#include <QLabel>
#include <QtCharts/QXYSeries>
#include <iostream>
#include <QtDebug>

XYSeriesIODevice::XYSeriesIODevice(QXYSeries *series, QObject *parent) :
    QIODevice(parent),
    m_series(series)
{

}

qint64 XYSeriesIODevice::readData(char *data, qint64 maxSize) // on ne l'utilise pas
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

double moyenne = 0.0;

double total = 0.0;



qint64 XYSeriesIODevice::writeData(const char *data, qint64 maxSize) // on envoie les données d buffer au graphique
{
    static const int resolution = 4;

    if (m_buffer.isEmpty()) {
        m_buffer.reserve(sampleCount);
        for (int i = 0; i < sampleCount; ++i)
            m_buffer.append(QPointF(i, 0));
    }

    int start = 0;
    const int availableSamples = int(maxSize) / resolution;
    if (availableSamples < sampleCount) {
        start = sampleCount - availableSamples;
        for (int s = 0; s < start; ++s)
            m_buffer[s].setY(m_buffer.at(s + availableSamples).y());
    }

    for (int s = start; s < sampleCount; ++s, data += resolution)
    m_buffer[s].setY(qreal(uchar(*data) -128) / qreal(128));


    m_series->replace(m_buffer);

    return (sampleCount - start) * resolution;
}

QString XYSeriesIODevice::getMax()
{ double max = 0.0;
    for (auto elem : m_buffer)
    {
        if (elem.y() > max) max=elem.y();
      //  qDebug()<<max;

    }
   QString maxString = QString::number(max,'f',2);
    //qDebug()<<maxString;
    return maxString;
}

QString XYSeriesIODevice::getMin()
{ double min = 0.0;
    for (auto elem : m_buffer)
    {
        if (elem.y() > min) min=elem.y();
    }
   QString minString = QString::number(min,'f',2);
    return minString;
}

QString XYSeriesIODevice::getMoyenne()
{
    for (auto elem : m_buffer)
    {
        total+=qAbs(elem.y());
        moyenne=total/(m_buffer.length());
    }

   QString moyenneString = QString::number(moyenne,'f',2);
    return moyenneString;
}

