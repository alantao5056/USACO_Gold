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

int N, M, K;

int INF = 1000000001;

struct Node
{
    int id;
    vi nbs;
    vi weight;
    int toEnd = INF;
    int toEnd2 = INF;
    int hayVal = -1;

    Node(int id)
    {
        this->id = id;
    }
};

vector<Node> nodes;

class Compare
{
public:
    bool operator() (int a, int b)
    {
        return nodes[a].toEnd > nodes[b].toEnd;
    }
};

int main() {
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);

    cin >> N >> M >> K;

    f(i, 0, N)
    {
        nodes.pb(Node(i));
    }

    f(i, 0, M)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;

        nodes[a].nbs.pb(b);
        nodes[b].nbs.pb(a);

        nodes[a].weight.pb(c);
        nodes[b].weight.pb(c);
    }

    f(i, 0, K)
    {
        int a, b;
        cin >> a >> b;
        a--;
        nodes[a].hayVal = b;
    }

    priority_queue<int, vi, Compare> pq;
    nodes[N-1].toEnd = 0;
    pq.push(N-1);

    while (!pq.empty())
    {
        int cur = pq.top();
        pq.pop();

        f(i, 0, nodes[cur].nbs.size())
        {
            int path = nodes[cur].toEnd + nodes[cur].weight[i];
            if (path < nodes[nodes[cur].nbs[i]].toEnd)
            {
                nodes[nodes[cur].nbs[i]].toEnd = path;
                pq.push(nodes[nodes[cur].nbs[i]].id);
            }
        }
    }

    nodes.pb(Node(N));
    f(i, 0, N)
    {
        if (nodes[i].hayVal == -1) continue;

        nodes[N].nbs.pb(i);
        nodes[N].weight.pb(nodes[i].toEnd-nodes[i].hayVal);
    }

    priority_queue<int, vi, Compare> pq2;
    nodes[N].toEnd2 = 0;
    pq2.push(N);

    while (!pq2.empty())
    {
        int cur = pq2.top();
        pq2.pop();

        f(i, 0, nodes[cur].nbs.size())
        {
            int path = nodes[cur].toEnd2 + nodes[cur].weight[i];
            if (path < nodes[nodes[cur].nbs[i]].toEnd2)
            {
                nodes[nodes[cur].nbs[i]].toEnd2 = path;
                pq2.push(nodes[nodes[cur].nbs[i]].id);
            }
        }
    }

    f(i, 0, N-1)
    {
        cout << (nodes[i].toEnd2 <= nodes[i].toEnd) << endl;
    }

    return 0;
}
