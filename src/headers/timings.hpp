// timings.hpp

#ifndef TIMINGS_HPP
#define TIMINGS_HPP

#include <chrono>
#include <vector>
#include <iostream>

struct MeasureTime {
  using precision = std::chrono::nanoseconds;
  std::vector<std::chrono::steady_clock::time_point> times;
  std::chrono::steady_clock::time_point oneLast;
  const char* p() {
    std::string details = "Execution speed (nanoseconds): ";
    details += std::to_string(std::chrono::duration_cast<precision>(times.back() - oneLast).count());
    m();
    return details.c_str();
  }
  void m() {
    oneLast = times.back();
    times.push_back(std::chrono::steady_clock::now());
  }
  const char* t() {
    m();
    return p();
  }
  MeasureTime() {
    times.push_back(std::chrono::steady_clock::now());
  }
};

#endif
