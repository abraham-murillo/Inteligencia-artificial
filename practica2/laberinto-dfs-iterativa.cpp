#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <class T>
T random(T l, T r) {
  return uniform_int_distribution<T>(l, r)(rng);
}

const int N = 20;
const int M = 20;
const int INF = 1e9 + 5;
char grid[N][M];
int dist[N][M];
int vis[N][M];
pair<int, int> from[N][M];
pair<int, int> start;
pair<int, int> target;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int timer = 0;

bool valid(int r, int c) {
  return 0 <= r && r < N && 0 <= c && c < M;
}

void createGrid() {
  start = make_pair(random(0, N - 1), random(0, N - 1));
  target = make_pair(random(0, M - 1), random(0, M - 1));
  grid[start.first][start.second] = 'S';
  grid[target.first][target.second] = 'E';

  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      if (make_pair(r, c) == start || make_pair(r, c) == target)
        continue;

      grid[r][c] = random(0, 1) == 0 ? ' ' : '#';
    }
  }
}

void printGrid() {
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      cout << grid[r][c];
    }

    cout << '\n';
  }

  cout << '\n';
}

struct Node {
  int r, c, dist;
};

int dfs(int sr, int sc) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      dist[i][j] = INF;

  stack<Node> stk;
  stk.push({.r = sr, .c = sc, .dist = 0});
  dist[sr][sc] = 0;
  from[sr][sc] = {-1, -1};

  while (!stk.empty()) {
    auto [r, c, d] = stk.top();
    stk.pop();

    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (valid(nr, nc) && grid[nr][nc] != '#') {
        if (d + 1 < dist[nr][nc]) {
          dist[nr][nc] = d + 1;
          from[nr][nc] = {r, c};
          stk.push({.r = nr, .c = nc, .dist = d + 1});
        }
      }
    }
  }

  return dist[target.first][target.second];
}

bool findShortestPath() {
  ++timer;
  return dfs(start.first, start.second) < INF;
}

void reconstructPath() {
  for (auto u = target; u != make_pair(-1, -1); u = from[u.first][u.second]) {
    if (u != target && u != start) {
      grid[u.first][u.second] = 'X';
    }
  }
}

int main() {
  do {
    createGrid();
  } while (!findShortestPath());

  printGrid();
  cout << "Número mínimo de movimientos: " << dfs(start.first, start.second) << '\n' << '\n';
  reconstructPath();
  printGrid();
  return 0;
}
