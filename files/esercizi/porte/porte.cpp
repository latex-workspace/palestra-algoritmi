#include <cstring>
#include <fstream>
#include <iostream>

#define MOD 1000000007
#define MAXN 400001

int N;
int A[MAXN];
int dp[MAXN];

int main(int argc, char *argv[]) {
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");
  in >> N;
  for (int i = 0; i < N; i++)
    in >> A[i];

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
