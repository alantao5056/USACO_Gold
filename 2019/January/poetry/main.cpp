// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int N, M, K;
const int MAXS = 5001;
const int MOD = 1000000007;
typedef long long ll;

ll power(ll x, ll y)
{
    ll res = 1;     // Initialize result

    x = x % MOD; // Update x if it is more than or
                // equal to p

    if (x == 0) return 0; // In case x is divisible by p;

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % MOD;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % MOD;
    }
    return res;
}

ll moduloMultiplication(ll a, ll b) {
  ll res = 0; // Initialize result

  // Update a if it is more than
  // or equal to mod
  a %= MOD;

  while (b) {
    // If b is odd, add a with result
    if (b & 1)
      res = (res + a) % MOD;

    // Here we assume that doing 2*a
    // doesn't cause overflow
    a = (2 * a) % MOD;

    b >>= 1; // b = b / 2
  }

  return res;
}

int main() {
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);

    cin >> N >> M >> K;

    vector<pair<int, int>> words(N, {0, 0}); // 1 is syllables, 2 is rhyme
    map<int, vector<int>> words2;

    for (int i = 0; i < N; i++)
    {
        cin >> words[i].first >> words[i].second;

        if (words2.find(words[i].second) != words2.end())
        {
            words2[words[i].second].push_back(words[i].first);
        } else {
            words2[words[i].second] = vector<int>({words[i].first});
        }
    }

    map<char, int> rhymes;

    for (int i = 0; i < M; i++)
    {
        string cur;
        cin >> cur;

        rhymes[cur[0]]++;
    }

    // dp get all possible combinations
    vector<ll> dp(K);
    dp[0] = 1;

    for (int i = 1; i <= K; i++)
    {
        for (pair<int, int> w : words)
        {
            if (i - w.first >= 0)
            {
                dp[i] += dp[i-w.first];
                dp[i] %= MOD;
            }
        }
    }

    vector<ll> combs;

    for (auto const& [key, val] : words2)
    {
        ll total = 0;
        for (int v : val)
        {
            total += dp[K-v];
            total %= MOD;
        }

        combs.push_back(total);
    }

    ll result = 1;
    for (auto const& [key, val] : rhymes)
    {
        ll total = 0;
        for (ll c : combs)
        {
            total += power(c, val);
            total %= MOD;
        }

        result = moduloMultiplication(result, total);
    }

    cout << result << endl;

    return 0;
}
