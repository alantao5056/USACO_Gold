#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N;

int main() {
  freopen("circlecross.in", "r", stdin);
  freopen("circlecross.out", "w", stdout);

  cin >> N;
  vector<int> arr(N*2);
  vector<pii> intervals(N, {-1, -1});
  for (int i = 0; i < 2*N; i++){
    cin >> arr[i];
    arr[i]--;

    if (intervals[arr[i]].first == -1) {
      intervals[arr[i]].first = i;
    } else {
      intervals[arr[i]].second = i;
    }
  }

  // for (int i = 0; i < N; i++) {
  //   cout << intervals[i].first << " " << intervals[i].second << endl;
  // }

  sort(intervals.begin(), intervals.end(), [](auto &left, auto &right) {
    return left.second < right.second;
  });

  set<int> start;
  int result = 0;
  for (pii i : intervals) {
    int I = distance(start.upper_bound(i.first), start.end());

    result += (i.second - i.first - 1 - 2*I);

    start.insert(i.first);
  }

  cout << result/2 << endl;

  return 0;
}