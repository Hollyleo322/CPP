#include "scene.h"
namespace s21 {

Scene::Scene(const std::vector<Figure> &figures, const Camera &camera)
    : _figures(figures), _camera(camera) {
  std::vector<BoundingBox> boxes;
  for (auto &figure : _figures) {
    boxes.push_back(figure.GetBoundingBox());
  }
  _boundingBox = BoundingBox(boxes);
}

Scene::Scene(const Scene &var) {
  if (var._figures.size() != 0) {
    _figures.clear();
    auto figu = var.GetFigure(0);
    _figures.push_back(figu);
    _camera = var._camera;
    _center = var._center;
    _boundingBox = var._boundingBox;
    _transformMatrix = var._transformMatrix;
  }
}
Scene &Scene::operator=(const Scene &var) {
  if (this != &var) {
    if (var._figures.size() != 0) {
      _figures.clear();
      auto figu = var.GetFigure(0);
      _figures.push_back(figu);
      _camera = var._camera;
      _center = var._center;
      _boundingBox = var._boundingBox;
      _transformMatrix = var._transformMatrix;
    }
  }
  return *this;
}

const std::vector<Figure> &Scene::GetFigures() const { return _figures; }

Figure Scene::GetFigure(int index) const { return _figures[index]; }

void Scene::setFigures(const Figure &var) {
  _figures.push_back(var);
  std::vector<BoundingBox> boxes;
  for (auto &figure : _figures) {
    boxes.push_back(figure.GetBoundingBox());
  }
  _boundingBox = BoundingBox(boxes);
}

void Scene::setCenter(Point3D center) {
  _center = Point3D(0, center.GetY(), 0);
}

Point3D Scene::GetCenter() const { return _center; }

Camera Scene::GetCamera() const { return _camera; }

void Scene::setCamera(const Camera &var) { _camera = var; }

void Scene::TransformFigures(const TransformMatrix &var) {
  for (auto &figure : _figures) {
    figure.Transform(var);
  }
}

void Scene::zoomCamera(float scaleFactor) {
  if (scaleFactor < -100) {
    scaleFactor = -100;
  } else if (scaleFactor > 100) {
    scaleFactor = 100;
  }
  _camera.SetScaleFactor(scaleFactor);
}

void Scene::TransformCamera(const TransformMatrix &var) {
  _camera.Transform(var);
}

float Scene::getSize() const {
  float res = _boundingBox.width();
  if (_boundingBox.height() > res) {
    res = _boundingBox.height();
  }
  if (_boundingBox.depth() > res) {
    res = _boundingBox.depth();
  }
  return res;
}

void Scene::setTransformation(const TransformMatrix &var) {
  _transformMatrix = var;
}

TransformMatrix Scene::getTransformation() const { return _transformMatrix; }

BoundingBox Scene::getBoundingBox() const { return _boundingBox; }

}  // namespace s21
