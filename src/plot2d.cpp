#include "plot2d.h"

#include <qt5/QtCore/QList>

namespace gui
{

PlotWidget::PlotWidget(QWidget *parent, const std::string xLabel, const std::string yLabel, const std::string title) :
  QWidget(parent),
  m_chart(new QtCharts::QChart),
  m_series(new QtCharts::QLineSeries),
  m_lowerBound(0), m_upperBound(10), m_leftBound(0), m_rightBound(10)
{
  QChartView *chartView = new QChartView(m_chart);
  m_chart->addSeries(m_series);
  m_axisX = new QValueAxis;
  m_axisX->setRange(m_leftBound, m_rightBound);
  m_axisX->setLabelFormat("%g");
  m_axisX->setTitleText(xLabel.c_str());
  m_axisY = new QValueAxis;
  m_axisY->setRange(m_lowerBound, m_upperBound);
  m_axisY->setTitleText(yLabel.c_str());
  m_chart->addAxis(m_axisX, Qt::AlignBottom);
  m_series->attachAxis(m_axisX);
  m_chart->addAxis(m_axisY, Qt::AlignLeft);
  m_series->attachAxis(m_axisY);
  m_chart->legend()->hide();
  m_chart->setTitle(title.c_str());

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(chartView);
}

void PlotWidget::SetXAxisRange(int leftBound, int rigthBound)
{
  m_leftBound = leftBound;
  m_rightBound = rigthBound;
  m_axisX->setRange(m_leftBound, m_rightBound);
}

void PlotWidget::SetYAxisRange(int lowerBound, int upperBound)
{
  m_lowerBound = lowerBound;
  m_upperBound = upperBound;
  m_axisY->setRange(m_lowerBound, m_upperBound);
}

void PlotWidget::UpdateXData(const PlotWidget::PlotData& plotData)
{
  // generate QList<QPointF>
  QList<QPointF> data;
  for(const auto& dataPoint : plotData)
  {
    data.push_back({dataPoint.first, dataPoint.second});
  }

  // update chart data
  m_series->replace(data);
}

const PlotWidget::PlotData PlotWidget::GetXData() const
{
  const QList<QPointF> points = m_series->points();
  PlotData data;
  for(const auto& point : points)
  {
    data.push_back({point.x(), point.y()});
  }

  return data;
}


} // namespace gui
