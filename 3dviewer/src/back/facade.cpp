#include "facade.h"

#include <iostream>
namespace s21 {
FacadeOperationResult::FacadeOperationResult()
    : _errorMessage("SUCCESS"), _success(true) {}

FacadeOperationResult::FacadeOperationResult(std::string errorMessage)
    : _errorMessage(errorMessage), _success(false) {}

std::string FacadeOperationResult::GetErrorMessage() const {
  return _errorMessage;
}

bool FacadeOperationResult::isSuccess() const { return _success; }

void FacadeOperationResult::SetErrorMessage(const std::string &msg) {
  _errorMessage = msg;
}

void FacadeOperationResult::SetResult(const bool &var) { _success = var; }

FacadeTransformedVertex::FacadeTransformedVertex(
    const std::vector<Point3D> &var, const std::vector<unsigned int> &indices)
    : _vertices(var), _indices(indices) {}

FacadeTransformedVertex::FacadeTransformedVertex(
    const FacadeTransformedVertex &var)
    : _vertices(var._vertices), _indices(var._indices) {}

FacadeTransformedVertex &FacadeTransformedVertex::operator=(
    const FacadeTransformedVertex &var) {
  _vertices = var._vertices;
  return *this;
}
std::vector<Point3D> &FacadeTransformedVertex::GetVertices() {
  return _vertices;
}

const std::vector<Point3D> &FacadeTransformedVertex::GetVertices() const {
  return _vertices;
}

const std::vector<unsigned int> &FacadeTransformedVertex::GetIndices() const {
  return _indices;
}

Facade::Facade(FileReader reader, Scene var)
    : _fileReader(reader), _scene(var) {}

Scene Facade::GetScene() const { return _scene; }

FacadeOperationResult Facade::MoveScene(float x_n, float y_n, float z_n) {
  BoundingBox box = _scene.getBoundingBox();
  float x = x_n / 100.0f * _scene.getSize();
  float y = y_n / 100.0f * _scene.getSize();
  float z = z_n / 100.0f * _scene.getSize();

  auto mt = TransformMatrixBuilder::CreateMoveMatrix(x, y, z);
  _scene.setTransformation(mt);
  return FacadeOperationResult();
}

FacadeOperationResult Facade::RotateScene(float x, float y, float z) {
  auto mt = TransformMatrixBuilder::CreateRotationMatrix(
      Convert::toRad(x), Convert::toRad(y), Convert::toRad(z));

  _scene.TransformCamera(mt);

  return FacadeOperationResult();
}

FacadeOperationResult Facade::ScaleScene(float size) {
  // auto mt = TransformMatrixBuilder::CreateScaleMatrix(size, size, size);
  // _scene.TransformCamera(mt);
  _scene.zoomCamera(size);
  return FacadeOperationResult();
}

FacadeTransformedVertex Facade::DrawScene(int view_width, int view_height,
                                          bool perspective) {
  TransformMatrix mt_proj;
  const Camera &cam = _scene.GetCamera();
  float aspect = (float)view_width / (float)view_height;
  if (perspective) {
    mt_proj = TransformMatrixBuilder::CreatePerspectiveMatrix(
        Convert::toRad(cam.GetViewAngle()), aspect, cam.GetZNear(),
        cam.GetZFar());
  } else {
    float w = _scene.getSize() * 2.0f * (1.0f - cam.GetScaleNormalisedFactor());
    float h = _scene.getSize() / aspect * 2.0f *
              (1.0f - cam.GetScaleNormalisedFactor());
    mt_proj = TransformMatrixBuilder::CreateOrthoMatrix(w, h, cam.GetZNear(),
                                                        cam.GetZFar());
  }
  auto mt_view = TransformMatrixBuilder::CreateViewMatrix(cam.GetPosition(),
                                                          _scene.GetCenter());
  auto mt_scene_move = _scene.getTransformation();
  auto mt = mt_proj * mt_scene_move * mt_view;
  auto figure = _scene.GetFigure(0);

  FacadeTransformedVertex res(figure.GetPoints(), figure.GetIndices());
  auto &res_vertices = res.GetVertices();

  const int numVert = res_vertices.size();
  const int numThreads = numVert / 300000 + 1;
  const int blockSize = numVert / numThreads;

  auto calc_lambda = [&](int start, int end) {
    for (int i = start; i < end; i++) {
      res_vertices[i] = mt * res_vertices[i];
    }
  };
  std::vector<std::thread> threads;
  for (int i = 0; i < numThreads; i++) {
    int start = i * blockSize;
    int end = (i == numThreads - 1) ? numVert : start + blockSize;
    threads.emplace_back(calc_lambda, start, end);
  }

  for (auto &thread : threads) {
    thread.join();
  }
  return res;
}

FacadeOperationResult Facade::LoadScene(const std::string &path) {
  FacadeOperationResult result;
  try {
    _scene = _fileReader.ReadScene(path.c_str());
  } catch (const std::exception &e) {
    result.SetResult(false);
    result.SetErrorMessage("File isn't existing");
  }
  return result;
}
}  // namespace s21
