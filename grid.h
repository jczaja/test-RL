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
    bool isStateTerminal(int i);
    float getReward(int i);
  private:
    void computeDynamic(state_dynamic& dynstate, int loc_x, int loc_y);  
  private:
    int m_t0_x, m_t0_y, m_t1_x, m_t1_y;
    int m_width;
    int m_height;
    std::vector<state_dynamic> m_dynamics;
};


class Policy {
  struct state {
    float P_l;
    float P_r;
    float P_u;
    float P_d;
  };
  public:
    Policy(int num_states);
    void evaluate(void);
  private:
    float evaluateState(int i);

  private:
    Dynamics m_env;
    std::vector<state> m_policy;
    std::vector<float> m_policy_evaluation;
};

class Grid : public QWidget
{
  Q_OBJECT

  public:
  //// Probability that from
   //struct {
      
   //}Dynamic;


  

  Grid(QApplication& app, int num_states);
  void rundp(void);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  int t0_x,t0_y,t1_x,t1_y;  // terminal states
  const int m_num_states;
  Policy m_policy;
  QTextEdit *textEdit;
  QPushButton *quitButton;
};
#endif
