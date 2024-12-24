#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;
using pii = pair<int, int>;

const int MOD = 1e9+7;

typedef tree<
pii,
null_type,
less<pii>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

struct Seg {
  int l, r, k;
};

int N;

int main() {
  // freopen("grass.in", "r", stdin);
  // freopen("grass.out", "w", stdout);

  cin >> N;
  ordered_set start;
  ordered_set end;
  set<pii> ks;
  set<pii> len;
  vector<Seg> grass(N);
  for (int i = 0; i < N; i++) {
    int l, r, k; cin >> l >> r >> k;
    grass[i].l = l;
    grass[i].r = r;
    grass[i].k = k;

    start.insert({l, i});
    end.insert({r, i});
    ks.insert({k, i});
    len.insert({r-l, i});
  }

  vector<int> ans(N);

  while (ks.size()) {
    int cur = ks.begin()->second;
    ks.erase(ks.begin());

    while (len.size() && len.begin()->first < grass[cur].k) {
      int temp = len.begin()->second;
      len.erase(len.begin());
      start.erase({grass[temp].l, temp});
      end.erase({grass[temp].r, temp});
      ks.erase({grass[temp].k, temp});
    }

    int s = start.size() - start.order_of_key(make_pair(grass[cur].r - grass[cur].k, MOD));
    int e = end.order_of_key(make_pair(grass[cur].l + grass[cur].k, -1));

    ans[cur] = len.size() - s - e;
  }

  for (int i = 0; i < N; i++) {
    cout << ans[i]-1 << endl;
  }

  return 0;
}