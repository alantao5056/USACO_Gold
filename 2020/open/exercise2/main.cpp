#include <bits/stdc++.h>

using namespace std;

#define ll long long

void setIO(string name) {
  ios_base::sync_with_stdio(0); cin.tie(0);
  freopen((name+".in").c_str(),"r",stdin);
  freopen((name+".out").c_str(),"w",stdout);
}

int N, M;
int P = 1234;
vector<vector<int>> dp;
vector<bool> prime;

void sieve()
{
    for (int p = 2; p * p <= N; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= N; i += p)
                prime[i] = false;
        }
    }
}

int main()
{
    setIO("exercise");
    cin >> N >> M;
    dp.resize(P, vector<int>(N+1));
    prime.resize(N+1, true);
    sieve();
    vector<int> primes;
    for (int i = 2; i <= N; i++)
    {
        if (prime[i]) primes.push_back(i);
    }
    for (int i = 0; i <= N; i++)
    {
        dp[0][i] = 1;
    }
    for (int i = 1; i <= primes.size(); i++)
    {
        for (int j = 0; j <= N; j++)
        {
            dp[i][j] = dp[i-1][j];
            int p = primes[i-1];
            while (p <= j)
            {
                dp[i][j] += ((ll)p * dp[i-1][j-p]) % M;
                dp[i][j] %= M;
                p *= primes[i-1];
            }
        }
    }

    cout << dp[primes.size()][N] << endl;

    return 0;
}
