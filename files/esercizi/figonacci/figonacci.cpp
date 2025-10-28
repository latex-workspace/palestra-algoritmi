#include <assert.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

inline int mod(int a, int b) {
  int r = a % b;
  return r + (r < 0) * b;
}

// f(n) = f(n-1) - (n-2)*f(n-2) - f(n-2) + (n-1)*f(n-1)
//      = (1+n 1)*f(n-1)-(n-2+1)f(n-2)
//      = n*f(n-1) - (n-1)*f(n-2)
//      = (n-1)*f(n-1) - (n-1)*f(n-2) + f(n-1)
//      = (n-1)*(f(n-1) - f(n-2)) + f(n-1)
int enumera(int N, int M) {
  int a = -1;
  int b = 0;

  for (int i = 2; i <= N; i++) {
    int c = mod((b - a) * (i - 1) + b, M);
    a = b;
    b = c;
  }
  return b;
}

int main() {
  FILE *fr, *fw;
  int N, M;

  fr = fopen("input.txt", "r");
  fw = fopen("output.txt", "w");
  assert(2 == fscanf(fr, "%d%d", &N, &M));

  fprintf(fw, "%d\n", enumera(N, M));
  fclose(fr);
  fclose(fw);
  return 0;
}
