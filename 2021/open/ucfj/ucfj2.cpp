#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N;

vector<int> bit;

// kind of like adding instead of updating
void update(int pos, int val) {
  pos++; // bit tree starts at 1
  while (pos <= N) {bit[pos] += val; pos += (pos&(-pos));}
}

int query(int pos) {
  pos++; // bit tree starts at 1
  int r = 0;
  while (pos > 0) { r+= bit[pos]; pos = pos- (pos&(-pos));} return r;
}

int main() {
  // freopen("ucfj.in", "r", stdin);
  // freopen("ucfj.out", "w", stdout);

  cin >> N;
  bit.resize(N+1);
  vector<int> cows(N);
  for (int i = 0; i < N; i++) {
    cin >> cows[i];
  }

  vector<int> rec(N, -1);
  ll result = 0;
  for (int i = 0; i < N; i++) {
    if (rec[cows[i]] == -1) {
      // first appearence
      result += query(i-1);
    } else{
      result += query(i-1) - query(rec[cows[i]]);
      update(rec[cows[i]], -1);
    }
    update(i, 1);
    rec[cows[i]] = i;
  }

  cout << result << endl;

  return 0;
}