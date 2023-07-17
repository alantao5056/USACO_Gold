#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N;

ll energy(int s, int e) {
  return pow(s-e, 2);
}

int main() {
  freopen("cbarn.in", "r", stdin);
  freopen("cbarn.out", "w", stdout);

  cin >> N;
  vector<int> barn(N);
  int low = INT_MAX;
  int start = 0;
  int cur = 0;
  for (int i = 0; i < N; i++) {
    cin >> barn[i];

    cur += barn[i]-1;
    if (cur <= low) {
      low = cur;
      start = i;
    }
  }

  start++;
  start %= N;

  rotate(barn.begin(), barn.begin()+start, barn.end());

  int d = 0;
  ll result = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < barn[i]; j++) {
      result += energy(i, d);
      d++;
    }
  }

  cout << result << endl;

  return 0;
}