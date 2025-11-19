#include <fstream>
#include <iostream>
#include <utility>
using namespace std;

void f() { std::cout << "no args" << std::endl; }

void f(int a) { std::cout << "int arg: " << a << std::endl; }

struct Point {
  int x, y;
  Point(int x, int y) : x(x), y(y) {}
  // bool operator<(const Point &other) const {
  //   if (this->x != other.x) {
  //     return this->x < other.x;
  //   }
  //   return this->y < other.y;
  // }
};

bool operator<(const Point &a, const Point &b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

std::ostream &operator<<(std::ostream &os, const Point &p) {
  return os << "(" << p.x << ", " << p.y << ")";
}

int main(int argc, char *argv[]) {
  // f();
  // f(42);
  // string a = "a";
  // string b = "asdfa";

  // std::cout << (2 + 2) << std::endl;
  // std::cout << (a + b) << std::endl;

  Point p1(3, 2);
  Point p2(3, 1);
  std::cout << "putno minore: " << ((p1 < p2) ? p1 : p2) << std::endl;
}
