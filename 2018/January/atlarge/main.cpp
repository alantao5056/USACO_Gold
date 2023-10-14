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
#define qi queue<int>

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

int N, root;

struct Node
{
public:
    int id;
    int toRoot = -1;
    int toLeaf = INT_MAX;
    Node* parent = NULL;
    vector<Node*> nbs;
    Node(int id)
    {
        this->id = id;
    }
};

int main() {
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);

    cin >> N >> root;
    root--;

    // init nodes
    vector<Node*> nodes;
    f(i, 0, N)
    {
        Node* cur = new Node(i);
        nodes.pb(cur);
    }

    // make starting graph
    f(i, 0, N-1)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        nodes[a]->nbs.pb(nodes[b]);
        nodes[b]->nbs.pb(nodes[a]);
    }

    // make tree and toRoot
    qi q;
    q.push(root);
    nodes[root]->toRoot = 0;

    while (!q.empty())
    {
        Node* cur = nodes[q.front()];
        q.pop();

        for (Node* c : cur->nbs)
        {
            if (c != cur->parent)
            {
                c->parent = cur;
                c->toRoot = cur->toRoot+1;
                q.push(c->id);
            }
        }
    }

    // toLeaf
    qi q2;
    f(i, 0, N)
    {
        if (nodes[i]->nbs.size() == 1)
        {
            // leaf
            nodes[i]->toLeaf = 0;
            q2.push(i);
        }
    }

    while (!q2.empty())
    {
        Node* cur = nodes[q2.front()];
        q2.pop();
        if (cur->id == root) continue;
        if (cur->parent->toLeaf == INT_MAX)
        {
            // not assigned
            cur->parent->toLeaf = cur->toLeaf+1;
            q2.push(cur->parent->id);
        }
    }

    // count answer
    int result = 0;
    qi q3;
    q3.push(root);

    while (!q3.empty())
    {
        Node* cur = nodes[q3.front()];
        q3.pop();
        if (cur->toLeaf <= cur->toRoot)
        {
            // counts
            result++;
        } else
        {
            // add children
            for (Node* c : cur->nbs)
            {
                if (c != cur->parent)
                {
                    q3.push(c->id);
                }
            }
        }
    }

    cout << result << endl;

    return 0;
}
