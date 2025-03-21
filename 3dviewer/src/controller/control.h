#pragma once
#include <iostream>

#include "../back/facade.h"

namespace s21 {
class Control {
 private:
  Facade* _ptrFac;
  int _width, _height;
  bool _isPerspective;

 public:
  explicit Control(Facade* ptr);
  std::vector<Point3D> getPoints();
  std::vector<unsigned int> getIndices();
  int getEdgesCount();
  int getVerticesCount();
  void load(const std::string& path);
  void scale(int size);
  void move(float x, float y, float z);
  void rotate(float horizontal, float vertical);
  void mode(float width, float height, bool isPerspective);
};
}  // namespace s21