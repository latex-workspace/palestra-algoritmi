#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
#define MAXN 501
#define MAXH 2001
// #define DBG

// input data
int n;
vector<int> h;
int dp[MAXN][MAXH][2];

void printdbg1() {
#ifdef DBG
  for (int i = MAXH - 1; i >= 0; i--) {
    for (int j = 0; j < n; j++) {
      if (dp[j][i][0] == INT_MAX)
        std::cout << "/\t";
      else
        cout << dp[j][i][0] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  for (int i = MAXH - 1; i >= 0; i--) {
    for (int j = 0; j < n; j++)
      if (dp[j][i][1] == INT_MAX)
        std::cout << "/\t";
      else
        cout << dp[j][i][1] << "\t";
    std::cout << std::endl;
  }
  std::cout << std::endl;
#endif
}

int main() {
  //  uncomment the following lines if you want to read/write from files
  // ifstream cin("input1.txt");
  //  ofstream cout("output.txt");

  cin >> n;
  h.resize(n);
  for (int i = 0; i < n; i++)
    cin >> h[i];

  for (int i = 0; i < MAXH; i++) {
    dp[0][i][0] = (h[0] - i) * (h[0] - i);
    dp[0][i][1] = (h[0] - i) * (h[0] - i);
  }

  for (int i = 1; i < n; i++) {
    //-_-
    int min = dp[i - 1][0][1];
    dp[i][0][0] = INT_MAX;
    for (int j = 1; j < MAXH; j++) {
      dp[i][j][0] = min + (h[i] - j) * (h[i] - j);
      min = std::min(min, dp[i - 1][j][1]);
    }

    //_-_
    min = dp[i - 1][MAXH - 1][0];
    dp[i][MAXH - 1][1] = INT_MAX;
    for (int j = MAXH - 2; j >= 0; j--) {
      dp[i][j][1] = min + (h[i] - j) * (h[i] - j);
      min = std::min(min, dp[i - 1][j][0]);
    }
  }

  printdbg1();

  int min = INT_MAX;
  for (int i = 0; i < MAXH; i++) {
    min = std::min(min, dp[n - 1][i][0]);
    min = std::min(min, dp[n - 1][i][1]);
  }

  // insert your code here

  cout << min << endl; // print the result
  return 0;
}
