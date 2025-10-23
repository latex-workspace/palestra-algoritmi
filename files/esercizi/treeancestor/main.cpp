#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> ans;
vector<bool> visited;
vector<int> path;
int N, K;

// DFS like explore of tree.
void explore(vector<vector<int>> &graph, int node, int depth) {
  visited[node] = true;
  ans[node] = depth;
  path[depth] = node;

  if (depth >= K) {
    ans[node] = path[depth - K];
  } else {
    ans[node] = -1;
  }

  for (int i = 0; i < graph[node].size(); i++) {
    if (!visited[graph[node][i]])
      explore(graph, graph[node][i], depth + 1);
  }
}

int main() {

  // ifstream cin("input.txt");
  // ofstream cout("output.txt");

  cin >> N >> K;

  vector<vector<int>> graph;
  graph.resize(N);
  ans.resize(N);
  visited.resize(N, 0);
  path.resize(N);

  for (int i = 0; i < N - 1; ++i) {
    int X, Y;
    cin >> X >> Y;
    graph[X].push_back(Y);
    graph[Y].push_back(X);
  }

  explore(graph, 0, 0);

  for (int i = 0; i < N; ++i)
    cout << ans[i] << " ";
  cout << endl;

  return 0;
}
