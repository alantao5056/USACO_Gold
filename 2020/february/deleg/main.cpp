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

int N, K;

struct Node
{
    int id;
    Node* parent = NULL;
    vector<Node*> nbs;
};

vector<Node> nodes;

void setParent(Node* cur)
{
    for (Node* n : cur->nbs)
    {
        if (n == cur->parent) continue;
        n->parent = cur;
        setParent(n);
    }
}

int recursive(Node* cur)
{
    if (cur->nbs.size() == 1 && cur->id != 0)
    {
        return 1;
    }
    vector<int> vals;
    for (Node* n : cur->nbs)
    {
        if (n == cur->parent) continue;
        int val = recursive(n);
        if (val == -1)
        {
            return -1;
        }
        if (val != 0)
        {
            vals.pb(val);
        }
    }
    sort(vals.begin(), vals.end());
    int left = 0;
    int right = vals.size() -1;
    int odd = -1;
    while (left < right)
    {
        int sum = vals[left] + vals[right];
        if (sum == K)
        {
            left++; right--;
            continue;
        }

        if (sum > K)
        {
            if (odd != -1)
            {
                return -1;
            }
            odd = vals[right];
            right--;
        } else // sum < K
        {
            if (odd != -1)
            {
                return -1;
            }
            odd = vals[left];
            left++;
        }
    }

    if (odd != -1 && vals.size()%2==0) return -1;

    if (left == right)
    {
        if (odd != -1) return -1;
        odd = vals[left];
    }

    if (odd == -1)
    {
        return 1;
    }

    return ((odd + 1) % K);
}

int main() {
    setIO("deleg");

    cin >> N;
    nodes.resize(N);

    f(i, 0, N)
    {
        nodes[i].id = i;
    }

    f(i, 0, N-1)
    {
        int a, b; cin >> a >> b; a--;b--;
        nodes[a].nbs.pb(&nodes[b]);
        nodes[b].nbs.pb(&nodes[a]);
    }

    setParent(&nodes[0]);

    cout << 1;
    cf(i, 2, N-1)
    {
        K = i;
        if ((N-1) % i != 0) {cout << 0; continue;}
        if (recursive(&nodes[0]) != 1) {cout << 0; continue;}
        cout << 1;
    }

    cout << endl;

    return 0;
}
