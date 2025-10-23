#include <fstream>
#include <iostream>

int solve(int N, int K, int *S) {

  int max = 0;
  int strawdberries = 0;
  int displeasure = 0;
  int left = 0;
  int right = N - 1;

  // Scorro da sinistra fino a che K lo permette
  while (displeasure <= K && left < N) {
    if (S[left] == 0)
      strawdberries++;
    else
      displeasure += S[left];
    left++;
  }

  // Posso prendere intero spiedino
  if (left == N)
    return strawdberries;

  left--;
  while (left >= 0 && S[left] != 0) {
    displeasure -= S[left];
    left--;
  }
  while (displeasure <= K) {
    if (S[right] == 0)
      strawdberries++;
    else
      displeasure += S[right];
    right--;
  }

  max = strawdberries;

  // Ritorno indietro controllando se ottengo risultati migliori
  while (left >= 0) {

    left--;
    while (left >= 0 && S[left] != 0) {
      displeasure -= S[left];
      left--;
    }
    strawdberries--;

    while (displeasure <= K) {
      if (S[right] == 0)
        strawdberries++;
      else
        displeasure += S[right];
      right--;
    }

    if (strawdberries > max)
      max = strawdberries;
  }

  return max;
}

int main(int argc, char *argv[]) {
  std::ifstream in("input.txt");

  int N, K;
  int S[N];

  in >> N >> K;

  for (int i = 0; i < N; i++)
    in >> S[i];

  std::cout << solve(N, K, S) << std::endl;
}
