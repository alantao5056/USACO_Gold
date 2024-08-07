#include <bits/stdc++.h>

using namespace std;

int main() {
  freopen("camp.in", "r", stdin);
  freopen("camp.out", "w", stdout);

  int N, K; cin >> N >> K;
  double n = N-1;

  // t array
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
  
  // k array
  vector<double> k(N);
  const double half = 1-(n/K);
  const double maxK = min(K, 10000);
  double cc = 1;
  for (int i = 1; i < maxK; i++) {
    cc += pow(half, i);
  }

  for (int i = 0; i < N; i++) {
    if (i <= n-(n/K)) {
      k[i] = pow(half, K-1) * t[i];
    } else {
      k[i] = cc * t[i];
    }
  }

  // answer
  double ans = 0;
  for (int i = 0; i < N; i++) {
    ans += k[i] * i;
  }

  cout << ans + 1 << endl;

  return 0;
}