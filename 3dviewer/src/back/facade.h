#pragma once
#include <string>
#include <thread>

#include "parser.h"
#include "scene.h"
#include "transform.h"

namespace s21 {
class FacadeOperationResult {
 public:
  FacadeOperationResult();
  FacadeOperationResult(std::string errorMessage);
  std::string GetErrorMessage() const;
  bool isSuccess() const;
  void SetErrorMessage(const std::string &msg);
  void SetResult(const bool &var);

 private:
  std::string _errorMessage;
  bool _success;
};

class FacadeTransformedVertex {
 public:
  FacadeTransformedVertex(const std::vector<Point3D> &var,
                          const std::vector<unsigned int> &indices);
  FacadeTransformedVertex(const FacadeTransformedVertex &var);
  FacadeTransformedVertex &operator=(const FacadeTransformedVertex &var);
  std::vector<Point3D> &GetVertices();
  const std::vector<Point3D> &GetVertices() const;
  const std::vector<unsigned int> &GetIndices() const;

 private:
  std::vector<Point3D> _vertices;
  const std::vector<unsigned int> _indices;
};

class Facade {
 public:
  Facade(FileReader reader, Scene var);
  Scene GetScene() const;
  FacadeTransformedVertex DrawScene(int view_width, int view_height,
                                    bool perspective = true);
  FacadeOperationResult LoadScene(const std::string &path);
  FacadeOperationResult MoveScene(float x, float y, float z);
  FacadeOperationResult RotateScene(float x_angle_deg, float y_angle_deg,
                                    float z_angle_deg);
  FacadeOperationResult ScaleScene(float size);

 private:
  FileReader _fileReader;
  Scene _scene;
};
}  // namespace s21