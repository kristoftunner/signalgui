#include "plot_widget.h"

#include <qt5/QtCore/QList>
#include <cstdlib>
#include <iostream>

namespace gui
{

SignalGenerator::ComplexSignalType SignalGenerator::GenerateSine(const float phi, const float frequency, const int N)
{
  const float T = 1 / frequency;
  ComplexSignalType x  = kfr::sin(kfr::linspace(phi, kfr::c_pi<float, 2> * T * N, N));
  return x;
}

PlotData SignalGenerator::GenerateCosine(float phi, float frequency, int N)
{

}

PlotData SignalGenerator::GenerateSawTooth(float phi, float frequency, int N)
{

}

PlotData SignalGenerator::GenerateTriangle(float phi, float frequency, int N)
{

}

PlotWidget::PlotWidget(QWidget *parent, const std::string xLabel, const std::string yLabel, const std::string title) :
  QWidget(parent),
  m_chart(new QtCharts::QChart),
  m_series(new QtCharts::QLineSeries),
  m_lowerBound(-10.0f), m_upperBound(10.0f), m_leftBound(0), m_rightBound(10)
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

void PlotWidget::ReplacePlotData(const PlotData& plotData)
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

const PlotData PlotWidget::GetPlotData() const
{
  const QList<QPointF> points = m_series->points();
  PlotData data;
  for(const auto& point : points)
  {
    data.push_back({point.x(), point.y()});
  }

  return data;
}

void PlotWidget::SelectSignalSource(SignalGenerator::SignalType type)
{
  m_signalType = type;
}

void PlotWidget::GenerateDataFromSource()
{
  const float phi = static_cast <float> (rand()) / (static_cast <float>(RAND_MAX) / kfr::c_pi<float>);
  SignalGenerator::ComplexSignalType signal; 
  switch(m_signalType)
  {
    case SignalGenerator::SignalType::Sine:
    {
      signal = m_signalSource->GenerateSine(phi, 10, 100); 
      break;  
    }
    //case SignalGenerator::SignalType::Cosine signal = m_signalSource->GenerateCosine(phi, 10, 100); break;  
    //case SignalGenerator::SignalType::Sawtooth: signal = m_signalSource->GenerateSawTooth(phi, 10, 100); break;  
    //case SignalGenerator::SignalType::Triangle: signal = m_signalSource->GenerateTriangle(phi, 10, 100); break;  
    default: break;
  }
    
  /* copy the real component into QList and replace the series */
  QList<QPointF> data;
  for(int i = 0; i < signal.size(); i++)
  {
    data.push_back({static_cast<qreal>(i), static_cast<qreal>(signal[i].real())});
  }
  m_series->replace(data);
} 

} // namespace gui
