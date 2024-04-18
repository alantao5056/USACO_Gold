#include <bits/stdc++.h>

using namespace std;

int N, K;

typedef long long ll;

struct Node {
  int idx;
  int val;
  ll dist = LLONG_MAX;
  vector<int> next;
  vector<int> prev;
};

vector<Node> nodes;

int main() {

  // freopen("telephone.in", "r", stdin);
  // freopen("telephone.out", "w", stdout);

  cin >> N >> K;

  nodes.resize(N);
  vector<vector<int>> pos(K, vector<int>());
  for (int i = 0; i < N; i++) {
    nodes[i].idx = i;
    cin >> nodes[i].val;
    nodes[i].val--;
    pos[nodes[i].val].push_back(i);
  }

  vector<vector<bool>> cango(K, vector<bool>(K));
  for (int i = 0; i < K; i++) {
    string line; cin >> line;
    for (int j = 0; j < K; j++) {
      cango[i][j] = line[j] == '1' ? true : false;
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < K; j++) {
      if (cango[nodes[i].val][j]) {
        // update left and right
        auto l = lower_bound(pos[j].begin(), pos[j].end(), i) - 1;
        auto r = upper_bound(pos[j].begin(), pos[j].end(), i);

        if (l >= pos[j].begin()) {
          nodes[i].prev.push_back(*l);
        }
        
        if (r < pos[j].end()) {
          nodes[i].next.push_back(*r);
        }
      }
    }
  }

  priority_queue<pair<ll, int>> pq; 

  nodes[0].dist = 0;
  pq.push({0, 0});

  ll result = LLONG_MAX;
  int last = nodes[N-1].val;

  while (!pq.empty()) {
    pair<ll, int> cur = pq.top(); pq.pop();

    if (cango[nodes[cur.second].val][last]) {
      result = min(result, nodes[cur.second].dist + N-1-cur.second);
    }

    for (int n : nodes[cur.second].next) {
      int newDist = nodes[cur.second].dist + nodes[n].idx - nodes[cur.second].idx;
      if (newDist < nodes[n].dist) {
        nodes[n].dist = newDist;
        pq.push({newDist, n});
      }
    }

    for (int p : nodes[cur.second].prev) {
      int newDist = nodes[cur.second].dist + nodes[cur.second].idx - nodes[p].idx;
      if (newDist < nodes[p].dist) {
        nodes[p].dist = newDist;
        pq.push({newDist, p});
      }
    }
  }

  int fin = min(result, nodes[N-1].dist);
  cout << (fin == LLONG_MAX ? -1 : fin) << endl;

  return 0;
}