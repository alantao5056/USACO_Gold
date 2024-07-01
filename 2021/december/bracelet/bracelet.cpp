#include <bits/stdc++.h>

using namespace std;

int T;

struct Link {
  int val = -1;
  Link* next = nullptr;
};

int main() {
  freopen("bracelet.in", "r", stdin);
  freopen("bracelet.out", "w", stdout);

  cin >> T;
  for (int i = 0; i < T; i++) {
    int N, M; cin >> N >> M;

    vector<Link*> ins(N, new Link());
    vector<int> sni(N, -1);
    vector<int> active(N);
    bool works = true;

    for (int j = 0; j < M; j++) {
      int k; cin >> k;
      if (!works) continue;
      stack<int> s;
      vector<bool> visited(N);
      for (int x = 0; x < k; x++) {
        int cur; cin >> cur; cur--;
        if (!works) continue;
        if (active[cur] == 2) {
          // appears after appearing in previous k
          works = false;
          continue;
        }
        active[cur] += 5;
        if (!visited[cur]) {
          visited[cur] = true;
          s.push(cur);
          continue;
        }

        visited[cur] = false;
        Link* prev = ins[cur];
        Link* cur = ins[cur]->next;
        while (!s.empty() && s.top() != cur) {
          while (l != nullptr && (active[l->val] == 1 || active[l->val] == 2)) {
            // get rid of inactive
            Link* t = l->next;
            delete l;
            l = t;
          }

          if (visited[s.top()]) {
            // no ending pair within a pair
            works = false;
            break;
          }


          if (sni[s.top()] == -1) {
            ins[cur].insert(s.top());
            sni[s.top()] = cur;
          } else if (sni[s.top()] != cur) {
            works = false;
            break;
          }
          s.pop();
        }
      }

      for (int x = 0; x < N; x++) {
        if (visited[x] == 1) {
          works = false;
          break;
        }

        if (active[x] && !visited[x]) {
          active[x] = 2;
        }
        if (visited[x]) {
          active[x] = 1;
        }
      }
    }
    if (works) {
      cout << "YES" << endl;
    } else {
      cout << "NO" << endl;
    }
  }

    
  return 0;
}