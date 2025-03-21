#pragma once
#include <iostream>

#include "../back/facade.h"

namespace s21 {
class Control {
 private:
  Facade* ptrFac;

 public:
  explicit Control(Facade* ptr);
  std::vector<Vertex> getVertixes();
  std::vector<Edge> getEdges();
  std::vector<unsigned int> getIndices();
  void load(const std::string& path);
  void scale(int size);
  void move(float x, float y, float z);
  void rotate(float horizontal, float vertical);
  std::vector<Point3D> mode(float width, float height, bool isPerspective);
};
}  // namespace s21