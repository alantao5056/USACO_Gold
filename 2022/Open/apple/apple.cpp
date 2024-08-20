#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

int N;

struct P {
  bool type = false;
  int x, y, cnt;
  bool operator<(const P&a) const {
    if (x != a.x) return x < a.x;
    return y < a.y;
  }
};

struct comp {
  inline bool operator() (const P& a, const P& b) {
    if (a.y != b.y) return a.y > b.y;
    return a.x > b.x;
  }
};

int main() {
  // freopen("apple.in", "r", stdin);
  // freopen("apple.out", "w", stdout);

  cin >> N;
  vector<P> vp(N);
  for (int i = 0; i < N; i++) {
    int q, t, x, n; cin >> q >> t >> x >> n;

    vp[i].type = q-1;
    vp[i].x = t+x;
    vp[i].y = t-x;
    vp[i].cnt = n;
  }

  sort(vp.begin(), vp.end(), comp());
  
  set<P> sp;
  int tot = 0;

  for (int i = 0; i < N; i++) {
    if (vp[i].type) {
      // apple
      sp.insert(vp[i]);
    } else {
      // cow
      auto it = sp.lower_bound(vp[i]);
      P temp;

      while (it != sp.end() && vp[i].cnt > 0) {
        if (it->cnt > vp[i].cnt) {
          // take partial
          tot += vp[i].cnt;
          temp.type = true; temp.x = it->x; temp.y = it->y; temp.cnt = it->cnt - vp[i].cnt;
          vp[i].cnt = 0;
        } else {
          // take all
          tot += it->cnt;
          vp[i].cnt -= it->cnt;
        }
        sp.erase(it++);
      }

      if (temp.type) {
        sp.insert(temp);
      }
    }
  }

  cout << tot << endl;

  return 0;
}