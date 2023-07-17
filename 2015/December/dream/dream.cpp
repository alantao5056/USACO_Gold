#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N, M;
int i_[] = {1, 0, -1, 0};
int j_[] = {0, 1, 0, -1};

int main()
{
  freopen("dream.in", "r", stdin);
  freopen("dream.out", "w", stdout);

  cin >> N >> M;

  vector<vector<int>> grid(N + 2, vector<int>(M + 2));

  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= M; j++)
    {
      cin >> grid[i][j];
    }
  }

  // bfs
  vector<vector<int>> visited(N + 2, vector<int>(M + 2)); // 1 no orange, 2 yes orange, 3 both
  queue<pii> q;
  q.push({1, 1});
  queue<pair<bool, int>> q2;
  q2.push({false, 0});
  visited[1][1] = 1;
  int result = INT_MAX;
  while (!q.empty())
  {
    int i = q.front().first;
    int j = q.front().second;
    q.pop();
    bool orange = q2.front().first;
    int moves = q2.front().second;
    q2.pop();

    if (i == N && j == M)
    {
      result = min(result, moves);
      continue;
    }

    for (int k = 0; k < 4; k++)
    {
      int i2 = i + i_[k];
      int j2 = j + j_[k];
      //   if (visited[i2][j2] == 3) {
      //     continue;
      //   }

      bool orange2 = orange;
      int moves2 = moves;

      if (grid[i2][j2] == 4)
      {
        orange2 = false;
        // slide
        if (k == 0)
        {
          // down
          while (grid[i2][j2] == 4)
          {
            i2++;
            moves2++;
          }
          if (grid[i2][j2] == 0 || grid[i2][j2] == 3)
          {
            i2--;
            moves2--;
          }
        }
        else if (k == 1)
        {
          // right
          while (grid[i2][j2] == 4)
          {
            j2++;
            moves2++;
          }
          if (grid[i2][j2] == 0 || grid[i2][j2] == 3)
          {
            j2--;
            moves2--;
          }
        }
        else if (k == 2)
        {
          // up
          while (grid[i2][j2] == 4)
          {
            i2--;
            moves2++;
          }
          if (grid[i2][j2] == 0 || grid[i2][j2] == 3)
          {
            i2++;
            moves2--;
          }
        }
        else
        {
          // left
          while (grid[i2][j2] == 4)
          {
            j2--;
            moves2++;
          }
          if (grid[i2][j2] == 0 || grid[i2][j2] == 3)
          {
            j2++;
            moves2--;
          }
        }
      }

      moves2++;

      if (grid[i2][j2] == 1 && (visited[i2][j2] == 0 || visited[i2][j2] == (orange2 ? 1 : 2)))
      {
        // can step
        q.push({i2, j2});
        q2.push({orange2, moves2});
        if (visited[i2][j2] == 0)
        {
          visited[i2][j2] = orange2 ? 2 : 1;
        }
        else
        {
          visited[i2][j2] = 3;
        }
      }
      else if (grid[i2][j2] == 2 && visited[i2][j2] == 0)
      {
        q.push({i2, j2});
        q2.push({true, moves2});
        visited[i2][j2] = 2;
      }
      else if (grid[i2][j2] == 3 && visited[i2][j2] == 0 && orange2)
      {
        q.push({i2, j2});
        q2.push({true, moves2});
        visited[i2][j2] = 2;
      }
      else if (grid[i2][j2] == 4 && visited[i2][j2] == 0)
      {
        q.push({i2, j2});
        q2.push({false, moves2});
        visited[i2][j2] = 1;
      }
    }
  }

  cout << ((result == INT_MAX) ? -1 : result) << endl;

  return 0;
}