#include <fstream>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

struct Point {
  int x;
  int y;
};
bool operator<(const Point &a, const Point &b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

bool operator>(const Point &a, const Point &b) {
  if (a.x != b.x) {
    return a.x > b.x;
  }
  return a.y > b.y;
}

int main(int argc, char *argv[]) {

  // std::priority_queue<Point, std::vector<Point>, std::greater<Point>> pq;
  //
  // pq.push(Point{3, 4});
  // pq.push(Point{3, 2});
  // pq.push(Point{5, 4});

  // int size = pq.size();
  // while (!pq.empty()) {
  //   Point p = pq.top();
  //   pq.pop();
  //   std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
  // }
  // for (int i = 0; i < size; i++) {
  //   Point p = pq.top();
  //   pq.pop();
  //   std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
  // }
  // std::sort(vec.begin(), vec.end(), std::less<int>());
  // std::sort(vec.begin(), vec.end(), std::greater<int>());
  vector<int> vec = {5, 2, 8, 1, 4};
  sort(vec.begin(), vec.end(), std::greater<int>());
  for (int v : vec) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  sort(vec.begin(), vec.end(), std::less<int>());
  for (int v : vec) {
    std::cout << v << " ";
  }
  std::cout << std::endl;

  sort(vec.begin(), vec.end(), [](auto &a, auto &b) { return a < b; });

  for (int v : vec) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
