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
#define fi first
#define se second

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int N;
int MOD = 1000000007;

int main() {
    setIO("help");

    cin >> N;
    vector<pii> p(N);
    vi prefix(N*2+2);
    f(i, 0, N)
    {
        cin >> p[i].fi >> p[i].se;
        prefix[p[i].fi]++;
        prefix[p[i].se]--;
    }

    sort(p.begin(), p.end());

    vll power(N);
    power[0] = 1;
    f(i, 1, N)
    {
        power[i] = power[i-1]*2;
        power[i] %= MOD;
    }

    cf(i, 1, N*2+1)
    {
        prefix[i] += prefix[i-1];
    }

    ll result = 0;
    f(i, 0, N)
    {
        result += power[N-prefix[p[i].fi]];
        result %= MOD;
    }

    cout << result << endl;

    return 0;
}
