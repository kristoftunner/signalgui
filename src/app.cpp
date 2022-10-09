#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QtUiTools>
#include <QtUiTools>
#include <QVBoxLayout>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>

#include <QLineSeries>

#include <string>
#include <iostream>
#include <filesystem>


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
  QWidget window;
  std::cout << std::filesystem::current_path() << std::endl;
  QWidget *ui = loadUiFile(&window, "../src/ui/app.ui");
  
  const auto layout = ui->findChild<QVBoxLayout*>("layout");
  Widget *plot = new Widget;
  layout->addWidget(plot);

  window.show();
  return app.exec();
}