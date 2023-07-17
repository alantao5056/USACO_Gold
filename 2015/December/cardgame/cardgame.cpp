#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N;

int main() {
  freopen("cardgame.in", "r", stdin);
  freopen("cardgame.out", "w", stdout);

  cin >> N;
  vector<bool> nums(2*N+1);
  vector<int> elsie1(N/2);
  vector<int> elsie2(N/2);
  for (int i = 0; i < N; i++) {
    if (i < N/2) {
      cin >> elsie1[i];
      nums[elsie1[i]] = true;
    } else {
      cin >> elsie2[i-N/2];
      nums[elsie2[i-N/2]] = true;
    }
  }
  vector<int> bessie1;
  vector<int> bessie2;
  for (int i = 1; i <= 2*N; i++) {
    if (nums[i]) continue;
    if (bessie2.size() < N/2) {
      bessie2.pb(i);
    } else {
      bessie1.pb(i);
    }
  }

  sort(elsie1.begin(), elsie1.end());
  sort(elsie2.begin(), elsie2.end());
  sort(bessie1.begin(), bessie1.end());
  sort(bessie2.begin(), bessie2.end());

  int e = 0;
  int b = 0;
  int result = 0;
  while (e < N/2 && b < N/2) {
    if (elsie1[e] < bessie1[b]) {
      e++;
      result++;
    }
    b++;
  }

  e = N/2-1;
  b = N/2-1;
  while (e >= 0 && b >= 0) {
    if (elsie2[e] > bessie2[b]) {
      e--;
      result++;
    }
    b--;
  }

  cout << result << endl;

  return 0;
}