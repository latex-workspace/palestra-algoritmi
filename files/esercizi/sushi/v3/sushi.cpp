#include <algorithm>
#include <climits>
#include <cstring>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
// #define DEBUG

using namespace std;

#ifdef DEBUG
string to_str(bool *v, int n) {
  string s = "";
  for (int i = 0; i < n; i++)
    s += to_string(v[i]) + " ";
  return s;
}
#endif

int sushi(int N, int B, vector<int> A) {

  // Salvo le ultime 2 righe della tabella del knapsack
  bool prev_buf[B + 1];
  bool curr_buf[B + 1];
  bool latest_buf[B + 1];

  bool *prev_dp = prev_buf;
  bool *curr_dp = curr_buf;
  bool *latest = latest_buf;

  for (int i = 0; i <= B; i++)
    prev_dp[i] = 0;
  prev_dp[0] = 1;
  curr_dp[0] = 1;
  latest[0] = 1;

#ifdef DEBUG
  std::cout << "   \t:\t";
  for (int k = 0; k <= B; k++)
    std::cout << k << " ";
  std::cout << std::endl;

  std::cout << "[x]\t:\t" << to_str(prev_dp, B + 1) << std::endl;
#endif
  int block_size = 1;

  while (1) {

    memcpy(latest, prev_dp, (B + 1) * sizeof(bool));

    // compute the ith knapsack problem
    for (int i = 0; i < N; i++) {

      // Long cause it can overflow in some testcase since its O(B^2)
      long long weight = (long long)block_size * A[i];
      for (int j = 1; j <= B; j++)
        curr_dp[j] = prev_dp[j] || (weight > j ? 0 : prev_dp[j - weight]);

#ifdef DEBUG
      std::cout << "[" << weight << "]\t:\t" << to_str(curr_dp, B + 1) << endl;
#endif
      std::swap(prev_dp, curr_dp);
    }

    if (prev_dp[B])
      break;
    // 2^k -1 is the sum of the first k power of 2
    else if (2 * block_size - 1 >= B)
      return -1;

    block_size *= 2;
  }

  int lower_bound = 1;
  int upper_bound = block_size + 1;

  while (lower_bound < upper_bound) {

#ifdef DEBUG
    std::cout << "b_search [" << lower_bound << ", " << upper_bound << ")"
              << endl;
    std::cout << "Latest\t:\t" << to_str(latest, B + 1) << endl;
#endif
    memcpy(prev_dp, latest, (B + 1) * sizeof(bool));

    int mid = (lower_bound + upper_bound) / 2;
    // compute the ith knapsack problem
    for (int i = 0; i < N; i++) {

      // Long cause it can overflow in some testcase since its O(B^2)
      long long weight = (long long)mid * A[i];
      for (int j = 1; j <= B; j++)
        curr_dp[j] = prev_dp[j] || (weight > j ? 0 : prev_dp[j - weight]);

#ifdef DEBUG
      std::cout << "[" << mid * A[i] << "]\t:\t" << to_str(curr_dp, B + 1)
                << endl;
#endif

      std::swap(prev_dp, curr_dp);
    }
    if (prev_dp[B]) {
      upper_bound = mid;
    } else {
      lower_bound = mid + 1;
    }
  }

  return block_size - 1 + lower_bound;
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
