#pragma once

#include "core.h"

#include <qt5/QtCharts/QtCharts>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCharts/QLineSeries>
#include <qt5/QtCharts/QValueAxis>

namespace gui
{

/**
 * PlotWidget class should abstract all the Qt internal away
*/
class PlotWidget : public QWidget
{
public:
  using PlotData = std::pair<float,float>;
public:
  PlotWidget(QWidget *parent, const std::string& xLabel, const std::string& yLabel, const std::string& title);
  void SetXAxisRange(int leftBound, int rigthBound);
  void SetYAxisRange(int lowerBound, int upperBound);
  void UpdateXData(const PlotData& data);
  const PlotData& GetXData() const; 

private:
  QLineSeries *m_series;  
  QChart *m_chart;
  QValueAxis *m_axisX, *m_axisY;
  int m_leftBound, m_rightBound, m_lowerBound, m_upperBound;
};

}// namespace gui