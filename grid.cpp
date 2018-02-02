#include "grid.h"

Dynamics::Dynamics(int t0_x, int t0_y, int t1_x, int t1_y, int width, int height) :
                   m_width(width), m_height(height)
{
  m_dynamics.resize(m_width*m_height);
  for (int h=0; h < m_height; ++h) {
    for(int w=0; w < m_width; ++w) {
      getDynamic(m_dynamics[h*m_width+w],w,h);
    }
  }
}


void Dynamics::getDynamic(state_dynamic& dynstate, int loc_x, int loc_y)  
{
  // Default immediate reward is -1.0
  // for terminal state it is 10.0
  if ((loc_x == 0 && loc_y == 0) || ((loc_x == m_width - 1) && (loc_y == m_height - 1))) {
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


Grid::Grid(QApplication& app) : t0_x(0), t0_y(0), t1_x(3), t1_y(3), m_env(0,0,3,3,4,4)
{
  // Policy initialization
  // Sectors from 0 - 15
  policy.resize(num_states);
  for(auto& policy_state : policy) {
      policy_state.P_l = 0.25;
      policy_state.P_r = 0.25;
      policy_state.P_u = 0.25;
      policy_state.P_d = 0.25;
  }
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



    //path.cubicTo(80, 0, 50, 50, 80, 80);

    QPainter painter(this);
    painter.setPen(QColor(0,0,0));
    painter.drawPath(path);
    ///int startAngle = 20 * 16;
    //int arcLength = 120 * 16;
}
