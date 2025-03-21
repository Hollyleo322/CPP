#pragma once
#include <vector>

#include "transform.h"
namespace s21 {
class TransformMatrix;

class Point3D {
 public:
  float GetX() const;
  float GetY() const;
  float GetZ() const;
  float GetW() const;
  void SetX(float x);
  void SetY(float y);
  void SetZ(float z);
  void SetW(float w);

  Point3D();
  Point3D(float x, float y, float z, float w = 1);
  ~Point3D() = default;

 private:
  float x;
  float y;
  float z;
  float w;
};
class SceneObject {
 public:
  virtual ~SceneObject() = default;

 protected:
  virtual void Transform(const TransformMatrix &var) = 0;
};

class Vertex : public SceneObject {
 public:
  Vertex() = default;
  Vertex(float x, float y, float z, unsigned int index);
  Point3D GetPosition() const;
  unsigned int GetIndex() const;
  void Transform(const TransformMatrix &var) override;
  bool operator<(const Vertex &other) const;
  bool operator==(const Vertex &other) const;

 private:
  Point3D _position;
  unsigned int _index;
};

class Edge {
 public:
  Edge() = default;
  Edge(Vertex &begin, Vertex &end);
  Edge(const Edge &var);
  Edge &operator=(const Edge &var);
  Vertex &GetBegin() const;
  Vertex &GetEnd() const;
  bool operator<(const Edge &other) const;
  bool operator==(const Edge &other) const;

 private:
  Vertex &_begin;
  Vertex &_end;
};

class BoundingBox {
 public:
  BoundingBox() = default;
  BoundingBox(const std::vector<Vertex> &vertices);
  BoundingBox(const std::vector<BoundingBox> &boxes);
  const Point3D GetMin() const;
  const Point3D GetMax() const;
  const Point3D GetCenter() const;
  float height() const;
  float width() const;
  float depth() const;

 private:
  Point3D min;
  Point3D max;
};

class Figure : public SceneObject {
 public:
  Figure();
  Figure(std::vector<Vertex> vertices, std::vector<Edge> edges);
  // Figure(const Figure &var);
  // Figure &operator=(const Figure &var);
  std::vector<Vertex> GetVertices() const;
  std::vector<Point3D> GetPoints();
  std::vector<Edge> GetEdges() const;
  const std::vector<unsigned int> &GetIndices() const;
  Vertex &GetVertexRef(int index);
  void addVertices(const Vertex &vertices);
  void addEdges(const Edge &edges);
  void addIndeces(const unsigned int &index);
  size_t GetVerticesSize() const;
  size_t GetEdgesSize() const;
  BoundingBox GetBoundingBox() const;
  void Transform(const TransformMatrix &var) override;

 private:
  std::vector<Vertex> _vertices;
  std::vector<unsigned int> _indices;
  std::vector<Edge> _edges;
};

class Camera : public SceneObject {
 public:
  Camera() = default;
  Camera(float x, float y, float z);
  void SetPosition(const Point3D &var);
  void SetBounds(float zNear, float zFar);
  void SetScaleFactor(float factor);
  float GetScaleNormalisedFactor() const;
  float GetViewAngle() const;
  Point3D GetPosition() const;
  float GetZNear() const;
  float GetZFar() const;
  void Transform(const TransformMatrix &var) override;

 private:
  Point3D _position_base;
  Point3D _position;
  float zNear;
  float zFar;
  float view_angle_min = 5.0f;
  float view_angle_max = 120.0f;
  float scaleFactor = 0.0f;
};
}  // namespace s21
