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

int N, M, T;

struct Node
{
    int id, cows, to;
    int cows2 = 0;
    int dist = INT_MAX;
    vi nbs;
    vi chs;
    vi w;
};

vector<Node> nodes;

int recursive(int cur)
{
    int tot = nodes[cur].cows;
    for (int ch : nodes[cur].chs)
    {
        tot += recursive(ch);
    }
    nodes[cur].cows2 = tot;
    return tot;
}

class Compare
{
public:
    bool operator() (int a, int b)
    {
        return nodes[a].dist > nodes[b].dist;
    }
};

int main() {
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);

    cin >> N >> M >> T;
    nodes.resize(N, Node());

    f(i, 0, N)
    {
        nodes[i].id = i;
        cin >> nodes[i].cows;
    }

    f(i, 0, M)
    {
        int a, b, w;
        cin >> a >> b >> w;
        a--; b--;

        nodes[a].nbs.pb(b);
        nodes[a].w.pb(w);
        nodes[b].nbs.pb(a);
        nodes[b].w.pb(w);
    }

    // run dijkstras
    priority_queue<int, vi, Compare> pq;
    pq.push(0);
    nodes[0].dist = 0;
    nodes[0].to = -1;

    while (!pq.empty())
    {
        int cur = pq.top();
        pq.pop();

        f(i, 0, nodes[cur].nbs.size())
        {
            int origDist = nodes[nodes[cur].nbs[i]].dist;
            int newDist = nodes[cur].dist + nodes[cur].w[i];
            if (newDist < origDist || (newDist == origDist && cur < nodes[nodes[cur].nbs[i]].to))
            {
                // update orig distance
                nodes[nodes[cur].nbs[i]].dist = newDist;
                nodes[nodes[cur].nbs[i]].to = cur;
                pq.push(nodes[cur].nbs[i]);
            }
        }
    }

    // construct tree
    f(i, 1, N)
    {
        nodes[nodes[i].to].chs.pb(i);
    }

    // count num of cows pass through
    recursive(0);

    // try every point
    ll result = 0;
    f(i, 1, N)
    {
        if (T < nodes[i].dist)
        {
            result = max(result, (ll) (nodes[i].dist - T) * nodes[i].cows2);
        }
    }

    cout << result << endl;

    return 0;
}
