#include <fstream>
#include <iostream>
#include <utility>
using namespace std;

struct X {
  int a;
  X(int a) : a(a) {}
};

class Y {
public:
  int b;
  Y(int b) : b(b) {}
};

void f(X x) { x.a += 10; }
void f(Y y) { y.b += 20; }
int main(int argc, char *argv[]) {
  X x(5);
  Y y(5);
  f(x);
  f(y);
  std::cout << x.a << std::endl;
  std::cout << y.b << std::endl;
}
