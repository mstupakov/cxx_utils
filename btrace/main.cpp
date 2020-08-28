#include <map>
#include "btrace.h"

struct A {
  void m1() {
    std::map<int, int> m_map = {};
    m_map.at(3);
  }
};

int main(int argc, char **argv) {
  BTrace b;

  A obj;
  obj.m1();

  return 0;
}
