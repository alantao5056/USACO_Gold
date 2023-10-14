#include <bits/stdc++.h>
using namespace std;

/*

math problem of finding the combinations in which there are at least k consecutive same letters.
uses dp. uses modular exponentiation and modular multiplication (you don't have to do this but its safe).
be careful when subtracting a number and then modding it. It might be negative.
so instead of (a-b)%MOD, write (a-b+MOD)%MOD.
found error in modular exponentiation template. Had to change it.
*/

// TYPES
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vb vector<bool>
#define vc vector<char>
#define vs vector<string>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

int N, M, K;
ll MOD = 1000000007;

ll multiply(ll a, ll b) {
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

int main() {
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);

    cin >> N >> M >> K;
    vll dp(N);
    vll dp2(N);
    f(i, 0, K-1)
    {
        dp2[i] = power(M, i+1);
    }
    dp[K-1] = M;
    dp2[K-1] = (power(M, K) - M + MOD) % MOD;

    f(i, K, N)
    {
        dp[i] = (multiply((ll) dp[i-1], (ll) M) + multiply((ll) dp2[i-K], (ll) (M-1))) % MOD;
        dp2[i] = (power(M, i+1) - dp[i] + MOD) % MOD;
    }

    cout << dp[N-1] << endl;

    return 0;
}
