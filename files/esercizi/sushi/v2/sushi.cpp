#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
// #define DEBUG

using namespace std;

#ifdef DEBUG
void print_v(int v[], int n) {
  for (int i = 0; i < n; i++)
    std::cout << i << "\t->\t" << v[i] << "\n";
}
#endif

int sushi(int N, int B, vector<int> A) {

  // Salvo le ultime 2 righe della tabella del knapsack
  bool prev_buf[B + 1];
  bool curr_buf[B + 1];
  bool *prev_dp = prev_buf;
  bool *curr_dp = curr_buf;

  for (int i = 0; i <= B; i++)
    prev_dp[i] = 0;
  prev_dp[0] = 1;
  curr_dp[0] = 1;

#ifdef DEBUG
  std::cout << "[x] : ";
  for (int k = 0; k <= B; k++)
    std::cout << prev_dp[k] << " ";
  std::cout << std::endl;
#endif

  int R = 1;

  while (1) {

    for (int i = 0; i < N; i++) {

      for (int j = 1; j <= B; j++)
        curr_dp[j] = prev_dp[j] || (A[i] > j ? 0 : prev_dp[j - A[i]]);

#ifdef DEBUG
      std::cout << "[" << A[i] << "] : ";
      for (int k = 0; k <= B; k++)
        std::cout << curr_dp[k] << " ";
      std::cout << std::endl;
#endif

      std::swap(prev_dp, curr_dp);
    }

    if (prev_dp[B])
      return R;
    else if (R >= B)
      return -1;

    R++;
  }

  return prev_dp[B];
}

#ifdef DEBUG
int main(int argc, char *argv[]) {
  std::ifstream in("input0.txt");

  int N, B;
  in >> N >> B;
  vector<int> A;
  for (int i = 0; i < N; i++) {
    int a;
    in >> a;
    A.push_back(a);
  }

  int rv = sushi(N, B, A);
  std::cout << rv << std::endl;
}
#endif
