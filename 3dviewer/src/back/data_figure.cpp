#include "data_figure.h"

#include <iostream>
namespace s21 {
Point3D::Point3D() : x(0), y(0), z(0), w(1) {}

Point3D::Point3D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
inline float Point3D::GetX() const { return x; }
float Point3D::GetW() const { return w; }
inline float Point3D::GetY() const { return y; }
inline float Point3D::GetZ() const { return z; }
inline void Point3D::SetX(float x) { this->x = x; }
inline void Point3D::SetY(float y) { this->y = y; }
inline void Point3D::SetZ(float z) { this->z = z; }
void Point3D::SetW(float w) { this->w = w; }

Vertex::Vertex(float x, float y, float z, unsigned int index) : _index(index) {
  Point3D tmp(x, y, z);
  this->_position = tmp;
}

inline void Vertex::Transform(const TransformMatrix &var) {
  _position = var * _position;
}

inline Point3D Vertex::GetPosition() const { return _position; }

unsigned int Vertex::GetIndex() const { return _index; }

inline bool Vertex::operator<(const Vertex &other) const {
  return _index < other._index;
}

inline bool Vertex::operator==(const Vertex &other) const {
  return _index == other._index;
}

Edge::Edge(Vertex &begin, Vertex &end) : _begin(begin), _end(end) {}

Edge::Edge(const Edge &var) : _begin(var._begin), _end(var._end) {}

Edge &Edge::operator=(const Edge &var) {
  _begin = var._begin;
  _end = var._end;
  return *this;
}
Vertex &Edge::GetBegin() const { return _begin; }

Vertex &Edge::GetEnd() const { return _end; }

bool Edge::operator<(const Edge &other) const {
  const Vertex &this_a1 = std::min(_begin, _end);
  const Vertex &this_a2 = std::max(_begin, _end);
  const Vertex &other_a1 = std::min(other._begin, other._end);
  const Vertex &other_a2 = std::max(other._begin, other._end);
  return this_a1 < other_a1 || (this_a1 == other_a1 && this_a2 < other_a2);
}

bool Edge::operator==(const Edge &other) const {
  return ((_begin == other._begin && _end == other._end) ||
          (_begin == other._end && _end == other._begin));
}

Figure::Figure() {}

Figure::Figure(std::vector<Vertex> vertices, std::vector<Edge> edges)
    : _vertices(vertices), _edges(edges) {}

const std::vector<Vertex> &Figure::GetVertices() const { return _vertices; }

const std::vector<Edge> &Figure::GetEdges() const { return _edges; }

const std::vector<unsigned int> &Figure::GetIndices() const { return _indices; }

Vertex &Figure::GetVertexRef(int index) { return _vertices[index]; }

void Figure::addVertices(const Vertex &vertices) {
  _vertices.push_back(vertices);
}

void Figure::addEdges(const Edge &edges) { _edges.push_back(edges); }

void Figure::addIndeces(const unsigned int &index) {
  _indices.push_back(index);
}

size_t Figure::GetVerticesSize() const { return _vertices.size(); }

size_t Figure::GetEdgesSize() const { return _edges.size(); }

void Figure::Transform(const TransformMatrix &var) {
  for (auto &vertex : _vertices) {
    vertex.Transform(var);
  }
}
std::vector<Point3D> Figure::GetPoints() const {
  std::vector<Point3D> res(_vertices.size());
  for (int i = 0; i < _vertices.size(); ++i) {
    res[i] = _vertices[i].GetPosition();
  }
  return res;
}

BoundingBox Figure::GetBoundingBox() const { return BoundingBox(_vertices); }

BoundingBox::BoundingBox(const std::vector<Vertex> &vertices) {
  min = vertices[0].GetPosition();
  max = vertices[0].GetPosition();
  for (auto &v : vertices) {
    Point3D point = v.GetPosition();
    if (point.GetX() < min.GetX()) min.SetX(point.GetX());
    if (point.GetY() < min.GetY()) min.SetY(point.GetY());
    if (point.GetZ() < min.GetZ()) min.SetZ(point.GetZ());
    if (point.GetX() > max.GetX()) max.SetX(point.GetX());
    if (point.GetY() > max.GetY()) max.SetY(point.GetY());
    if (point.GetZ() > max.GetZ()) max.SetZ(point.GetZ());
  }
}

BoundingBox::BoundingBox(const std::vector<BoundingBox> &boxes) {
  min = boxes[0].GetMin();
  max = boxes[0].GetMax();
  for (auto &b : boxes) {
    if (b.GetMin().GetX() < min.GetX()) min.SetX(b.GetMin().GetX());
    if (b.GetMin().GetY() < min.GetY()) min.SetY(b.GetMin().GetY());
    if (b.GetMin().GetZ() < min.GetZ()) min.SetZ(b.GetMin().GetZ());
    if (b.GetMax().GetX() > max.GetX()) max.SetX(b.GetMax().GetX());
    if (b.GetMax().GetY() > max.GetY()) max.SetY(b.GetMax().GetY());
    if (b.GetMax().GetZ() > max.GetZ()) max.SetZ(b.GetMax().GetZ());
  }
}

const Point3D BoundingBox::GetMin() const { return min; }

const Point3D BoundingBox::GetMax() const { return max; }

const Point3D BoundingBox::GetCenter() const {
  return Point3D((min.GetX() + max.GetX()) / 2, (min.GetY() + max.GetY()) / 2,
                 (min.GetZ() + max.GetZ()) / 2);
}

float BoundingBox::height() const { return std::abs(max.GetY() - min.GetY()); }
float BoundingBox::width() const { return std::abs(max.GetX() - min.GetX()); }
float BoundingBox::depth() const { return std::abs(max.GetZ() - min.GetZ()); }

Camera::Camera(float x, float y, float z)
    : _position_base(x, y, z), _position(x, y, z) {}

void Camera::SetPosition(const Point3D &var) { _position = var; }

void Camera::SetBounds(float zNear, float zFar) {
  this->zNear = zNear;
  this->zFar = zFar;
}
void Camera::SetScaleFactor(float factor) { scaleFactor = factor; }

float Camera::GetScaleNormalisedFactor() const { return scaleFactor / 100.0f; }

float Camera::GetViewAngle() const {
  return view_angle_max -
         (scaleFactor + 100) / 200 * (view_angle_max - view_angle_min);
}
Point3D Camera::GetPosition() const { return _position; }

float Camera::GetZNear() const { return zNear; }

float Camera::GetZFar() const { return zFar; }

void Camera::Transform(const TransformMatrix &var) {
  _position = var * _position_base;
}
}  // namespace s21