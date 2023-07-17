#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

int N, K;

int main() {
  freopen("lineup.in", "r", stdin);
  freopen("lineup.out", "w", stdout);

  cin >> N >> K;
  vector<int> cows(N);
  for (int i = 0; i < N; i++) {
    cin >> cows[i];
  }

  map<int, int> ba;
  map<int, set<int>> ab;

  int i = 0;
  int j = 0;
  int result = 0;
  ba[cows[0]]++;
  ab[1].insert(cows[0]);
  while (i < N && j < N-1) {
    while (ba.size() <= K+1) {
      j++;
      if (j == N) {
        j--;
        break;
      }

      if (ba.size() == K+1 && ba.find(cows[j]) == ba.end()) {
        j--;
        break;
      }

      ba[cows[j]]++;
      ab[ba[cows[j]]].insert(cows[j]);
      if (ba[cows[j]] > 1) {
        ab[ba[cows[j]]-1].erase(cows[j]);
        if (ab[ba[cows[j]]-1].size() == 0) {
          ab.erase(ba[cows[j]]-1);
        }
      }
    }

    result = max(result, ab.rbegin()->first);

    ba[cows[i]]--;
    bool none = false;
    if (ba[cows[i]] == 0) {
      none = true;
      ba.erase(cows[i]);
    }

    if (none) {
      ab[1].erase(cows[i]);
      if (ab[1].size() == 0) {
        ab.erase(1);
      }
    } else {
      ab[ba[cows[i]]+1].erase(cows[i]);
      if (ab[ba[cows[i]]+1].size() == 0) {
        ab.erase(ba[cows[i]]+1);
      }
      ab[ba[cows[i]]].insert(cows[i]);
    }

    i++;
  }

  cout << result << endl;

  return 0;
}