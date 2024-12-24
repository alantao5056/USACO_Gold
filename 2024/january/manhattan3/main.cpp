#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

int N, Q, V, H;

vector<int> vert;
vector<int> hori;

pii simul(int vi, int hi, int dl, int dw) {
  if (dw%2) {
    // right
    if (vi + 1 == V) {
      return {vert[vi] + dl, hori[hi]};
    }

    int dist = vert[vi+1] - vert[vi];
    if (dl <= dist) {
      return {vert[vi] + dl, hori[hi]};
    }

    dl -= dist;
    dw += dist;
    return simul(vi+1, hi, dl, dw);
  } else {
    // up
    if (hi + 1 == H) {
      return {vert[vi], hori[hi] + dl};
    }

    int dist = hori[hi+1] - hori[hi];
    if (dl <= dist) {
      return {vert[vi], hori[hi] + dl};
    }

    dl -= dist;
    dw += dist;
    return simul(vi, hi+1, dl, dw);
  }
}

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  // freopen("1.in", "r", stdin);
  // freopen("1.out", "w", stdout);

  cin >> N >> Q;

  for (int i = 0; i < N; i++) {
    char c; int x; cin >> c >> x;
    if (c == 'V') {
      vert.push_back(x);
    } else {
      hori.push_back(x);
    }
  }

  V = vert.size();
  H = hori.size();

  sort(vert.begin(), vert.end());
  sort(hori.begin(), hori.end());

  for (int i = 0; i < Q; i++) {
    int x, y, d; cin >> x >> y >> d;
    int xi = lower_bound(vert.begin(), vert.end(), x) - vert.begin();
    int yi = lower_bound(hori.begin(), hori.end(), y) - hori.begin();

    bool xb = xi != V && vert[xi] == x;
    bool yb = yi != H && hori[yi] == y;

    int dist = 0;
    if (xb && yb) {
    } else if (xb) {
      // on vertical road
      if (yi < H) {
        dist = hori[yi] - y;
        if (d <= dist) {
          cout << x << " " << y+d << endl;
          continue;
        }
      } else {
        cout << x << " " << y+d << endl;
        continue;
      }

      d -= dist;
    } else {
      // on horizontal road
      if (xi < V) {
        dist = vert[xi] - x;
        if (d <= dist) {
          cout << x+d << " " << y << endl;
          continue;
        }
      } else {
        cout << x+d << " " << y << endl;
        continue;
      }

      d -= dist;
    }
    pii ans = simul(xi, yi, d, dist);
    cout << ans.first << " " << ans.second << endl;
  }

  return 0;
}