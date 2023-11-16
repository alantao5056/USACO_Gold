#include <bits/stdc++.h>
using namespace std;

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

int N, K;

int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);

    cin >> N >> K;

    vi arr(N+1);
    cf(i, 1, N)
    {
        cin >> arr[i];
    }

    vi dp(N+1);
    cf(i, 1, N)
    {
        si cur;
        f(j, 0, K)
        {
            if (i-j-1 < 0) break;

            cur.insert(arr[i-j]);

            int big = *cur.rbegin();

            dp[i] = max(dp[i], dp[i-j-1] + (big * (j+1)));
        }
    }

    cout << dp[N] << endl;

    return 0;
}
