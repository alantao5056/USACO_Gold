#include <bits/stdc++.h>

using namespace std;

#define ll long long

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}
int MOD = 1e9+7;
int N;
string s;
vector<int> ss;

int main()
{
    //setIO("genetics");
    cin >> s;
    N = s.size();
    ss.resize(N);

    for (int i = 0; i < N; i++)
    {
        if (s[i] == 'A') ss[i] = 0;
        else if (s[i] == 'C') ss[i] = 1;
        else if (s[i] == 'G') ss[i] = 2;
        else if (s[i] == 'T') ss[i] = 3;
        else ss[i] = 4;
    }

    ll dp[N][4][4][4]; // idx, first letter of second to last, first letter of last, last letter of last
    for (int k = 0; k < N; k++)
    {
        for (int n = 0; n < 4; n++)
        {
            for (int l = 0; l < 4; l++)
            {
                for (int m = 0; m < 4; m++)
                {
                    dp[k][n][l][m] = 0;
                }
            }
        }
    }

    for (int l = 0; l < 4; l++)
    {
        for (int m = 0; m < 4; m++)
        {
            if (ss[0] == 4 || ss[0] == m)
            {
                dp[0][l][m][m] = 1;
            }
        }
    }

    for (int k = 1; k < N; k++)
    {
        for (int m2 = 0; m2 < 4; m2++)
        {
            if (ss[k] == 4 || ss[k] == m2) {
                for (int n = 0; n < 4; n++)
                {
                    for (int l = 0; l < 4; l++)
                    {
                        for (int m = 0; m < 4; m++)
                        {
                            if (m2 != m) // not repeat
                            { // extend
                                dp[k][n][l][m2] += dp[k-1][n][l][m];
                                dp[k][n][l][m2]%=MOD;
                            }

                            if (m == n)
                            {
                                dp[k][l][m2][m2] += dp[k-1][n][l][m];
                                dp[k][l][m2][m2]%=MOD;
                            }
                        }
                    }
                }
            }
        }
    }

    ll tot = 0;
    for (int l = 0; l < 4; l++)
    {
        for (int m = 0; m < 4; m++)
        {
            tot += dp[N-1][m][l][m];
            tot %= MOD;
        }
    }

    cout << tot << endl;
    return 0;
}
