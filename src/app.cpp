#include "app.h"
#include "filesystem.hpp"

#include <QPushButton>
#include <QtUiTools>
#include <QVBoxLayout>
#include <cassert>

static QWidget *loadUiFile(QWidget *parent, const std::string& path)
{
  QFile file(path.c_str());
  file.open(QIODevice::ReadOnly);

  QUiLoader loader;
  return loader.load(&file, parent);
}

namespace gui
{

Application::Application(QWidget *parent)
{
  QWidget *ui = loadUiFile(nullptr, FileSystem::GetInstance().GetAbsolutePath("src/ui/main.ui"));
  
  const auto layout = ui->findChild<QHBoxLayout*>("layout");
  assert(layout != nullptr);
  
  QPushButton *button1 = new QPushButton("asd");
  QPushButton *button2 = new QPushButton("asdasd");
  layout->addWidget(button1);
  layout->addWidget(button2);
  m_plot = new gui::PlotWidget(nullptr, "xlabel", "ylabel", "title");

  layout->addWidget(m_plot);
  ui->show();
}

Application::~Application()
{
  delete(m_plot);
}

} // namespace gui
