#include "timer.hpp"

#include <iostream>
#include <iomanip>
double calcTime() {
  struct timespec getTime;
  clock_gettime(CLOCK_MONOTONIC, &getTime);
  return (getTime.tv_sec + getTime.tv_nsec * 1e-9) * 1000;
}

timer::timer() { checkpoint = calcTime(); }

timer::~timer() {}

timer::timer(timer const &rhs) { *this = rhs; }

timer &timer::operator=(timer const &rhs) {
  if (this != &rhs) {
    checkpoint = rhs.checkpoint;
  }
  return (*this);
}

void timer::record(const char *msg) {
  double newcp = calcTime();

  std::cout << std::setw(15) << std::left << msg;
  std::cout << std::fixed << std::setprecision(5) << newcp - checkpoint << std::endl;
  checkpoint = calcTime();
}

void timer::start(void) {
  checkpoint = calcTime();
}
