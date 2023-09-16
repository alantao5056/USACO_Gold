#include <bits/stdc++.h>
using namespace std;

// TYPES
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vb vector<bool>
#define vc vector<char>;
#define vs vector<string>;
#define mii map<int, int>
#define si set<int>
#define sc set<char>

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

int N, K;

vector<vi> graph;
vi color;
vector<vll> dp;

void recursive(int n, int prev, int c, int prevC) {
  if (color[n] != -1) {
    if (c != color[n]) {
      dp[n][c] = 0;
      return;
    }
  }
  dp[n][c] = 1;
  for (int nb : graph[n]) {
    if (nb == prev) continue;
    if (color[nb] == c) {
      // same color as assigned color
      dp[n][c] = 0;
      return;
    }
    int sum = 0;
    cf(j, 0, 2) {
      if (j == c) continue;
      if (dp[nb][j] == -1) {;
        recursive(nb, n, j, c);
      }

      sum += dp[nb][j];
    }

    dp[n][c] *= sum;
  }
}

int main() {
  freopen("barnpainting.in", "r", stdin);
  freopen("barnpainting.out", "w", stdout);

  cin >> N >> K;
  graph.resize(N, vi());
  color.resize(N, -1);
  dp.resize(N, vll(3, -1));

  f(i, 0, N-1) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    graph[a].pb(b);
    graph[b].pb(a);
  }

  f(i, 0, K) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    color[a] = b;
  }

  recursive(0, -1, 0, -1);
  recursive(0, -1, 1, -1);
  recursive(0, -1, 2, -1);

  // f(i, 0, N) {
  //   f(j, 0, 3) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << endl;
  // }

  cout << dp[0][0] + dp[0][1] + dp[0][2] << endl;

  return 0;
}