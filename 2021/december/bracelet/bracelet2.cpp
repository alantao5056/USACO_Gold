#include <bits/stdc++.h>

using namespace std;

int T;

struct Node {
  int id;
  int parent = -1;
  vector<int> children;
};

int main() {
  // freopen("bracelet.in", "r", stdin);
  // freopen("bracelet.out", "w", stdout);

  cin >> T;
  for (int i = 0; i < T; i++) {
    int N, M; cin >> N >> M;
    bool works = true;
    
    vector<int> active(N+1); // 0: not seen, 1: active, 2: deactivated
    vector<Node> nodes(N+1);
    for (int j = 0; j <= N; j++) {
      nodes[j].id = j;
    }

    for (int j = 0; j < M; j++) {
      stack<int> s;
      int K; cin >> K;
      for (int k = 0; k < K+2; k++) {
        int x;
        if (k == 0 || k == K+1) {
          x = 0;
        } else {
          cin >> x;
        }

        if (!works) continue;
        if (active[x] == 2) { // already deactivated
          works = false;
          continue;
        }

        if (active[x] == 0 || active[x] == 1) {
          // new
          active[x] = 3;
          s.push(x);
        } else if (active[x] == 3) {
          // second time this line
          vector<int> children;
          while (!s.empty() && s.top() != x) {
            children.push_back(s.top());
            if (nodes[s.top()].parent != -1 && nodes[s.top()].parent != x) {
              // parent changed
              works = false;
              break;
            }
            nodes[s.top()].parent = x;
            s.pop();
          }

          if (s.empty()) {
            works = false;
            continue;
          }

          if (!works) continue;

          // check children ordering
          map<int, int> pos;
          for (int l = 0; l < nodes[x].children.size(); l++) {
            pos[nodes[x].children[l]] = l;
          }

          nodes[x].children.clear();

          int curIdx = -1;
          for (int l = 0; l < children.size(); l++) {
            if (pos.find(children[l]) != pos.end()) {
              if (pos[children[l]] < curIdx) {
                works = false;
                break;
              }
              curIdx = pos[children[l]];
            }
            nodes[x].children.push_back(children[l]);
          }
        }
      }

      if (!works) continue;

      for (int k = 0; k <= N; k++) {
        if (active[k] == 3) {
          active[k] = 1;
        } else if (active[k] == 1) {
          active[k] = 2;
        }
      }
    }

    if (!works) {
      cout << "NO" << endl;
    } else {
      cout << "YES" << endl;
    }
  }

  return 0;
}