#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#define MAXN 10002

using namespace std;

inline static int scanInt(FILE *file = stdin) {
  int n = 0, neg = 1;
  char c = getc_unlocked(file);
  while (c != '-' && (c < '0' || c > '9'))
    c = getc_unlocked(file);
  if (c == '-') {
    neg = -1;
    c = getc_unlocked(file);
  }
  while (c >= '0' && c <= '9') {
    n = n * 10 + (c - '0');
    c = getc_unlocked(file);
  }
  return n * neg;
}

int N, R, T, L;
int X[MAXN + 1];
unsigned int dp_buf1[MAXN + 1], dp_buf2[MAXN + 1];

int main() {

  FILE *in = fopen("input1.txt", "r");
  if (!in)
    in = stdin;

  unsigned int *dp_prev = dp_buf1;
  unsigned int *dp_cur = dp_buf2;

  N = scanInt(in);
  R = scanInt(in);
  T = scanInt(in);
  L = scanInt(in);

  for (int i = 0; i < N; i++)
    X[i] = scanInt(in);
  X[N] = L;

  for (int i = 0; i <= R; i++)
    dp_prev[i] = X[0];

  for (int i = 1; i <= N; i++) {
    int upper_bound = min(R, i);
    unsigned int delta = X[i] - X[i - 1];

    for (int j = 0; j <= upper_bound; j++) {
      // Safe read for j == 0
      unsigned int prev_jm1 = (j > 0) ? dp_prev[j - 1] : UINT_MAX;

      // Option 1: skip allowed
      unsigned int t1 = prev_jm1;

      // Option 2: can't skip anymore
      unsigned int mod = dp_prev[j] % (2 * T);
      unsigned int over = (mod >= T);
      unsigned int adjust = over * (T - (mod - T));

      // Safe read for j == i
      unsigned int t2 = dp_prev[j - (i == j)] + adjust;

      dp_cur[j] = min(t1, t2) + delta;
    }

    std::swap(dp_prev, dp_cur);
  }

  // after final swap, dp_prev has the result
  cout << dp_prev[R] << endl;

  fclose(in);
  return 0;
}
