#include <algorithm>
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

  int prev_sk_buf[B + 1];
  int curr_sk_buf[B + 1];
  int *prev_sk = prev_sk_buf;
  int *curr_sk = curr_sk_buf;

  for (int i = 0; i <= B; i++) {
    prev_sk[i] = -1;
    curr_sk[i] = -1;
  }

  prev_sk[0] = 0;

  // For each type of sushi
  for (int i = 0; i < N; i++) {

#ifdef DEBUG
    std::cout << "Iterazione " << i << std::endl;
#endif
    // I can take any number without exceeding the budget
    for (int j = 0; j <= B; j++)
      curr_sk[j] = -1;

    for (int j = 1; j <= B / A[i]; j++) {
      // For each number, see if it can improve a solution for a budget < B
      for (int k = 0; k <= B; k++) {
        if (prev_sk[k] != -1) {
          int curr_price = k + A[i] * j;
          int curr_sk_s = max(j, prev_sk[k]);

          if (curr_price > B)
            continue;

          curr_sk[curr_price] = curr_sk[curr_price] == -1
                                    ? curr_sk_s
                                    : min(curr_sk[curr_price], curr_sk_s);
        }
      }
    }

#ifdef DEBUG
    std::cout << "CURR SK PRE MERGE" << std::endl;
    print_v(curr_sk, B + 1);
    std::cout << "------------------" << std::endl;
#endif

    for (int k = 0; k <= B; k++) {
      int merged = min(curr_sk[k], prev_sk[k]);
      merged = merged == -1 ? max(curr_sk[k], prev_sk[k]) : merged;
      curr_sk[k] = merged;
    }

#ifdef DEBUG
    std::cout << "CURR SK POST MERGE" << std::endl;
    print_v(curr_sk, B + 1);
    std::cout << "------------------" << std::endl;
#endif

    std::swap(prev_sk, curr_sk);
  }

  return prev_sk[B];
}

#ifdef DEBUG
int main(int argc, char *argv[]) {
  std::ifstream in("input2.txt");

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
