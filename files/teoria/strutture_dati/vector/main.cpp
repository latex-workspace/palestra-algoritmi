#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> void print_vector(const std::vector<T> &v) {
  std::cout << "[ ";
  for (int i = 0; i < v.size(); i++) {
    std::cout << v[i] << " ";
  }
  std::cout << "]\n";
}

struct my_struct {
  int a;
  double b;
  my_struct(int a_, double b_) : a(a_), b(b_) {}
};

std::ostream &operator<<(std::ostream &os, const my_struct &s) {
  return os << "my_struct(" << s.a << ", " << s.b << ")";
}

void basic() {
  vector<int> v;
  // resize
  v.resize(10);
  v[5] = -1;
  print_vector(v);

  // append
  v.push_back(42);
  print_vector(v);

  // remove last
  v.pop_back();
  print_vector(v);

  // clear
  v.clear();
  print_vector(v);
}

void structs() {
  vector<my_struct> v_structs;
  my_struct s(1, 2);
  v_structs.resize(3, s);
  print_vector(v_structs);
  v_structs[0].a = 10;
  print_vector(v_structs);

  v_structs.emplace_back(11, 22.0);
  print_vector(v_structs);
}

void iterators() {
  vector<int> v = {1, 2, 3, 4, 5};
  for (auto it = v.begin(); it != v.end(); ++it) {
    cout << *it << " ";
    (*it)++;
  }
  cout << std::endl;

  for (auto &elem : v) {
    cout << elem << " ";
    elem++;
  }
  cout << std::endl;

  print_vector(v);
}

void matrix() {
  vector<vector<int>> matrix;

  // Occhio ad inizializare sempre! matrix[0][0] -> errore
  matrix.resize(3, vector<int>(4, 0));

  for (int i = 0; i < min(matrix.size(), matrix[0].size()); i++)
    matrix[i][i] = 1;

  for (const auto &row : matrix)
    print_vector(row);
}

void other() {
  vector<int> v = {4, 2, 3, 1, 5};
  auto pos = std::find(v.begin(), v.end(), 2);
  v.erase(pos);
  print_vector(v);

  pos = std::find(v.begin(), v.end(), 2);
  std::cout << (pos == v.end()) << std::endl;

  v.insert(v.begin() + 1, 2);
  sort(v.begin(), v.end(), greater<>());
  print_vector(v);

  sort(v.begin(), v.end(), less<>());
  print_vector(v);
}

int main(int argc, char *argv[]) {
  // basic();
  // structs();
  // iterators();
  // matrix();
  // other();
}
