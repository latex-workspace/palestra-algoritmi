#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
#define MAXSTRLEN 4

// Tutte le seguenti functioni scrivono e leggono da stdout e stdin

inline static int scanInt() {
  int n = 0;
  int neg = 1;
  char c = getchar_unlocked();
  if (c == '-')
    neg = -1;
  while (c < '0' || c > '9') {
    c = getchar_unlocked();
    if (c == '-')
      neg = -1;
  }
  while (c >= '0' && c <= '9') {
    n = (n << 3) + (n << 1) + c - '0';
    c = getchar_unlocked();
  }
  return n * neg;
}

inline static void writeInt(int v) {
  static char buf[14];
  int p = 0;
  if (v == 0) {
    putchar_unlocked('0');
    return;
  }
  if (v < 0) {
    putchar_unlocked('-');
    v = -v;
  }
  while (v) {
    buf[p++] = v % 10;
    v /= 10;
  }
  while (p--) {
    putchar_unlocked(buf[p] + '0');
  }
}

inline static std::string getString() {
  std::string s;
  int c = getchar_unlocked();

  // Skip leading whitespace
  while (c != EOF && (c == ' ' || c == '\n' || c == '\t' || c == '\r'))
    c = getchar_unlocked();

  // Read until next whitespace or EOF
  while (c != EOF && c != ' ' && c != '\n' && c != '\t' && c != '\r') {
    s.push_back(static_cast<char>(c));
    c = getchar_unlocked();
  }

  return s;
}

inline static std::string putString(std::string &s) {
  int c = getchar_unlocked();

  // Skip leading whitespace
  while (c != EOF && (c == ' ' || c == '\n' || c == '\t' || c == '\r'))
    c = getchar_unlocked();

  // Read until next whitespace or EOF
  while (c != EOF && c != ' ' && c != '\n' && c != '\t' && c != '\r') {
    s.push_back(static_cast<char>(c));
    c = getchar_unlocked();
  }

  return s;
}

inline static void putString(const std::string &s) {
  for (char c : s)
    putchar_unlocked(c);
}

int main(int argc, char *argv[]) {

  // Input
  freopen("input.txt", "r", stdin);
  int n1, n2;
  n1 = scanInt();
  n2 = scanInt();

  int v1[n1][2];
  std::string v2[n2][3];

  for (int i = 0; i < n1; i++) {
    v1[i][0] = scanInt();
    v1[i][1] = scanInt();
  }

  for (int i = 0; i < n2; i++) {
    v2[i][0] = getString();
    v2[i][1] = getString();
    v2[i][2] = getString();
  }

  // Output
  freopen("output.txt", "w", stdout);

  // Per formattare la stringa in modo simile a cout
  std::ostringstream oss;
  for (int i = 0; i < n1; i++) {
    oss.str("");
    oss.clear();
    oss << v1[i][0] << " " << v1[i][1] << "\n";
    putString(oss.str());
  }

  for (int i = 0; i < n2; i++) {
    oss.str("");
    oss.clear();
    oss << v2[i][0] << " " << v2[i][1] << " " << v2[i][2] << "\n";
    putString(oss.str());
  }
}
