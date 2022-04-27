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
int mem[N][M];
int done[N][M];
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

int dfs(int r, int c) {
  if (!valid(r, c) || grid[r][c] == '#')
    return INF;

  if (make_pair(r, c) == target)
    return 0;

  int& mn = mem[r][c];

  if (done[r][c] == timer)
    return mn;

  mn = INF;
  done[r][c] = timer;

  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];
    mn = min(mn, dfs(nr, nc) + 1);
  }

  return mn;
}

void reconstructPath(int r, int c) {
  if (make_pair(r, c) == target)
    return;

  if (!valid(r, c) || grid[r][c] == '#')
    return;

  int mn = dfs(r, c);

  for (int i = 0; i < 4; i++) {
    int nr = r + dr[i];
    int nc = c + dc[i];

    if (mn == dfs(nr, nc) + 1 && make_pair(nr, nc) != target) {
      grid[nr][nc] = 'X';
      reconstructPath(nr, nc);
    }
  }
}

bool findShortestPath() {
  ++timer;
  return dfs(start.first, start.second) < INF;
}

int main() {
  do {
    createGrid();
  } while (!findShortestPath());

  printGrid();
  cout << "Número mínimo de movimientos: " << dfs(start.first, start.second) << '\n' << '\n';
  reconstructPath(start.first, start.second);
  printGrid();
  return 0;
}
