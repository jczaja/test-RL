#ifndef __GRID__
#define  __GRID__
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QtGui>
#include <vector>

class Grid : public QWidget
{
  Q_OBJECT

  public:
  //// Probability that from
   //struct {
      
   //}Dynamic;


   //struct {
      //float P_l;
      //float P_r;
      //float P_u;
      //float P_d;
      //float Reward;   // Immediate reward
   //} sector;

  struct state {
    float P_l;
    float P_r;
    float P_u;
    float P_d;
  };
  

    Grid(QApplication& app);

protected:
    void paintEvent(QPaintEvent *event) override;

  private:
      QTextEdit *textEdit;
      QPushButton *quitButton;
      const int num_states = 16;
      std::vector<state> policy; 
  };
#endif
