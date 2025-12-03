#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#define DEBUG

using namespace std;

constexpr int MAXB = 100'100;

template <size_t N> class masked_bitset {
  // static_assert(N % 64 == 0, "N must be a multiple of 64");
  static constexpr size_t num_words = size_t(N + 63) / 64;
  uint64_t buf[num_words]{};

public:
  // Set ith bit
  void set(size_t i) { buf[i / 64] |= (1ULL << (i % 64)); }

  // Unset ith bit
  void unset(size_t i) { buf[i / 64] &= ~(1ULL << (i % 64)); }

  // Test ith bit
  bool test(size_t i) const { return (buf[i / 64] & (1ULL << (i % 64))) != 0; }

  void offset_or(size_t offset) {
    // Basically does this: *this |= (*this << offset);
    if (offset >= N)
      return;
    size_t word_shift = offset / 64;
    size_t bit_shift = offset % 64;
    bool zero_shif_correction = bit_shift == 0;
    for (size_t i = num_words; i-- > word_shift + 1;) {
      // std::cout << i << std::endl;
      uint64_t high = buf[i - word_shift] << bit_shift;
      uint64_t low =
          buf[i - word_shift - 1 + zero_shif_correction] >> (64 - bit_shift);
      buf[i] |= (high | low);
    }

    buf[word_shift] |= buf[0] << bit_shift;
  }

  // true if the same bits are on
  bool operator==(const masked_bitset &other) const {
    for (size_t i = 0; i < num_words; ++i) {
      if (buf[i] != other.buf[i])
        return false;
    }
    return true;
  }

  // Deep copy of bitset
  masked_bitset &operator=(const masked_bitset &other) {
    if (this != &other) {
      for (size_t i = 0; i < num_words; ++i) {
        buf[i] = other.buf[i];
      }
    }
    return *this;
  }

  // Print masked_bitset as a sequence of bits, high-to-low (like
  // std::bitset)
  friend std::ostream &operator<<(std::ostream &os, const masked_bitset &bs) {
    for (size_t i = N; i > 0; --i) {
      size_t bit_idx = i - 1;
      size_t group = bit_idx / 64;
      size_t offset = bit_idx % 64;
      if (i % 64 == 0 && i != N)
        os << '\n';
      os << ((bs.buf[group] & (1ULL << offset)) ? '1' : '0');
    }
    return os;
  }
};

string bitset_str(masked_bitset<MAXB> &bs, int n) {
  string s = "";
  for (int i = n - 1; i >= 0; i--)
    s += to_string(bs.test(i)) + " ";
  return s;
}

int sushi(int N, int B, vector<int> A) {
  masked_bitset<MAXB> S1, S2;
  S1.set(0);

  int R = 1;

#ifdef DEBUG
  std::cout << "[x]\t:\t" << bitset_str(S1, B + 1) << endl;
#endif
  while (true) {
    S2 = S1;
    for (int a : A) {
      // S2 |= S2 << (a * R);
      S2.offset_or(a * R);
#ifdef DEBUG
      std::cout << "[" << a * R << "]\t:\t" << bitset_str(S2, B + 1) << endl;
#endif
    }
    if (S2.test(B))
      break;

    R *= 2;
    S1 = S2;
    if (R > B)
      return -1;
  }

#ifdef DEBUG
  std::cout << "Latest" << bitset_str(S1, B + 1) << endl;
#endif
  for (int t = R / 2; t > 0; t /= 2) {
    S2 = S1;
    for (int a : A) {
      // S2 |= S2 << (a * t);
      S2.offset_or(a * t);
#ifdef DEBUG
      std::cout << "[" << a * t << "]\t:\t" << bitset_str(S2, B + 1) << endl;
#endif
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
  std::ifstream in("input1.txt");

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
