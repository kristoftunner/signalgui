#pragma once

#include "plot_widget.h"
#include <qt5/QtCore/QObject>
#include <qt5/QtWidgets/QComboBox>

namespace gui
{

class Application : public QObject
{
Q_OBJECT
public:
  Application(QWidget *parent = nullptr);
  ~Application();
  PlotWidget* GetPlotWidget(){return m_plot;}

signals:
  void SignalSourceSelected(SignalGenerator::SignalType type);

public slots:
  void UpdateSignalSource(int index);

private:
  PlotWidget* m_plot;
  QComboBox* m_signalSelector;
};

} // namespace gui
