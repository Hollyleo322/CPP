#pragma once
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>

#include "scene.h"
namespace s21 {
class BaseFileReader {
 public:
  virtual ~BaseFileReader() = default;

 protected:
  virtual Scene ReadScene(const char *path) = 0;
};

class FileReader : public BaseFileReader {
 public:
  Scene ReadScene(const char *path) override;

 private:
  void createCam(const float &maxX, const float &maxY, const float &maxZ,
                 Scene &result);
};
}  // namespace s21
