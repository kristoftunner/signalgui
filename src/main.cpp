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
      widget->GenerateDataFromSource();
      std::this_thread::sleep_for(1000ms);
    }
  };
  
  std::thread t1(lambda, windowApp.GetPlotWidget());
  return app.exec();
}
