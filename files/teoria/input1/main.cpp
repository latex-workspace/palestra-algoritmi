#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {

  // Input
  std::ifstream in("input.txt");
  int n1, n2;
  in >> n1 >> n2;

  int v1[n1][2];
  string v2[n2][3];

  for (int i = 0; i < n1; i++)
    in >> v1[i][0] >> v1[i][1];

  for (int i = 0; i < n2; i++)
    in >> v2[i][0] >> v2[i][1] >> v2[i][2];

  // Output
  std::ofstream out("output.txt");

  for (int i = 0; i < n1; i++)
    out << v1[i][0] << " " << v1[i][1] << "\n";

  for (int i = 0; i < n2; i++)
    out << v2[i][0] << " " << v2[i][1] << " " << v2[i][2] << "\n";
}
