#include <climits>
#include <fstream>
#include <iostream>
#define MAXN 10002

using namespace std;

// input data
int N, R, T, L;
int X[MAXN + 1];
unsigned int dp[MAXN + 1][MAXN];

int main() {
  // uncomment the following lines if you want to read/write from files
  // ifstream cin("input1.txt");
  // ofstream cout("output.txt");

  cin >> N >> R >> T >> L;
  for (int i = 0; i < N; i++)
    cin >> X[i];
  X[N] = L;

  for (int i = 0; i <= R; i++)
    dp[0][i] = X[0];

  for (int i = 1; i <= N; i++) {
    for (int j = 0; j <= R; j++) {
      // Option 1: i have skipped at max j-1 and i know I can skip another one
      unsigned int t1;
      if (j == 0)
        t1 = UINT_MAX;
      else
        t1 = dp[i - 1][j - 1];

      // Option 2: i have skipped at max j and i know I can't skip
      // another one
      bool can_pass = dp[i - 1][j] % (2 * T) < T;
      unsigned int t2 = dp[i - 1][j] + (can_pass ? 0 : T - dp[i - 1][j] % T);

      dp[i][j] = min(t1, t2) + X[i] - X[i - 1];
    }
  }

  // for (int j = 0; j <= R; j++) {
  //   for (int i = 0; i <= N; i++) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  cout << dp[N][R] << endl;
  return 0;
}
