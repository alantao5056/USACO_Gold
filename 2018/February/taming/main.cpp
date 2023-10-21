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

int N;
vi logs;
vector<vi> memo;

int recursive(int pos, int num)
{
    if (memo[pos][num] != -1)
    {
        return memo[pos][num];
    }
    if (pos == 0)
    {
        if (num == 1)
        {
            return logs[pos] == 0 ? 0 : 1;
        } else
        {
            return 0;
        }
    }

    if (num == 1)
    {
        int ans = 0;
        cf(i, 0, pos)
        {
            ans += logs[i] == i ? 0 : 1;
        }
        return ans;
    }

    int minAns = INT_MAX;
    f(lb, num-1, pos+1)
    {
        int ans = 0;
        f(j, lb, pos+1)
        {
            ans += logs[j] == j-lb ? 0 : 1;
        }
        minAns = min(minAns, ans + recursive(lb-1, num-1));
    }

    memo[pos][num] = minAns;
    return minAns;
}

int main() {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);

    cin >> N;
//    log.resize(N);
    memo.resize(N+1, vi(N+1));
    cf(i, 0, N)
    {
        cf(j, 0, N)
        {
            memo[i][j] = -1;
        }
    }
    f(i, 0, N)
    {
        int a;
        cin >> a;
        logs.pb(a);
    }

    cf(i, 1, N)
    {
        cout << recursive(N-1, i) << endl;
    }

    return 0;
}
