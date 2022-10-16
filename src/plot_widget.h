#pragma once

#include "core.h"

#include <qt5/QtCharts/QtCharts>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtCharts/QLineSeries>
#include <qt5/QtCharts/QValueAxis>
#include <kfr/base.hpp>

namespace gui
{

using PlotData = std::vector<std::pair<float,float>>;
/**
 * @brief collection of digital signal generator function and storage for signals
 * 
 */
class SignalGenerator
{
public:
  enum class SignalType
  {
    Unknown, Sine, Cosine, Sawtooth, Square, Triangle
  };
  using ComplexSignalType = kfr::univector<kfr::complex<kfr::fbase>,100>;  
public:
  SignalGenerator() = default;
  ComplexSignalType GenerateSine(const float phi,const  float frequency, const int N);
  PlotData GenerateCosine(float phi, float frequency, int N);
  PlotData GenerateSawTooth(float phi, float frequency, int N);
  PlotData GenerateTriangle(float phi, float frequency, int N);
};

/**
 * PlotWidget class should abstract all the Qt internal away
*/
class PlotWidget : public QWidget
{
public:
  PlotWidget(QWidget *parent, const std::string xLabel, const std::string yLabel, const std::string title);
  void SetXAxisRange(int leftBound, int rigthBound);
  void SetYAxisRange(int lowerBound, int upperBound);
  void ReplacePlotData(const PlotData& data);
  const PlotData GetPlotData() const;
  void GenerateDataFromSource(const SignalGenerator::SignalType& type); 
  void SetSignalGenerator(Ref<SignalGenerator> generator){m_signalSource = generator;}

private:
  Ref<SignalGenerator> m_signalSource;
  QLineSeries *m_series;  
  QChart *m_chart;
  QValueAxis *m_axisX, *m_axisY;
  int m_leftBound, m_rightBound, m_lowerBound, m_upperBound;
};

}// namespace gui