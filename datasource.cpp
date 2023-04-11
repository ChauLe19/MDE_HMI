// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>

QT_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

DataSource::DataSource(QQuickView *appViewer, QObject *parent) :
    QObject(parent),
    m_appViewer(appViewer),
    m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    //  add the first point to prevent crashing
    QList<QPointF> initpoints;
    initpoints.reserve(0);
    initpoints.append(QPointF(0, 0));
    m_data.append(initpoints);
    m_data.append(initpoints);
}

void DataSource::update(QAbstractSeries *series)
{
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        m_index++;
        if (m_index > m_data.count() - 1)
            m_index = 0;

        QList<QPointF> points = m_data.at(m_index);
        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(points);
    }
}


void DataSource::addVoltage(double voltageValue)
{
    static const int xMax = 100;
    static int x = -1;
    static QList<QPointF> points;
    points.reserve(xMax);
    x++;
    points.append(QPointF(x, voltageValue));
    m_data.replace(0, points);
}

void DataSource::addCurrent(double currentValue)
{
    static const int xMax = 100;
    static int x = -1;
    static QList<QPointF> points;
    points.reserve(xMax);
    x++;
    points.append(QPointF(x, currentValue/2)); // only for testing
    m_data.replace(1, points);
}

int DataSource::getLastXPos()
{
    return (*(m_data.at(0).end()-1)).toPoint().x();
}
