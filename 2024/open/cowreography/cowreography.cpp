#include <bits/stdc++.h>

using namespace std;

int N, K;

int main() {
  freopen("cowreography.in", "r", stdin);
  freopen("cowreography.out", "w", stdout);

  cin >> N >> K;

  string start, finish;

  cin >> start >> finish;

  vector<int> s(N);
  vector<int> f(N);
  int l = -1;
  int r = -1;

  for (int i = 0; i < N; i++) {
    s[i] = start[i] == '1' ? 1 : 0;
    f[i] = finish[i] == '1' ? 1 : 0;
    if (s[i] == 1 && f[i] == 1) {
      s[i] = 0;
      f[i] = 0;
    }
    if (l == -1 && s[i] == 1) l = i;
    if (r == -1 && f[i] == 1) r = i;
  }

  if (l==-1) {
    cout << 0 << endl;
    return 0;
  }

  int result = 0;
  while (l < N && r < N) {
    if (l == r) {
      s[l]--;
      f[r]--;
      while (l < N && s[l] == 0) {
        l++;
      }

      while (r < N && f[r] == 0) {
        r++;
      }

    } else if (l < r) {
      if (l + K >= r)
      { // can reach in one step
        f[r]--;
        s[l]--;

        while (r < N && f[r] == 0) {
          r++;
        }
      } else {
        s[l]--;
        s[l+K]++;
      }

      while (l < N && s[l] == 0) {
        l++;
      }
      
      result++;
    } else {
      if (r + K >= l)
      { // can reach in one step
        s[l]--;
        f[r]--;

        while (l < N && s[l] == 0) {
          l++;
        }
      } else {
        f[r]--;
        f[r+K]++;
      }

      while (r < N && f[r] == 0) {
        r++;
      }

      result++;
    }
  }

  cout << result << endl;

  return 0;
}