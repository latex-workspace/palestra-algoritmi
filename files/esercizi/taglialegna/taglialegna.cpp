#include <fstream>
#include <iostream>

void Abbatti(int, int);

// Commenta quanto sottoponi al sito
void Abbatti(int pos, int dir) { std::cout << pos << " " << dir << std::endl; }

void Pianifica(int n, int h[]) {

  int lb[n], rb[n];
  for (int i = 0; i < n; i++) {
    lb[i] = i;
    while (lb[i] > 0 && lb[i] > i - h[i] + 1)
      lb[i] = lb[lb[i] - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    rb[i] = i;
    while (rb[i] < n - 1 && rb[i] < i + h[i] - 1)
      rb[i] = rb[rb[i] + 1];
  }

  for (int i = 0; i < n; i++)
    std::cout << lb[i] << "\t";
  std::cout << std::endl;
  for (int i = 0; i < n; i++)
    std::cout << rb[i] << "\t";
  std::cout << std::endl;

  // for (int i = N - 1; i >= 0; i--) {
  //   rep[i] = i;
  //   while (rep[i] + 1 < N && rep[i] + 1 < i + H[i])
  //     rep[i] = rep[rep[i] + 1];
  // }

  Abbatti(0, 1);
  //
}

int n, altezza[100000];
int main(int argc, char *argv[]) {
  std::ifstream in("input3.txt");

  in >> n;
  for (int i = 0; i < n; i++)
    in >> altezza[i];

  Pianifica(n, altezza);
}
