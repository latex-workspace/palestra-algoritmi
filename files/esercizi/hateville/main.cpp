#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
  std::ifstream in("input.txt");
  int n;
  in >> n;

  int prices[n];

  for (int i = 0; i < n; i++) {
    in >> prices[i];

    return 0;
  }
