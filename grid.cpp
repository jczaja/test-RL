#include "grid.h"

Grid::Grid(QApplication& app)
{

  QTextEdit *textEdit = new QTextEdit;
  QPushButton *quitButton = new QPushButton("&Quit");

  QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(textEdit);
  layout->addWidget(quitButton);

  setLayout(layout);

}
