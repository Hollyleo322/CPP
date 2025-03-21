#pragma once
#include <vector>

#include "data_figure.h"
namespace s21 {
class Figure;
class Scene {
 private:
  std::vector<Figure> _figures;
  Camera _camera;
  Point3D _center;
  BoundingBox _boundingBox;
  TransformMatrix _transformMatrix =
      TransformMatrixBuilder::CreateIdentityMatrix();

 public:
  Scene() = default;
  Scene(const std::vector<Figure> &figures, const Camera &camera);
  Scene(const Scene &var);
  Scene &operator=(const Scene &var);
  ~Scene() = default;
  const std::vector<Figure> &GetFigures() const;
  Figure GetFigure(int index) const;
  void setFigures(const Figure &var);
  void setCenter(Point3D center);
  Point3D GetCenter() const;
  Camera GetCamera() const;
  void setCamera(const Camera &var);
  void zoomCamera(float size);
  void setTransformation(const TransformMatrix &var);
  TransformMatrix getTransformation() const;
  void TransformFigures(const TransformMatrix &var);
  void TransformCamera(const TransformMatrix &var);
  float getSize() const;
  BoundingBox getBoundingBox() const;
};
}  // namespace s21