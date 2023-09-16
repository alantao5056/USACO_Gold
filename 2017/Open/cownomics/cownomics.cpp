#include <bits/stdc++.h>
using namespace std;

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

/* FUNCTIONS */
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

int N, M;
const int A = 100000007;
const int MOD = 1000000007;

ll expo(ll base, ll exp, int mod) {
  ll res = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      res= (res * base) % mod;
    }
    exp = exp >> 1;
    base = (base * base) % mod;
  }
  return res;
}

ll multiply(ll a, ll b, ll mod) {
  ll res = 0; // Initialize result

  // Update a if it is more than
  // or equal to mod
  a %= mod;

  while (b) {
      // If b is odd, add a with result
      if (b & 1)
          res = (res + a) % mod;

      // Here we assume that doing 2*a
      // doesn't cause overflow
      a = (2 * a) % mod;

      b >>= 1; // b = b / 2
  }

  return res;
}

bool check(vector<vi>& spotty, vector<vi>& plain, int size) {
  vll h1(N);
  vll h2(N);

  f(i, 0, N) {
    f(j, 0, size) {
      h1[i] += multiply(spotty[i][j], expo(A, (size-j-1), MOD), MOD);
      h1[i] %= MOD;
      h2[i] += multiply(plain[i][j], expo(A, (size-j-1), MOD), MOD);
      h2[i] %= MOD;
    }
  }

  cf(i, 0, M-size) {
    // check if works
    set<ll> s1(h1.begin(), h1.end());
    bool works = true;
    for (int h : h2) {
      if (s1.count(h)) {
        // duplicate
        works = false;
        break;
      }
    }

    if (works) return true;

    // update hash
    f(j, 0, N) {
      h1[j] -= multiply(spotty[j][i], expo(A, size-1, MOD), MOD);
      if (h1[j] < 0) {
        h1[j] += MOD;
      }
      h1[j] *= A;
      h1[j] %= MOD;
      h1[j] += spotty[j][i+size];
      h1[j] %= MOD;

      h2[j] -= multiply(plain[j][i], expo(A, size-1, MOD), MOD);
      if (h2[j] < 0) {
        h2[j] += MOD;
      }
      h2[j] *= A;
      h2[j] %= MOD;
      h2[j] += plain[j][i+size];
      h2[j] %= MOD;
    }
  }

  // check if works
  set<ll> s1(h1.begin(), h1.end());
  bool works = true;
  for (ll h : h2) {
    if (s1.count(h)) {
      // duplicate
      works = false;
      break;
    }
  }

  if (works) return true;

  return false;
}

int main() {
  freopen("cownomics.in", "r", stdin);
  freopen("cownomics.out", "w", stdout);

  cin >> N >> M;

  vector<vi> spotty(N, vi(M));
  f(i, 0, N) {
    string s;
    cin >> s;
    f(j, 0, M) {
      int val;
      if (s[j] == 'A') {
        val = 1;
      } else if (s[j] == 'C') {
        val = 2;
      } else if (s[j] == 'G') {
        val = 3;
      } else { // s[j] == 'T'
        val = 4;
      }
      spotty[i][j] = val;
    }
  }

  vector<vi> plain(N, vi(M));
  f(i, 0, N) {
    string s;
    cin >> s;
    f(j, 0, M) {
      int val;
      if (s[j] == 'A') {
        val = 1;
      } else if (s[j] == 'C') {
        val = 2;
      } else if (s[j] == 'G') {
        val = 3;
      } else { // s[j] == 'T'
        val = 4;
      }
      plain[i][j] = val;
    }
  }

  // binary search
  int low = 1;
  int high = M;
  
  while (low < high) { // notice we do not compare element at mid with our target
    int mid = low + (high - low) / 2;
    if (check(spotty, plain, mid))
      high = mid;
    else
      low = mid + 1;
  }

  cout << low << endl;

  return 0;
}