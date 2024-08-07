#include <bits/stdc++.h>

using namespace std;
using ld = long double;

ld formula(int q, ld a, ld b, ld ex) {
  return pow(a, q) * ex + b * (1 - pow(a, q)) / (1 - a);
}

int main() {
  // freopen("camp.in", "r", stdin);
  // freopen("camp.out", "w", stdout);

  int N, K;
  cin >> N >> K;
  ld n = N-1;

  vector<ld> t(N);
  // ld num = 1;
  // ld den = 1;
  ld cur = 1;
  const ld c = pow(0.5, n);

  for (int i = 0; i < N; i++) {
    t[i] = cur * c;
    // num *= n-i;
    // den *= i+1;
    cur *= (ld)(n-i)/(i+1);
  }

  vector<ld> pref(N); // prefix sum of percents from left to right
  pref[0] = t[0];
  for (int i = 1; i < N; i++) {
    pref[i] = pref[i-1] + t[i];
  }

  vector<ld> ev(N); // prefix sum of expected value from right to left
  ev[n] = t[n] * n;
  for (int i = n-1; i >= 0; i--) {
    ev[i] = ev[i+1] + t[i] * i;
  }

  ld curE = 0;
  for (int i = 0; i < K;) {
    int fe = floor(curE);
    ld a = pref[fe];
    ld b = ev[fe + 1];

    // binary search
    int low = 0;
    int high = K-i-1;
    ld newE;
    
    while (low < high) {
      int mid = low + (high - low + 1) / 2;
      newE = formula(mid, a, b, curE);

      if (floor(newE) == fe) {
        low = mid;
      } else {
        high = mid - 1;
      }
    }

    curE = a * formula(low, a, b, curE) + b;
    i += low + 1;
  }
  
  cout << setprecision(10) << curE + 1.0 << endl;

  return 0;
}