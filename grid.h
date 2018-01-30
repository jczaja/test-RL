#ifndef __GRID__
#define  __GRID__
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QtGui>

class Grid : public QWidget
{
  Q_OBJECT

  public:
    Grid(QApplication& app);

  private:
      QTextEdit *textEdit;
      QPushButton *quitButton;
  };
#endif
