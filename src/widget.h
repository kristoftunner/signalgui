#pragma once

#include "qt5/QtCharts/QtCharts"
#include "qt5/QtWidgets/QWidget"
#include "qt5/QtCharts/QLineSeries"

class Widget : public QWidget
{
public:
    Widget(QWidget *parent = nullptr);
    virtual ~Widget() override;

private:
    QChart *m_chart;
    QLineSeries *m_series;
};
