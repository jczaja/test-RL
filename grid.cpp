#include "grid.h"

Grid::Grid(QApplication& app)
{

  //QTextEdit *textEdit = new QTextEdit;
  //QPushButton *quitButton = new QPushButton("&Quit");

  //QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

  //QVBoxLayout *layout = new QVBoxLayout;
  //layout->addWidget(textEdit);
  //layout->addWidget(quitButton);

  //setLayout(layout);

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
