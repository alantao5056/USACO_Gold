#include <bits/stdc++.h>

using namespace std;

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
        tree[node] = max(tree[2 * node], tree[2 * node + 1]); // Change this for different queries (e.g., min or max)
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
        tree[node] = max(tree[2 * node], tree[2 * node + 1]); // Change this for different queries (e.g., min or max)
    }

    // Update the value at index 'index' to 'newValue'
    void update(int index, int newValue) {
        update(index, newValue, 1, 0, n - 1);
    }

    // Query the range [left, right]
    int query(int left, int right, int node, int start, int end) {
        if (right < start || left > end) {
            return INT_MIN; // Change this for different queries (e.g., INT_MAX for min query)
        }

        if (left <= start && right >= end) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int leftSum = query(left, right, 2 * node, start, mid);
        int rightSum = query(left, right, 2 * node + 1, mid + 1, end);

        return max(leftSum, rightSum); // Change this for different queries (e.g., min or max)
    }

    // Query the range [left, right]
    int query(int left, int right) {
        return query(left, right, 1, 0, n - 1);
    }
};

int N, K;

int main()
{
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);

    cin >> N >> K;
    vector<int> arr(N+1);
    vector<int> prefix(N+1);
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        prefix[i] = prefix[i-1] + arr[i];
    }

    SegmentTree st(arr);

    vector<vector<int>> dp(K+2, vector<int>(N+1, 1000000000)); // i is group num j is element
//    for (int j = 0; j <= N; j++)
//    {
//        dp[0][j] = 0;
//    }
    dp[0][0] = 0;
    for (int i = 1; i <= K+1; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            for (int k = j; k >= 0; k--)
            {
                int big = st.query(k+1, j);
                int sum = prefix[j] - prefix[k];
                int waste = big * (j-k) - sum;

                dp[i][j] = min(dp[i][j], waste + dp[i-1][k]);
            }
//            cout << dp[i][j] << " ";

        }
//        cout << endl;
    }

    cout << dp[K+1][N] << endl;;

    return 0;
}
