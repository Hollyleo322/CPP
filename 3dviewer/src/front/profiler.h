#pragma once
#include <chrono>
#include <iostream>
#include <string>

class Profiler {
 public:
  explicit Profiler(const std::string& name = "Profiler")
      : name(name), last(std::chrono::high_resolution_clock::now()) {
    std::cout << "[" << name << "] Профайлер запущен.\n";
  }

  void mark_start(const std::string& label) {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> diff = now - last;
    last = now;  // Обновляем метку времени
    std::cout << "[" << name << "] " << label << std::endl;
  }

  void mark_end(const std::string& label) {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> diff = now - last;
    last = now;  // Обновляем метку времени
    std::cout << "[" << name << "] " << label << ": " << diff.count()
              << " мс\n";
  }

 private:
  std::string name;
  std::chrono::time_point<std::chrono::high_resolution_clock> last;
};
