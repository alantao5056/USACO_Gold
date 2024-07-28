#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, K;

struct Node {
  ll val;
  vector<Node*> nbs;
};

int depth(Node* cur) {
  int d = -1;
  for (Node* nb : cur->nbs) {
    d = max(d, depth(nb));
  }

  return d+1;
}

int cnt = 0;
void dfs(Node* cur, int level) {
  for (Node* nb : cur->nbs) {
    dfs(nb, level-1);
  }
  cur->val = (ll)level * K + cnt;
  cnt++;
}

int main() {
  // freopen("haybales.in", "r", stdin);
  // freopen("haybales.out", "w", stdout);

  cin >> N;
  K = N;

  vector<Node> nodes(N+1);

  for (int i = 0; i < N; i++) {
    int cur; cin >> cur;
    nodes[cur].nbs.push_back(&nodes[i]);
  }

  int d = depth(&nodes[N]);
  dfs(&nodes[N], d);

  cout << K << endl;
  for (int i = 0; i < N; i++) {
    cout << nodes[i].val << endl;
  }

  return 0;
}