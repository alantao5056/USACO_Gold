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

class SegmentTree {
private:
    vector<int> tree;
    int n;

    // Helper function to build the segment tree
    void buildTree(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        buildTree(arr, 2 * node, start, mid);
        buildTree(arr, 2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1]; // Change this for different queries (e.g., min or max)
    }

public:
    // Constructor to initialize the segment tree
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n); // The segment tree can have at most 4 * n nodes
        buildTree(arr, 1, 0, n - 1);
    }

    // Update the value at index 'index' to 'newValue'
    void update(int index, int newValue, int node, int start, int end) {
        if (start == end) {
            tree[node] = newValue;
            return;
        }

        int mid = (start + end) / 2;
        if (index <= mid) {
            update(index, newValue, 2 * node, start, mid);
        } else {
            update(index, newValue, 2 * node + 1, mid + 1, end);
        }
        tree[node] = tree[2 * node] + tree[2 * node + 1]; // Change this for different queries (e.g., min or max)
    }

    // Update the value at index 'index' to 'newValue'
    void update(int index, int newValue) {
        update(index, newValue, 1, 0, n - 1);
    }

    // Query the range [left, right]
    int query(int left, int right, int node, int start, int end) {
        if (right < start || left > end) {
            return 0; // Change this for different queries (e.g., INT_MAX for min query)
        }

        if (left <= start && right >= end) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int leftSum = query(left, right, 2 * node, start, mid);
        int rightSum = query(left, right, 2 * node + 1, mid + 1, end);

        return leftSum + rightSum; // Change this for different queries (e.g., min or max)
    }

    // Query the range [left, right]
    int query(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

class Node
{
public:
    int cc = 1; //cc = children count
    int i, val, idx, level;
    SegmentTree* chain;
    int cs = 1; // chain size
    Node* parent;
    vector<Node*> nbs;
};
int maxLevel = 0;

void parents(Node* n)
{
    maxLevel = max(maxLevel, n->level);
    for(Node* nb : n->nbs)
    {
        if (nb != n->parent)
        {
            nb->parent = n;
            nb->level = n->level+1;
            parents(nb);
            n->cc += nb->cc;
        }
    }
}

void chain(Node* n)
{
    if (n->nbs.size() == 1)
    {
        return;
    }

    Node* big = new Node();
    for (Node* nb : n->nbs)
    {
        if (nb != n->parent && nb->cc >= big->cc)
        {
            big = nb;
        }
    }

    n->chain->update(n->cs, big->val);
    n->cs++;
    big->chain = n->chain;

    chain(big);

    for (Node* nb : n->nbs)
    {
        if (nb != n->parent && nb != big)
        {
            // new chain
            vector<int> arr(maxLevel - nb->level + 2);
            nb->chain = new SegmentTree(arr);
            nb->chain->update(0, nb->val);
            chain(nb);
        }
    }
}

int main() {
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);

    cin >> N >> Q;

    vector<Node> nodes;
    f(i, 0, N)
    {
        Node n = Node();
        n.i = i;
        cin >> n.val;
        nodes.pb(n);
    }

    // construct connections
    f(i, 0, N-1)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        nodes[a].nbs.pb(&nodes[b]);
        nodes[b].nbs.pb(&nodes[a]);
    }

    // assign parents
    queue<Node*> q;
    q.push(&nodes[0]);
    nodes[0].parent = NULL;

    while (!q.empty())
    {
        Node* cur = q.front();
        q.pop();

        for (Node* nb : cur->nbs)
        {
            if (nb != cur->parent)
            {
                nb->parent = cur;
                q.push(nb);
            }
        }
    }

    // give parents and count subtree size
    parents(&nodes[0]);

    //
    vector<int> arr(N);
    nodes[0].chain = new SegmentTree(arr);
    nodes[0].chain->update(0, nodes[0].val);
    chain(&nodes[0]);

    f(i, 0, Q)
    {
        int a, b, c;
        cin >> a >> b >> c;
        b--; c--;
        if (a == 1)
        {
            6666666666
        }
    }
    return 0;
}
