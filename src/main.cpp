#include <QApplication>

#include <iostream>
#include <filesystem>
#include <thread>
#include <cstdlib>

#include "app.h"

int main(int argc, char **argv)
{
  QApplication app (argc, argv);
  gui::Application windowApp; 
  using namespace std::chrono_literals;
  auto lambda = [](gui::PlotWidget* widget){
    int x = 3;
    while(true)
    {
      widget->GenerateDataFromSource(gui::SignalGenerator::SignalType::Sine);
      std::this_thread::sleep_for(1000ms);
    }
    //gui::PlotData data = {{1,2},{2,5},{3,4}};
    //widget->ReplacePlotData(data);
    //std::this_thread::sleep_for(1000ms);
    //data.push_back({4,4});
    //data.push_back({5,7});
    //widget->ReplacePlotData(data);
    //std::this_thread::sleep_for(1000ms);
  };
  std::thread t1(lambda, windowApp.GetPlotWidget());
  return app.exec();
}
