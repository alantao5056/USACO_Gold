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

void setIO(string name) {
	ios_base::sync_with_stdio(0); cin.tie(0);
	freopen((name+".in").c_str(),"r",stdin);
	freopen((name+".out").c_str(),"w",stdout);
}

int N, M, C;


struct Time
{
    int val;
    int id;
    int prev = 0;
    bool visited = false;
    vector<int> nbs;
    vector<int> weight;
};

vector<Time> times;

void recursive(int cur)
{
    f(i, 0, times[cur].nbs.size())
    {
        times[cur].val = max(times[cur].val, times[times[cur].nbs[i]].val + times[cur].weight[i]);
        if (!times[times[cur].nbs[i]].visited)
        {
            times[times[cur].nbs[i]].visited = true;
            recursive(times[cur].nbs[i]);
            times[cur].val = max(times[cur].val, times[times[cur].nbs[i]].val + times[cur].weight[i]);
        }
    }
}

int main() {
    setIO("timeline");


    cin >> N >> M >> C;
    times.resize(N);
    f(i, 0, N)
    {
        cin >> times[i].val;
        times[i].id = i;
    }

    f(i, 0, C)
    {
        int a, b, c; cin >> a >> b >> c; a--;b--;

        times[b].nbs.pb(a);
        times[b].weight.pb(c);
        times[a].prev++;
    }

    f(i, 0, N)
    {
        if (times[i].visited || times[i].prev > 0) continue;

        times[i].visited = true;
        recursive(i);
    }

    f(i, 0, N)
    {
        cout << times[i].val << endl;
    }

    return 0;
}
