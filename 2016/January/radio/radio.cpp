#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N, M, FX, FY, BX, BY;
string fj;
string b;

int dist(int x1, int y1, int x2, int y2) {
  return pow(x1-x2, 2) + pow(y1-y2, 2);
}

int main() {
  freopen("radio.in", "r", stdin);
  freopen("radio.out", "w", stdout);

  cin >> N >> M >> FX >> FY >> BX >> BY;
  cin >> fj >> b;

  vector<pair<int, int>> fjPos(N+1);
  int fx = FX;
  int fy = FY;
  fjPos[0] = make_pair(fx, fy);
  for (int i = 1; i <= N; i++) {
    if (fj[i-1] == 'N') {
      fy++;
    } else if (fj[i-1] == 'E') {
      fx++;
    } else if (fj[i-1] == 'S') {
      fy--;
    } else { // fj[i-1] == 'W'
      fx--;
    }
    fjPos[i] = make_pair(fx, fy);
  }

  vector<pair<int, int>> bPos(M+1);
  int bx = BX;
  int by = BY;
  bPos[0] = make_pair(bx, by);
  for (int i = 1; i <= M; i++) {
    if (b[i-1] == 'N') {
      by++;
    } else if (b[i-1] == 'E') {
      bx++;
    } else if (b[i-1] == 'S') {
      by--;
    } else { // fj[i-1] == 'W'
      bx--;
    }
    bPos[i] = make_pair(bx, by);
  }

  vector<vector<int>> dp(N+1, vector<int>(M+1));
  dp[0][0] = 0;
  for (int i = 0; i <= N; i++) {
    for (int j = 0; j <= M; j++) {
      if (i == 0 && j == 0) continue;
      dp[i][j] = min(i > 0 ? dp[i-1][j] : INT_MAX, 
                 min(j > 0 ? dp[i][j-1] : INT_MAX,
                     i>0 && j>0 ? dp[i-1][j-1] : INT_MAX))
                 + dist(fjPos[i].first, fjPos[i].second, bPos[j].first, bPos[j].second);
    }
  }

  cout << dp[N][M] << endl;

  return 0;
}