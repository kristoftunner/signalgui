#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QtUiTools>
#include <QVBoxLayout>

#include <iostream>
#include <filesystem>
#include <thread>

#include "widget.h"

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
  Widget *plot = new Widget;
  layout->addWidget(plot);
  ui->show();
  
  using namespace std::chrono_literals;
  auto lambda = [](QLineSeries *series){
    int x = 3;
    while(true)
    {
      std::this_thread::sleep_for(1000ms);
      series->append(x++, 6);
      series->append(x++, 4);
      std::this_thread::sleep_for(1000ms);
      series->append(x++, 1);
      series->append(x++, 2);
    }
  };
  std::thread t1(lambda, plot->GetSeriesData());
  return app.exec();
}