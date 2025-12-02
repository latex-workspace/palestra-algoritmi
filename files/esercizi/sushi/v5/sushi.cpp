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
static NullStream DBG_null_stream;
#define DBG DBG_null_stream
#endif

constexpr int MAXB = 100'100;
bitset<MAXB> S1_buf, S2_buf, latest;
auto S1 = &S1_buf, S2 = &S2_buf;

string bitset_str(bitset<MAXB> &bs, int n) {
  string s = "";
  for (int i = 0; i < n; i++)
    s += to_string(bs.test(i)) + " ";
  return s;
}

int sushi(int N, int B, vector<int> A) {

  (*S1)[0] = 1;

  int R = 1;
  while (true) {
    latest = *S1;
    std::swap(S1, S2);

    for (int a : A) {
      *S2 |= (*S2) << (a * R);
      // DBG << "[" << a * R << "]\t:\t" << bitset_str(*S2, B + 1) << endl;
    }
    if ((*S2).test(B))
      break;

    R *= 2;
    std::swap(S1, S2);
    if (R > B)
      return -1;
  }

  // DBG << "Ricerca binaria:" << endl;
  // DBG << "Latest" << bitset_str(latest, B + 1) << endl;
  *S1 = latest;
  for (int t = R / 2; t > 0; t /= 2) {
    // std::swap(S1, S2);
    *S2 = *S1;
    for (int a : A) {
      *S2 |= (*S2) << (a * t);

      // DBG << "[" << a * t << "]\t:\t" << bitset_str(*S2, B + 1) << endl;
    }
    if (!(*S2).test(B)) {
      R |= t;
      *S1 = *S2;
      // std::swap(S1, S2);
    }
  }

  return R;
}

#ifdef DEBUG
int main(int argc, char *argv[]) {
  std::ifstream in("input3.txt");

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
