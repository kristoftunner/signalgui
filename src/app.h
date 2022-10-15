#pragma once


#include "plot2d.h"

namespace gui
{

class Application
{
public:
  Application(QWidget *parent = nullptr);
  ~Application();
  PlotWidget* GetPlotWidget(){return m_plot;}

private:
  PlotWidget *m_plot;
};

} // namespace gui
