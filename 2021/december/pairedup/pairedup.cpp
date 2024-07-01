#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;

int T, N, K;
int INF = 1e9;

int main() {
  // freopen("pairedup.in", "r", stdin);
  // freopen("pairedup.out", "w", stdout);

  cin >> T >> N >> K;

  vector<pii> cows(N+2);
  int tot = 0;
  for (int i = 1; i <= N; i++) {
    cin >> cows[i].first >> cows[i].second;
    tot += cows[i].second;
  }

  cows[0] = {-1e9-1, 0};
  cows[N+1] = {2e9+1, 0};

  sort(cows.begin(), cows.end());

  vector<pii> pa(N+1); // prev after
  for (int i = 1; i <= N; i++) {
    pa[i].first = cows[i].first - cows[i-1].first;
    pa[i].second = cows[i+1].first - cows[i].first;
  }

  if (T == 1) {
    int t1 = 0;
    int start = 1;
    for (int i = 1; i <= N; i++) {
      if (pa[i].second > K) {
        // out of reach
        if ((i-start+1)%2==1) {
          // cannot pair all
          int minRem = min(cows[start].second, cows[i].second);
          for (int j = 0; j < i-start+1; j++) {
            if (j%2==0 || pa[start+j].first + pa[start+j].second <= K) {
              // automatically canidate
              minRem = min(minRem, cows[start+j].second);
            }
          }

          t1 += minRem;
        }
        start = i+1;
      }
    }
    cout << t1 << endl;
  } else {
    // t2
    int t2 = 0;
    vector<pii> dp;
    vector<pii> cur;
    cur.push_back({-INF-1, 0});
    dp.push_back({0, -INF});
    for (int i = 1; i <= N; i++) {
      cur.push_back(cows[i]);
      dp.push_back({0, 0});
      if (pa[i].second > K) {
        int n = dp.size()-1;
        // new group
        for (int j = 1; j <= n+1; j++) {
          dp[j] = dp[j-1];
          int ub = upper_bound(cur.begin(), cur.end(), make_pair(cur[j].first - K - 1, INF)) - cur.begin() - 1;
          int idx = i-n+j;
          
          if (pa[idx].first + pa[idx].second <= K || j%2==0) {
            dp[j].first = max(dp[j].first, dp[ub].second + cur[j].second);
          }
          if (pa[idx].first + pa[idx].second <= K || j%2==1) {
            dp[j].second = max(dp[j].second, dp[ub].first + cur[j].second);
          }
        }

        if (n%2==0) {
          t2 += dp[n].first;
        } else {
          t2 += dp[n].second;
        }

        cur.clear();
        dp.clear();
        cur.push_back({-INF-1, 0});
        dp.push_back({0, -INF});
      }

      
    }

    cout << t2 << endl;
  }
  
  return 0;
}