#include "grid.h"


//TODO: Make terminal states
Dynamics::Dynamics(int t0_x, int t0_y, int t1_x, int t1_y, int width, int height) :
                   m_t0_x(t0_x), m_t0_y(t0_y), m_t1_x(t1_x), m_t1_y(t1_y), m_width(width), m_height(height)
{
  m_dynamics.resize(m_width*m_height);
  for (int h=0; h < m_height; ++h) {
    for(int w=0; w < m_width; ++w) {
      computeDynamic(m_dynamics[h*m_width+w],w,h);
    }
  }
}

// Being at location: loc_x , loc_y , what are possible transitions
void Dynamics::computeDynamic(state_dynamic& dynstate, int loc_x, int loc_y)  
{
  // Default immediate reward is -1.0
  // for terminal state it is 10.0
  if ((loc_x == m_t0_x && loc_y == m_t0_y) || ((loc_x == m_t1_x) && (loc_y == m_t1_y))) {
    dynstate.m_reward = 10.0;
  } else { 
    dynstate.m_reward = -1.0;
  }

  // Left means neighbour location on left , with exception
  // of most left sectors (loc_x == 0)
  if (loc_x > 0) {
    dynstate.m_transitions[direction::left] = loc_y*m_width + (loc_x - 1);
  } else {
    dynstate.m_transitions[direction::left] = loc_y*m_width;
  }

  // Right means location of location on the right ,
  //  with exception of rightmost sectors (loc_x == m_width - 1)
  if (loc_x < m_width - 1) {
    dynstate.m_transitions[direction::right] = loc_y*m_width + loc_x + 1;
  } else {
    dynstate.m_transitions[direction::right] = loc_y*m_width + m_width - 1;
  }

  // Up means location of sector upper,
  //  with exception of uppermost sectors (loc_y == 0)
  if (loc_y > 0) {
    dynstate.m_transitions[direction::up] = (loc_y - 1)*m_width + loc_x;
  } else {
    dynstate.m_transitions[direction::up] = loc_x;
  }


  // Down means location of sector located below,
  // with exception of lowermost sectors (loc_y == m_height -1)
  if (loc_y < m_height - 1) {
    dynstate.m_transitions[direction::up] = (loc_y + 1)*m_width + loc_x;
  } else {
    dynstate.m_transitions[direction::up] = (m_height - 1)*m_width + loc_x;
  }
}


bool Dynamics::isStateTerminal(int i)
{
  // Get x and y coords from index of states
  int x = i%m_width;
  int y = i%m_height;

  if ((x == m_t0_x && y == m_t0_y) || (x == m_t1_x && y == m_t1_y)) {
    return true;
  }
  return false;
}


float Dynamics::getReward(int i)
{
  return m_dynamics[i].m_reward;
}


int Dynamics::getNextState(int curr, direction direct)
{
  return m_dynamics[curr].m_transitions[direct]; 
}


Policy::Policy(int num_states): m_env(0,0,3,3,4,4), m_policy_evaluation(num_states,0.0f)
{
  m_policy.resize(num_states);

  // Initial uniform policy
  for(auto& policy_state : m_policy) {
      policy_state.P_l = 0.25;
      policy_state.P_r = 0.25;
      policy_state.P_u = 0.25;
      policy_state.P_d = 0.25;
  }
}


float Policy::evaluateState(int i)
{
  // Get state reward
  float reward = m_env.getReward(i);
  // If terminal state then return reward immediatly and finish evaluation
  if (m_env.isStateTerminal(i) == false) {  
    // If not terminal then 
    // Evaluate next states
    reward += m_policy[i].P_l*this->evaluateState(m_env.getNextState(i,direction::left));    
    reward += m_policy[i].P_r*this->evaluateState(m_env.getNextState(i,direction::right));    
    reward += m_policy[i].P_u*this->evaluateState(m_env.getNextState(i,direction::up));    
    reward += m_policy[i].P_d*this->evaluateState(m_env.getNextState(i,direction::down));    
  } 
  
  return reward;
}


// compute the expected value of policy
void Policy::evaluate(void)
{
  // What is start state
  // For all states
  std::fill(m_policy_evaluation.begin(), m_policy_evaluation.end(), 0.0f);

  int num_states = m_policy.size();
  for (int i=0; i< num_states; ++i) {
    m_policy_evaluation[i] = this->evaluateState(i);
  }
}


Grid::Grid(QApplication& app, int num_states) : t0_x(0), t0_y(0), t1_x(3), m_num_states(num_states), 
                                                t1_y(3), m_policy(num_states)
{
  // Initial evaluation
  m_policy.evaluate();
}

void Grid::paintEvent(QPaintEvent * event)
{
    static const QPoint points[4] = {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };

    QRect rect(10, 20, 80, 60);

    qreal top_left_x = 100.0;
    qreal top_left_y = 100.0;
    qreal length = 400.0;
    int num_sectors = 4;
    qreal vskip = length/num_sectors;
    qreal hskip = length/num_sectors;

    QPainterPath path;
    for(int i=0; i <= num_sectors; ++ i) {
      path.moveTo(top_left_x, top_left_y + i*vskip);
      path.lineTo(top_left_x + length, top_left_y + i*vskip);

      path.moveTo(top_left_x + hskip*i, top_left_y);
      path.lineTo(top_left_x +  hskip*i, top_left_y + length );
    }

    // Fill terminal states
    path.addRect(top_left_x + t0_x*vskip, top_left_y + t0_y*hskip,vskip,hskip);
    path.addRect(top_left_x + t1_x*vskip, top_left_y + t1_y*hskip,vskip,hskip);


    QPainter painter(this);
    painter.setPen(QColor(0,0,0));
    //QLinearGradient myGradient;
    QBrush brush(QColor(255,255,0)); 
    //QBrush brush(myGradient); 
    painter.setBrush(brush);
    painter.drawPath(path);
    ///int startAngle = 20 * 16;
    //int arcLength = 120 * 16;
}


void Grid::rundp(void)
{
  // Call policy iteration
  // Call polocy evaluation
  // Update drawing area
}
