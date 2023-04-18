#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N;

struct Hay {
  int pos;
  int left;
  int right;
};

// struct less_than_key {
//   inline bool operator() (const Hay& struct1, const Hay& struct2) {
//     return (struct1.pos < struct2.pos);
//   }
// };

vector<Hay> hays;

bool check(int len) {
  int l = 0;
  int r = 0;
  while (l < N) {
    int end = hays[l].pos + len;
    while (r < N && hays[r].pos <= end) {
      r++;
    }

    // l and r-1 are endpoints
    if (len/2 >= hays[l].left+1 && len/2 >= hays[r-1].right+1) {
      // can explode
      return true;
    }
    l++;
  }
  return false;
}

int main() {
  freopen("angry.in", "r", stdin);
  freopen("angry.out", "w", stdout);

  cin >> N;
  for (int i = 0; i < N; i++) {
    Hay h;
    cin >> h.pos;
    hays.pb(h);
  }

  sort(hays.begin(), hays.end(), [ ]( const auto& lhs, const auto& rhs )
  {
    return lhs.pos < rhs.pos;
  });

  // do left
  int l = 0;
  int r = 1;
  while (l < N && r < N) {
    int end = hays[l].pos + hays[l].left;
    while (r < N && hays[r].pos <= end) {
      hays[r].left = hays[l].left + 1;
      r++;
    }

    if (hays[r-1].pos == hays[l].pos) {
      // there are no hays
      hays[r].left = hays[r].pos - hays[l].pos;
      l++;
    } else {
      l = r-1;
    }
    r = l+1;
  }

  // do right
  l = N-1;
  r = N-2;
  while (l >= 0 && r >= 0) {
    int end = hays[l].pos - hays[l].right;
    while (r >= 0 && hays[r].pos >= end) {
      hays[r].right = hays[l].right + 1;
      r--;
    }

    if (hays[r+1].pos == hays[l].pos) {
      // there are no hays
      hays[r].right = hays[l].pos - hays[r].pos;
      l--;
    } else {
      l = r+1;
    }
    r = l-1;
  }

  int low = 0;
  int high = 1000000000;
  
  while (low < high) { // notice we do not compare element at mid with our target
    int mid = low + (high - low) / 2;
    if (check(mid)) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }

  cout << to_string(low / 2) << ".0" << endl;

  return 0;
}