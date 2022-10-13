#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QtUiTools>
#include <QVBoxLayout>

#include <iostream>
#include <filesystem>
#include <thread>

#include "plot2d.h"

static QWidget *loadUiFile(QWidget *parent, const std::string& path)
{
  QFile file(path.c_str());
  file.open(QIODevice::ReadOnly);

  QUiLoader loader;
  return loader.load(&file, parent);
}

int main(int argc, char **argv)
{
  QApplication app (argc, argv);
  QWidget *ui = loadUiFile(nullptr, "../src/ui/main.ui");
  
  const auto layout = ui->findChild<QVBoxLayout*>("layout");
  
  QPushButton *button1 = new QPushButton("asd");
  QPushButton *button2 = new QPushButton("asdasd");
  layout->addWidget(button1);
  layout->addWidget(button2);
  gui::PlotWidget* plot = new gui::PlotWidget(nullptr, "xlabel", "ylabel", "title");

  layout->addWidget(plot);
  ui->show();
  
  using namespace std::chrono_literals;
  auto lambda = [](gui::PlotWidget *widget){
    int x = 3;
      gui::PlotWidget::PlotData data = {{1,2},{2,5},{3,4}};
      widget->UpdateXData(data);
      std::this_thread::sleep_for(1000ms);
      data.push_back({4,4});
      data.push_back({5,7});
      widget->UpdateXData(data);
      std::this_thread::sleep_for(1000ms);
  };
  std::thread t1(lambda, plot);
  return app.exec();
}