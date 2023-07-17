#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int T, A, B;

int main() {
  freopen("feast.in", "r", stdin);
  freopen("feast.out", "w", stdout);

  cin >> T >> A >> B;

  vector<bool> yes(T+1);
  yes[0] = true;
  yes[A] = true;
  yes[B] = true;
  for (int i = 0; i <= T; i++) {
    if (yes[i]) continue;
    if (i >= A && yes[i-A]) {
      yes[i] = true;
    } else if (i >= B && yes[i-B]) {
      yes[i] = true;
    }
  }

  int ans1;
  for (int i = T; i >= 0; i--) {
    if (yes[i]) {
      ans1 = i;
      break;
    }
  }

  int ans2;
  for (int i = T-A/2; i >= 0; i--) {
    if (yes[i]) {
      ans2 = i;
      break;
    }
  }

  int ans3;
  for (int i = T-B/2; i >= 0; i--) {
    if (yes[i]) {
      ans3 = i;
      break;
    }
  }

  int ans4 = -1000000000;
  if (A + B <= T) {
    for (int i = T-A/2-B/2; i >= 0; i--) {
      if (yes[i]) {
        ans4 = i;
        break;
      }
    }
  }

  if (T-ans1 < T-A/2-ans2 && T-ans1 < T-B/2-ans3 && T-ans1 < T-A/2-B/2-ans4) {
    cout << ans1 << endl;
  } else if (T-A/2-ans2 < T-B/2-ans3 && T-A/2-ans2 < T-A/2-B/2-ans4) {
    cout << ans2 + A/2 << endl;
  } else if (T-B/2-ans3 < T-A/2-B/2-ans4) {
    cout << ans3 + B/2 << endl;
  } else {
    cout << ans4 + A/2 + B/2 << endl;
  }

  return 0;
}