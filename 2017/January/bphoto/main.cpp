#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

// TYPES
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi std::vector<int>
#define vll std::vector<long long>
#define vb std::vector<bool>
#define vc std::vector<char>;
#define vs std::vector<string>;
#define mii map<int, int>
#define si set<int>
#define sc set<char>

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

typedef __gnu_pbds::tree<
int,
__gnu_pbds::null_type,
std::less<int>,
__gnu_pbds::rb_tree_tag,
__gnu_pbds::tree_order_statistics_node_update>
ordered_set;

int N;

using namespace std;

int main() {
  freopen("bphoto.in", "r", stdin);
  freopen("bphoto.out", "w", stdout);

  cin >> N;
  vi cows(N);
  f(i, 0, N) {
    cin >> cows[i];
  }

  vi left(N);
  ordered_set s;

  f(i, 0, N) {
    int idx = s.order_of_key(cows[i]);
    if (idx == s.size()) {
        s.insert(cows[i]);
        continue;
    }
    if (*s.find_by_order(idx) <= cows[i]) {
      idx++;
    }
    left[i] = s.size()-idx;
    s.insert(cows[i]);
  }

  vi right(N);
  ordered_set s2;

  rf(i, N, 0) {
    int idx = s2.order_of_key(cows[i]);
    if (idx == s2.size()) {
        s2.insert(cows[i]);
        continue;
    }
    if (*s2.find_by_order(idx) <= cows[i]) {
      idx++;
    }
    right[i] = s2.size()-idx;
    s2.insert(cows[i]);
  }

  int count = 0;
  f(i, 0, N) {
      if (left[i]*2 < right[i] || right[i]*2 < left[i]) {
        count++;
      }
  }

  cout << count << endl;

  return 0;
}
