#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N;
struct V {
  int x, y;
  int id;
  int angle;
  int prevLen;
  int minDist;

  V(int id_) {
    id = id_;
  }

  void defPrevLen(V& prev) {
    prevLen = abs(prev.x - x) + abs(prev.y - y);
  }
  void defAngle(V& prev, V& next) {
    // 90
    if ((x > prev.x && next.y < y) || 
        (y < prev.y && next.x < x) ||
        (x < prev.x && next.y > y) ||
        (y > prev.y && next.x > x))
    {
      angle = 90;
    } else { // 270
      angle = 270;
    }
  }
};

int main() {
  freopen("lightsout.in", "r", stdin);
  freopen("lightsout.out", "w", stdout);

  cin >> N;
  vector<V> poly(N, V(-1));
  poly[0] = V(0);
  cin >> poly[0].x >> poly[0].y;
  int totDist = 0;
  for (int i = 1; i < N-1; i++) {
    poly[i] = V(i);
    cin >> poly[i].x >> poly[i].y;
    poly[i].defPrevLen(poly[i-1]);
    totDist += poly[i].prevLen;
    // poly[i].defAngle(poly[i-1], poly[i+1]);
  }

  poly[N-1] = V(N-1);
  cin >> poly[N-1].x >> poly[N-1].y;
  poly[N-1].defPrevLen(poly[N-2]);
  totDist += poly[N-1].prevLen;
  poly[N-1].defAngle(poly[N-2], poly[0]);

  poly[0].defPrevLen(poly[N-1]);
  totDist += poly[0].prevLen;
  poly[0].defAngle(poly[N-1], poly[1]);

  poly[0].minDist = 0;
  poly[N-1].minDist = poly[0].prevLen;

  int lDist = 0;
  int rDist = totDist;
  for (int i = 1; i < N-1; i++) {
    lDist += poly[i].prevLen;
    rDist -= poly[i].prevLen;
    poly[i].defAngle(poly[i-1], poly[i+1]);
    poly[i].minDist = min(lDist, rDist);
  }

  int maxDiff = 0;
  for (int i = 1; i < N; i++) {
    vector<int> possible;
    for (int j = 1; j < N; j++) {
      if (j == i) continue;
      if (poly[j].angle == poly[i].angle) {
        possible.pb(j);
      }
    }

    if (possible.empty()) {
      continue;
    }

    int dist = 0;
    bool found = false;
    for (int j = i+1; j < N; j++) {
      dist += poly[j].prevLen;
      vector<int> possible_;
      for (int p : possible) {
        p++;
        if (poly[j].angle == poly[p].angle && poly[j].prevLen == poly[p].prevLen) {
          possible_.pb(p);
        }
      }

      if (possible_.empty()) {
        dist += poly[j].minDist;
        found = true;
        break;
      }
      possible = possible_;
    }

    if (!found) {
      dist += poly[0].prevLen;
    }

    maxDiff = max(maxDiff, dist - poly[i].minDist);
  }

  cout << maxDiff << endl;

  return 0;
}