#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <class T>
T random(T l, T r) {
  return uniform_int_distribution<T>(l, r)(rng);
}

const int N = 20;
const int M = 20;
char grid[N][M];
int dist[N][M];
bool vis[N][M];
pair<int, int> from[N][M];
pair<int, int> start;
pair<int, int> target;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

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

bool findShortestPath() {
  for (int r = 0; r < N; r++) {
    for (int c = 0; c < M; c++) {
      dist[r][c] = 0;
      vis[r][c] = false;
      from[r][c] = {-1, -1};
    }
  }

  queue<pair<int, int>> qu;
  qu.push(start);
  vis[start.first][start.second] = true;

  while (!qu.empty()) {
    auto [r, c] = qu.front();
    qu.pop();

    for (int i = 0; i < 4; i++) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (valid(nr, nc) && grid[nr][nc] != '#' && !vis[nr][nc]) {
        from[nr][nc] = {r, c};
        dist[nr][nc] = dist[r][c] + 1;
        qu.emplace(nr, nc);
        vis[nr][nc] = true;

        if (make_pair(nr, nc) == target) {
          return true;
        }
      }
    }
  }

  return false;
}

void reconstructPath() {
  for (auto u = target; u != make_pair(-1, -1); u = from[u.first][u.second]) {
    if (u != target && u != start) {
      grid[u.first][u.second] = 'X';
    }
  }
}

int main() {
  while (!findShortestPath()) {
    createGrid();
  }

  printGrid();
  cout << "Número mínimo de movimientos: " << dist[target.first][target.second] << '\n' << '\n';
  reconstructPath();
  printGrid();
  return 0;
}
