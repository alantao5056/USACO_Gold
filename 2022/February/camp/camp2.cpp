#include <bits/stdc++.h>

using namespace std;

int main() {
  // freopen("camp.in", "r", stdin);
  // freopen("camp.out", "w", stdout);

  int N, K;
  cin >> N >> K;
  double n = N-1;

  vector<double> t(N);
  // double num = 1;
  // double den = 1;
  double cur = 1;
  const double c = pow(0.5, n);

  for (int i = 0; i < N; i++) {
    t[i] = cur * c;
    // num *= n-i;
    // den *= i+1;
    cur *= (double)(n-i)/(i+1);
  }

  vector<double> pref(N); // prefix sum of percents from left to right
  pref[0] = t[0];
  for (int i = 1; i < N; i++) {
    pref[i] = pref[i-1] + t[i];
  }

  vector<double> ev(N); // prefix sum of expected value from right to left
  ev[n] = t[n] * n;
  for (int i = n-1; i >= 0; i--) {
    ev[i] = ev[i+1] + t[i] * i;
  }

  vector<double> et(K+1);
  et[0] = 0;

  for (int i = 1; i <= K; i++) {
    double ps = pref[floor(et[i-1])];
    et[i] = ev[floor(et[i-1]) + 1] + ps * et[i-1];
  }
  
  cout << setprecision(10) << et[K]+1.0 << endl;

  return 0;
}