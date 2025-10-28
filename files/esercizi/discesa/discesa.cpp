#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#define MAXN 10

using namespace std;

int dp[MAXN][MAXN];
int n;

int main() {

  std::ifstream in("input.txt");
  std::ofstream out("output.txt");

  in >> n;
  int tmp;
  in >> dp[0][0];
  for (int i = 1; i < n; i++) {
    in >> tmp;
    dp[i][0] = dp[i - 1][0] + tmp;
    for (int j = 1; j < i; j++) {
      in >> tmp;
      dp[i][j] = tmp + max(dp[i - 1][j - 1], dp[i - 1][j]);
    }
    in >> tmp;
    dp[i][i] = dp[i - 1][i - 1] + tmp;
  }

  out << *max_element(dp[n - 1], dp[n - 1] + n) << std::endl;
}
