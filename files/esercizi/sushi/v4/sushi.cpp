#include <bitset>
#include <cstring>
#include <fstream>
#include <iostream>
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

using namespace std;

constexpr int MAXB = 100'100;

string bitset_str(bitset<MAXB> &bs, int n) {
  string s = "";
  for (int i = n - 1; i >= 0; i--)
    s += to_string(bs.test(i)) + " ";
  return s;
}

int sushi(int N, int B, vector<int> A) {
  bitset<MAXB> S1, S2;
  S1[0] = 1;

  int R = 1;
  while (true) {
    S2 = S1;
    for (int a : A) {
      S2 |= S2 << (a * R);
      DBG << "[" << a * R << "]\t:\t" << bitset_str(S2, B + 1) << endl;
    }
    if (S2.test(B))
      break;

    R *= 2;
    S1 = S2;
    if (R > B)
      return -1;
  }

  DBG << "Latest" << bitset_str(S1, B + 1) << endl;
  for (int t = R / 2; t > 0; t /= 2) {
    S2 = S1;
    for (int a : A) {
      S2 |= S2 << (a * t);
      DBG << "[" << a * t << "]\t:\t" << bitset_str(S2, B + 1) << endl;
    }
    if (!S2.test(B)) {
      R |= t;
      S1 = S2;
    }
  }

  return R;
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
