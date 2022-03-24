// https://classroom.google.com/c/NDUzNTYwMTE5MjUz/a/NDUzNTYwMTE5Mjgz/details
// Solución al problema puzzle búsqueda en amplitud

#include <bits/stdc++.h>
using namespace std;

// Mersenne Twister pseudo-random generator of 32-bit numbers (https://www.cplusplus.com/reference/random/mt19937/)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Matrix : array<array<int, 3>, 3> {
  int toInt() const {
    auto mat = *this;
    int num = 0;
    for (auto row : mat)
      for (int x : row)
        num = num * 10 + x;
    return num;
  }

  bool operator==(const Matrix& other) const {
    return toInt() == other.toInt();
  }

  pair<int, int> zeroPos() {
    auto& mat = *this;
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < 3; j++)
        if (mat[i][j] == 0)
          return make_pair(i, j);
    return make_pair(-1, -1);
  }

  bool operator<(const Matrix& other) const {
    return toInt() < other.toInt();
  }

  friend ostream& operator<<(ostream& os, const Matrix& mat) {
    for (auto row : mat) {
      for (auto x : row)
        os << x << " ";
      os << '\n';
    }
    return os;
  }
};

Matrix getMatrix(vector<int> gen) {
  Matrix mat;
  for (int pos = 0; pos < gen.size(); pos++) {
    mat[pos / 3][pos % 3] = gen[pos];
  }
  return mat;
}

Matrix getRandomMatrix() {
  // Crea una matrix aleatoria
  vector<int> gen(9);
  iota(gen.begin(), gen.end(), 0);
  shuffle(gen.begin(), gen.end(), rng);
  return getMatrix(gen);
}

const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool validPos(int row, int col) {
  return 0 <= row && row < 3 && 0 <= col && col < 3;
}

int main() {
  Matrix start;
  start = getMatrix({5, 1, 6, 8, 7, 2, 0, 3, 4});
  // start = getMatrix({1, 3, 4, 8, 6, 2, 0, 7, 5});
  // start = getRandomMatrix();
  cout << "Estado random:\n";
  cout << start << '\n';

  Matrix end;
  // end = getMatrix({1, 2, 3, 8, 0, 4, 7, 6, 5});
  end = getMatrix({0, 1, 2, 3, 4, 5, 6, 7, 8});

  set<Matrix> vis;
  stack<pair<Matrix, int>> dfs;
  int answer = -1;

  dfs.push({start, 0});
  vis.insert(start);
  while (!dfs.empty()) {
    auto [cur, depth] = dfs.top();
    dfs.pop();

    if (cur == end) {
      // Alcanzó la solución, al ser búsqueda en profundidad es la primera vez que llega, pero puede que no sea la mejor solución
      answer = depth;
      break;
    }

    if (depth <= 100) {
      auto zeroPos = cur.zeroPos();

      for (auto dir : directions) {
        auto nxtZeroPos = zeroPos;
        nxtZeroPos.first += dir.first;
        nxtZeroPos.second += dir.second;

        if (!validPos(nxtZeroPos.first, nxtZeroPos.second)) {
          continue;
        }

        Matrix nxt = cur;
        swap(nxt[zeroPos.first][zeroPos.second], nxt[nxtZeroPos.first][nxtZeroPos.second]);

        if (!vis.count(nxt)) {
          // No está este nuevo estado, lo agregamos en la pila de recursión
          vis.insert(nxt);
          dfs.push({nxt, depth + 1});
        }
      }
    }
  }

  if (answer >= 0) {
    cout << "Estado final alcanzado en " << answer << " movimientos\n";
    cout << end << '\n';
  } else {
    cout << "No se puede resolver\n";
    cout << "Se probaron " << vis.size() << " tableros distintos\n";
  }

  return 0;
}