#include "parser.h"

#include <chrono>
#include <iostream>

// Специализация std::hash внутри namespace std
namespace std {
template <>
struct hash<s21::Edge> {
  size_t operator()(const s21::Edge &e) const {
    return std::hash<int>()(e.GetBegin().GetIndex()) ^
           std::hash<int>()(e.GetEnd().GetIndex());
  }
};
}  // namespace std
namespace s21 {
Scene FileReader::ReadScene(const char *path) {
  std::ifstream file(path);
  Scene result;
  if (file.is_open()) {
    std::string line;
    std::set<Edge> edges_temp;
    Figure figure;
    unsigned int vIdx = 0;
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string type;
      iss >> type;

      if (type == "v") {
        float x, y, z;
        iss >> x >> y >> z;
        figure.addVertices(Vertex(x, y, z, vIdx));
        ++vIdx;
      }
    }
    file.clear();
    file.seekg(0);
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string type;
      iss >> type;
      if (type == "f") {
        std::vector<int> indices;
        std::string vertex;
        while (iss >> vertex) {
          int vIdx_f = std::stoi(vertex) - 1;
          indices.push_back(vIdx_f);
        }
        for (size_t i = 0; i < indices.size(); ++i) {
          int v1 = indices[i], v2 = indices[(i + 1) % indices.size()];
          edges_temp.insert(
              Edge(figure.GetVertexRef(v1), figure.GetVertexRef(v2)));
        }
      }
    }
    for (auto &edge : edges_temp) {
      figure.addEdges(edge);
      figure.addIndeces(edge.GetBegin().GetIndex());
      figure.addIndeces(edge.GetEnd().GetIndex());
    }

    BoundingBox box = figure.GetBoundingBox();
    Camera cam(0, box.GetCenter().GetY(), box.GetMax().GetZ() * 4);
    cam.SetBounds(1, box.GetMax().GetZ() * 10);
    result.setFigures(figure);
    result.setCamera(cam);
    result.setCenter(box.GetCenter());
    file.close();
  } else {
    throw std::exception();
  }
  return result;
}

void FileReader::createCam(const float &maxX, const float &maxY,
                           const float &maxZ, Scene &result) {
  (void)maxX;
  Camera cam(0, maxY, maxZ * 4);
  // cam.SetPosition(Point3D(0, maxY, maxZ * 4));
  cam.SetBounds(1, maxZ * 10);
  result.setCamera(cam);
}
}  // namespace s21