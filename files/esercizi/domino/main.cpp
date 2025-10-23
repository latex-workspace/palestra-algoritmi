#include <fstream>
#include <iostream>
#include <unordered_map>

#define MAXN 1000

// int map[MAXN]; sono stato io
std::unordered_map<int, int> map;

int domino_rec(int n) {
  std::cout << n << std::endl;

  if (n <= 2)
    return n;

  auto n1 = map.find(n - 1);
  auto n2 = map.find(n - 2);

  if (n1 == map.end()) {
    int rv = domino_rec(n - 1);
    map.insert({n - 1, rv});
  }

  if (n2 == map.end()) {
    int rv = domino_rec(n - 2);
    map.insert({n - 2, rv});
  }

  return map[n - 1] + map[n - 2];
}

int domino_dp(int n) {
  int dp[n];
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 2;

  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

int main(int argc, char *argv[]) {
  int n = 6;
  // int dp[n];

  std::cout << domino_rec(n) << std::endl;
  std::cout << domino_dp(n) << std::endl;

  std::cout << "\n\n\n" << std::endl;
  std::cout << "\n\n\n" << std::endl;
  // for (auto it : map) {
  //   std::cout << it.first << " => " << it.second << std::endl;
  // }
}
