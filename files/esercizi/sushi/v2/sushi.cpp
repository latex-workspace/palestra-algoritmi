#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#define DEBUG

using namespace std;

struct NullStream : public std::ostream {
  NullStream() : std::ostream(nullptr) {}
};

#ifdef DEBUG
#define DBG std::cout
#else
static NullStream dbg_null_stream;
#define DBG dbg_null_stream
#endif

void print_v(int v[], int n) {
  for (int i = 0; i < n; i++)
    DBG << i << "\t->\t" << v[i] << "\n";
}

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

  DBG << "[x] : ";
  for (int k = 0; k <= B; k++)
    DBG << prev_dp[k] << " ";
  DBG << std::endl;

  int R = 1;

  while (1) {

    for (int i = 0; i < N; i++) {

      for (int j = 1; j <= B; j++)
        curr_dp[j] = prev_dp[j] || (A[i] > j ? 0 : prev_dp[j - A[i]]);

      DBG << "[" << A[i] << "] : ";
      for (int k = 0; k <= B; k++)
        DBG << curr_dp[k] << " ";
      DBG << std::endl;

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
  DBG << rv << std::endl;
}
#endif
