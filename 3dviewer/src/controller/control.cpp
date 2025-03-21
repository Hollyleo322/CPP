#include "control.h"
namespace s21 {
Control::Control(Facade* ptr) : _ptrFac(ptr) {}

std::vector<Point3D> Control::getPoints() {
  return _ptrFac->DrawScene(_width, _height, _isPerspective);
}
std::vector<unsigned int> Control::getIndices() {
  auto scene = _ptrFac->GetScene();
  auto figure = scene.GetFigure(0);
  return figure.GetIndices();
}
int Control::getEdgesCount() {
  auto scene = _ptrFac->GetScene();
  auto figure = scene.GetFigure(0);
  return figure.GetEdges().size();
}
int Control::getVerticesCount() {
  auto scene = _ptrFac->GetScene();
  auto figure = scene.GetFigure(0);
  return figure.GetVertices().size();
}

void Control::load(const std::string& path) { _ptrFac->LoadScene(path); }
void Control::scale(int size) { _ptrFac->ScaleScene(size); }
void Control::move(float x, float y, float z) { _ptrFac->MoveScene(x, y, z); }
void Control::rotate(float horizontal, float vertical) {
  _ptrFac->RotateScene(horizontal, vertical, 0);
}
void Control::mode(float width, float height, bool isPerspective) {
  _width = width;
  _height = height;
  _isPerspective = isPerspective;
}
}  // namespace s21