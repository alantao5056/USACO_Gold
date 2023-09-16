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

int main()
{
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    cin >> N >> K;

    vc hps(N);
    f(i, 0, N)
    {
        cin >> hps[i];
    }

    vector<vector<vi>> dp(K+1, vector<vi>(N, vi(3))); // 0: H   1: P   2: S

    int h = 0;
    int p = 0;
    int s = 0;

    f(i, 0, N)
    {
        if (hps[i] == 'H')
            h++;
        else if (hps[i] == 'P')
            p++;
        else
            s++;

        dp[0][i][0] = h;
        dp[0][i][1] = p;
        dp[0][i][2] = s;
    }

    cf(i, 1, K)
    {
        dp[i][0][0] = dp[0][0][0];
        dp[i][0][1] = dp[0][0][1];
        dp[i][0][2] = dp[0][0][2];
    }

    cf(i, 1, K)
    {
        f(j, 1, N)
        {
            // inherit
            dp[i][j][0] = max(dp[i][j-1][0], dp[i-1][j][0]);
            dp[i][j][1] = max(dp[i][j-1][1], dp[i-1][j][1]);
            dp[i][j][2] = max(dp[i][j-1][2], dp[i-1][j][2]);

            // change
            int maxChange = max(max(dp[i-1][j-1][0], dp[i-1][j-1][1]), dp[i-1][j-1][2]);

            dp[i][j][0] = max(dp[i][j][0], maxChange);
            dp[i][j][1] = max(dp[i][j][1], maxChange);
            dp[i][j][2] = max(dp[i][j][2], maxChange);

            if (hps[j] == 'H')
            {
                dp[i][j][0]++;
            } else if (hps[j] == 'P')
            {
                dp[i][j][1]++;
            } else
            {
                dp[i][j][2]++;
            }
        }
    }

    cout << max(max(dp[K][N-1][0], dp[K][N-1][1]), dp[K][N-1][2]) << endl;

    return 0;
}
