#include "control.h"
namespace s21 {
Control::Control(Facade* ptr) : ptrFac(ptr) {}

std::vector<Vertex> Control::getVertixes() {
  auto scene = ptrFac->GetScene();
  auto figure = scene.GetFigure(0);
  return figure.GetVertices();
}
std::vector<Edge> Control::getEdges() {
  auto scene = ptrFac->GetScene();
  auto figure = scene.GetFigure(0);
  return figure.GetEdges();
}
std::vector<unsigned int> Control::getIndices() {
  auto scene = ptrFac->GetScene();
  auto figure = scene.GetFigure(0);
  return figure.GetIndices();
}
void Control::load(const std::string& path) { ptrFac->LoadScene(path); }
void Control::scale(int size) { ptrFac->ScaleScene(size); }
void Control::move(float x, float y, float z) { ptrFac->MoveScene(x, y, z); }
void Control::rotate(float horizontal, float vertical) {
  ptrFac->RotateScene(horizontal, vertical, 0);
}
std::vector<Point3D> Control::mode(float width, float height,
                                   bool isPerspective) {
  auto transformedVert = ptrFac->DrawScene(width, height, isPerspective);
  std::vector<Point3D> points = transformedVert.GetVertices();
  return points;
}
}  // namespace s21