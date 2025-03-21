#include <iostream>

#include "facade.h"
using namespace s21;
int main(void) {
  FileReader rdr;
  Scene scn;
  Facade f(rdr, scn);
  f.LoadScene("../front/cube.obj");
  auto scene = f.GetScene();
  auto figure = scene.GetFigure(0);
  auto vertices = figure.GetPoints();
  auto index = figure.GetIndices();
  for (auto it = vertices.begin(); it != vertices.end(); ++it) {
    std::cout << it->GetX() << " " << it->GetY() << " " << it->GetZ()
              << std::endl;
  }
  for (auto it = index.begin(); it != index.end(); ++it) {
    std::cout << *it << " ";
  }
  
}