#include <bits/stdc++.h>

using namespace std;

int N;

int main() {
  // freopen("hilo.in", "r", stdin);
  // freopen("hilo.out", "w", stdout);

  cin >> N;

  vector<int> perm(N);
  vector<int> merp(N+1);
  vector<vector<int>> hist(N+1);
  set<int> prev;
  for (int i = 0; i < N; i++) {
    cin >> perm[i];
    merp[perm[i]] = i;
    auto it = prev.lower_bound(perm[i]);
    if (it == prev.begin()) {
      hist[0].push_back(i);
    } else {
      it--;
      hist[*it].push_back(i);
    }

    prev.insert(perm[i]);
  }

  set<int> hi;
  stack<int> lo;
  map<int, bool> hilo{{-1, false}, {N+1, true}};

  int curTot = 0;
  for (int i = 0; i <= N; i++) {
    for (int h : hist[i]) {
      hi.insert(h);

      auto it = hilo.lower_bound(h);
      if (!it->second && !((it--)->second)) {
        curTot++;
      }

      hilo[h] = true;
    }

    cout << curTot << endl;

    // i becomes low
    if (i == N) continue;

    hi.erase(merp[i+1]);
    while (!lo.empty() && merp[i+1] < lo.top()) {
      auto it = hilo.lower_bound(lo.top());
      if ((--it)->second) {
        curTot--;
      }
      hilo.erase(lo.top());
      lo.pop();
    }

    bool prev = (--hilo.lower_bound(merp[i+1]))->second;
    bool next = (++hilo.lower_bound(merp[i+1]))->second;
    if (prev && next) {
      curTot++;
    } else if (!next) {
      curTot--;
    }
    hi.erase(merp[i+1]);
    lo.push(merp[i+1]);
    hilo[merp[i+1]] = false;
  }

  return 0;
}