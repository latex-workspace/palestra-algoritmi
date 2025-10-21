#include <cstdio>
using namespace std;
#define MAXSTRLEN 4

int main(int argc, char *argv[]) {

  // Input
  FILE *in = fopen("input.txt", "r");
  int n1, n2;
  fscanf(in, "%d %d", &n1, &n2);

  int v1[n1][2];
  char v2[n2][3][MAXSTRLEN];

  for (int i = 0; i < n1; i++)
    fscanf(in, "%d %d", &v1[i][0], &v1[i][1]);

  for (int i = 0; i < n2; i++)
    fscanf(in, "%s %s %s", v2[i][0], v2[i][1], v2[i][2]);

  // Output
  FILE *out = fopen("output.txt", "w");

  for (int i = 0; i < n1; i++)
    fprintf(out, "%d %d\n", v1[i][0], v1[i][1]);

  for (int i = 0; i < n2; i++)
    fprintf(out, "%s %s %s\n", v2[i][0], v2[i][1], v2[i][2]);
}
