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

int N, Q;

struct Edge
{
public:
    int p, q, r;
    Edge(int p, int q, int r)
    {
        this->p = p;
        this->q = q;
        this->r = r;
    }
};

struct Case
{
public:
    int k, v, idx;
    Case(int k, int v, int idx)
    {
        this->k = k;
        this->v = v;
        this->idx = idx;
    }
};

bool myComp(const Edge &a, const Edge &b)
{
    return a.r > b.r;
}

bool myComp2(const Case &a, const Case &b)
{
    return a.k > b.k;
}

int main() {
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);

    cin >> N >> Q;
    vector<Edge> edges;
    f(i, 0, N-1)
    {
        int p, q, r;
        cin >> p >> q >> r;
        p--;
        q--;
        Edge cur = Edge(p, q, r);

        edges.pb(cur);
    }

    sort(edges.begin(), edges.end(), myComp);

//    f(i, 0, N-1)
//    {
//        cout << edges[i].p << " " << edges[i].q << " " << edges[i].r << endl;
//    }

    vector<Case> cases;

    f(i, 0, Q)
    {
        int k, v;
        cin >> k >> v;
        v--;
        Case c = Case(k, v, i);
        cases.pb(c);
    }

    sort(cases.begin(), cases.end(), myComp2);

//    f(i, 0, Q)
//    {
//        cout << cases2[i].k << " " << cases2[i].v << endl;
//    }

    int edgeIdx = 0;
    vi dsu(N, -1);
    vi result(Q);
    f(i, 0, Q)
    {
        while (edgeIdx < N-1 && edges[edgeIdx].r >= cases[i].k)
        {
            // add edge
            int a = edges[edgeIdx].p;
            int b = edges[edgeIdx].q;

            int aRoot = a, bRoot = b;

            while (dsu[aRoot] >= 0)
            {
                aRoot = dsu[aRoot];
            }

            while (dsu[bRoot] >= 0)
            {
                bRoot = dsu[bRoot];
            }

            if (dsu[aRoot] < dsu[bRoot]) // aParent has more nodes
            {
                dsu[aRoot] += dsu[bRoot];
                dsu[bRoot] = aRoot;
            } else // bParent has more nodes
            {
                dsu[bRoot] += dsu[aRoot];
                dsu[aRoot] = bRoot;
            }

            edgeIdx++;
        }

        // check how many elements in the same group with cases2[i].v;
        int cur = cases[i].v;

        while (dsu[cur] >= 0)
        {
            cur = dsu[cur];
        }

         result[cases[i].idx] = (dsu[cur] * -1) - 1;
    }

    f(i, 0, Q)
    {
        cout << result[i] << endl;
    }

    return 0;
}
