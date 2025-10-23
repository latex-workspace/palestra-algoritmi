#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {

  // ifstream cin("input0.txt");
  // ofstream cout("output.txt");

  int N;
  cin >> N;

  vector<int> T(N);
  for (int i = 0; i < N; i++)
    cin >> T[i];

  vector<int> ts(N); // se mi fermo
  vector<int> tr(N); // se non mi fermo

  ts[0] = T[0];
  tr[0] = 0;

  for (int i = 1; i < N; i++) {
    ts[i] = T[i] + min(tr[i - 1], ts[i - 1]);
    tr[i] = ts[i - 1];
  }

  cout << min(ts[N - 1], tr[N - 1]) << endl;
  return 0;
}
