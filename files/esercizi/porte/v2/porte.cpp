#include <cstring>
#include <fstream>
#include <iostream>

#define MOD 1000000007
#define MAXN 400001

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

int N;
int A[MAXN];
int dp[MAXN];

int main(int argc, char *argv[]) {
  FILE *in = fopen("input.txt", "r");
  std::ofstream out("output.txt");
  N = scanInt(in);
  for (int i = 0; i < N; i++)
    A[i] = scanInt(in);

  memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  for (int i = 1; i < N; i++) {
    int pow = 1;
    while (pow <= i) {
      if ((A[i] + A[i - pow]) % pow == 0) {
        dp[i] += dp[i - pow];
        dp[i] %= MOD;
      }
      pow *= 2;
    }
  }

  out << dp[N - 1] % MOD << std::endl;
}
