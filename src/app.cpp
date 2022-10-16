#include "app.h"
#include "filesystem.hpp"

#include <QPushButton>
#include <QtUiTools>
#include <QVBoxLayout>
#include <cassert>
#include <iostream>

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
  m_signalSelector = ui->findChild<QComboBox*>("signalSelector");
  const auto splitter = ui->findChild<QSplitter*>("splitter");
  assert(layout != nullptr);
  assert(splitter != nullptr);
  assert(m_signalSelector != nullptr);
  
  m_plot = new gui::PlotWidget(nullptr, "xlabel", "ylabel", "title");

  Ref<SignalGenerator> signalSource;
  signalSource.reset(new SignalGenerator());
  m_plot->SetSignalGenerator(signalSource);

  m_signalSelector->addItem("Sine");
  m_signalSelector->addItem("Cosine");
  m_signalSelector->addItem("Sawtooth");
  m_signalSelector->addItem("Square");
  m_signalSelector->addItem("Triangle");

  splitter->setStretchFactor(0,1); // stretch of the signalSelector
  splitter->setStretchFactor(1,3); // stretch of the plot
  
  /* connect signal selector and plot widget signals*/
  QObject::connect(m_signalSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(UpdateSignalSource(int)));
  QObject::connect(this, SIGNAL(SignalSourceSelected(SignalGenerator::SignalType)), 
                   m_plot, SLOT(SelectSignalSource(SignalGenerator::SignalType)));

  /* set default signal source */
  emit SignalSourceSelected(SignalGenerator::SignalType::Sine);

  layout->addWidget(m_plot);
  ui->show();
}

Application::~Application()
{
  delete(m_plot);
}

void Application::UpdateSignalSource(int index)
{
  switch(index)
  {
    case 0: emit SignalSourceSelected(SignalGenerator::SignalType::Sine); break;
    case 1: emit SignalSourceSelected(SignalGenerator::SignalType::Cosine); break;
    case 2: emit SignalSourceSelected(SignalGenerator::SignalType::Sawtooth); break;
    case 3: emit SignalSourceSelected(SignalGenerator::SignalType::Square); break;
    case 4: emit SignalSourceSelected(SignalGenerator::SignalType::Triangle); break;
  } 
}

} // namespace gui
