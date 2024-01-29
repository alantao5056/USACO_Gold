#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, Q;

int main()
{
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    cin >> N >> Q;
    vector<int> nums(N+1);
    for (int i = 1; i <= N; i++)
    {
        cin >> nums[i];
    }

    vector<vector<ll>> dp(N+1, vector<ll>(N+1));

    vector<int> m(2000001);
    for (int i = 1; i <= N; i++)
    {
        for (int j = i+1; j <= N; j++)
        {
            int ind = 1000000-nums[i]-nums[j];
            if (ind >= 0 && ind <= 2000000)
            {
                dp[i][j] = m[ind];
            }
            m[nums[j]+1000000]++;
        }
        for (int j = i+1; j <= N; j++)
        {
            m[nums[j]+1000000]--;
        }
    }

    for (int i = N; i>=1; i--)
    {
        for (int j = i+1; j<=N; j++)
        {
            dp[i][j] += dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
        }
    }

    for (int i = 0; i < Q; i++)
    {
        int a, b;
        cin >> a >> b;
        if (b - a <= 1)
        {
            cout << 0 << endl;
        } else
        {
            cout << dp[a][b] << endl;
        }
    }

    return 0;
}
