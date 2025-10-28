#include <fstream>
#include <iostream>

void Abbatti(int, int);

// Commenta quanto sottoponi al sito
void Abbatti(int pos, int dir) { std::cout << pos << " " << dir << std::endl; }

void Pianifica(int n, int h[]) {

  int lb[n], rb[n]; // Right/left bound for each tree
  int ff[n];        // First falling tree to hit i-th tree
  for (int i = 0; i < n; i++) {
    lb[i] = i;
    while (lb[i] > 0 && lb[i] > i - h[i] + 1)
      lb[i] = lb[lb[i] - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    rb[i] = i;
    ff[i] = -1;
    while (rb[i] < n - 1 && rb[i] < i + h[i] - 1) {
      ff[rb[i] + 1] = i;
      rb[i] = rb[rb[i] + 1];
    }
  }

  // Saving in solution[i] the optimal solution for trees in range 0 - i
  // included
  int solution[n];

  // In which direction should I cut the last tree in order to obtain i-th
  // optimal solution: 0=left 1=right
  bool dir[n];

  // Saves the optimal spot to to start the domino effect when making the trees
  // fall to the right
  int opt_split[n];

  // Saves the first tree to cut in the i-th optimal solution
  int first_cut[n];

  solution[0] = 1;
  dir[0] = 1;
  opt_split[0] = 0;
  first_cut[0] = 0;

  for (int i = 1; i < n; i++) {

    // Case 1: last tree is cut to the left
    int sol1 = 1 + (lb[i] > 0 ? solution[lb[i] - 1] : 0);
    int cut1 = i;
    bool dir1 = 0;

    // Case 2: last tree falls to the right
    if (ff[i] != -1) {
      // Case 2.1: tree falls for domino effect
      int idx1 = opt_split[ff[i]];
      int sol21 = 1 + (idx1 > 0 ? solution[idx1 - 1] : 0);

      // Case 2.2: tree is cut to the right
      int idx2 = i;
      int sol22 = 1 + (idx2 > 0 ? solution[idx2 - 1] : 0);

      opt_split[i] = (sol21 < sol22) ? idx1 : idx2;

    } else
      opt_split[i] = i;

    int sol2 = 1 + (opt_split[i] > 0 ? solution[opt_split[i] - 1] : 0);
    int cut2 = opt_split[i];
    bool dir2 = 1;

    // Saving better solution
    if (sol1 < sol2) {
      solution[i] = sol1;
      first_cut[i] = cut1;
      dir[i] = dir1;
    } else {
      solution[i] = sol2;
      first_cut[i] = cut2;
      dir[i] = dir2;
    }
  }

  std::cout << "lb:  ";
  for (int i = 0; i < n; i++)
    std::cout << lb[i] << "\t";
  std::cout << std::endl;

  std::cout << "rb:  ";
  for (int i = 0; i < n; i++)
    std::cout << rb[i] << "\t";
  std::cout << std::endl;

  std::cout << "ff:  ";
  for (int i = 0; i < n; i++)
    std::cout << ff[i] << "\t";
  std::cout << std::endl;

  std::cout << "sol: ";
  for (int i = 0; i < n; i++)
    std::cout << solution[i] << "\t";
  std::cout << std::endl;

  std::cout << "fc:  ";
  for (int i = 0; i < n; i++)
    std::cout << first_cut[i] << "\t";
  std::cout << std::endl;

  std::cout << "dir: ";
  for (int i = 0; i < n; i++)
    std::cout << dir[i] << "\t";
  std::cout << std::endl;

  std::cout << "os:  ";
  for (int i = 0; i < n; i++)
    std::cout << opt_split[i] << "\t";
  std::cout << std::endl;

  int pos = n - 1;
  while (pos >= 0) {
    Abbatti(first_cut[pos], dir[pos]);

    if (dir[pos] == 0)
      pos = lb[pos] - 1;
    else
      pos = first_cut[pos] - 1;
  }
}

int n, altezza[100000];
int main(int argc, char *argv[]) {
  std::ifstream in("input3.txt");

  in >> n;
  for (int i = 0; i < n; i++)
    in >> altezza[i];

  Pianifica(n, altezza);
}
