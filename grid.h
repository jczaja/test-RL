#ifndef __GRID__
#define  __GRID__
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QtGui>
#include <vector>
#include <map>


enum class direction {left, right, up, down};

class Dynamics {
 
  struct state_dynamic
  {
    std::map <direction,int> m_transitions;
    float m_reward;
  };
 
  public:
    Dynamics(int t0_x, int t0_y, int t1_x, int t1_y, int width, int height);
  private:
    void computeDynamic(state_dynamic& dynstate, int loc_x, int loc_y);  
  private:
    int m_t0_x, m_t0_y, m_t1_x, m_t1_y;
    int m_width;
    int m_height;
    std::vector<state_dynamic> m_dynamics;
};


class Grid : public QWidget
{
  Q_OBJECT

  public:
  //// Probability that from
   //struct {
      
   //}Dynamic;


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
  int t0_x,t0_y,t1_x,t1_y;  // terminal states
  Dynamics m_env;
  QTextEdit *textEdit;
  QPushButton *quitButton;
  const int num_states = 16;
  std::vector<state> policy; 
};
#endif
