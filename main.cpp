#include <QApplication>
#include <grid.h>
#include <memory>


int main(int argv, char **args)
{
  QApplication app(argv, args);

  std::unique_ptr<Grid> siatka(new Grid(app,16)); 
  siatka->show();
  siatka->rundp();

  return app.exec();
}

