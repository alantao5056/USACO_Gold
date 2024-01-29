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

void setIO(string name) {
  ios_base::sync_with_stdio(0); cin.tie(0);
  freopen((name+".in").c_str(),"r",stdin);
  freopen((name+".out").c_str(),"w",stdout);
}

int N;

int main() {
    setIO("haircut");

    cin >> N;
    vector<pii> sorted(N);
    vi hair(N);

    f(i, 0, N)
    {
        cin >> hair[i];
        sorted[i] = {hair[i], i};
    }

    sort(sorted.begin(), sorted.end());

    vi arr(N, 1);
    SegmentTree st(arr);

    ll tot = 0;
    int lines = 0;
    cf(i, 0, sorted[0].fi)
    {
        if (lines == N)
        {
            break;
        }
        cout << 0 << endl;
        lines++;
    }
    f(i, 0, N-1)
    {
        st.update(sorted[i].se, 0);
        int add = st.query(0, sorted[i].se);
        tot += add;
        f(j, sorted[i].fi, sorted[i+1].fi)
        {
            if (lines == N)
            {
                break;
            }
            cout << tot << endl;
            lines++;
        }
    }

    while (lines < N)
    {
        cout << tot << endl;
        lines++;
    }

    return 0;
}
