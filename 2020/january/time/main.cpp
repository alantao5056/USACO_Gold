#include <bits/stdc++.h>

using namespace std;

int N, M, C;

struct Node
{
public:
    vector<int> to;
    vector<int> from;
    int id;
    int val;

    Node(int id, int val)
    {
        this->id = id;
        this->val = val;
    }
};

vector<Node> nodes;
vector<vector<int>> dp;

int main()
{
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    cin >> N >> M >> C;

    for (int i = 0; i < N; i++)
    {
        int val;
        cin >> val;
        nodes.push_back(Node(i, val));
    }

    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b; a--; b--;

        nodes[a].to.push_back(b);
        nodes[b].from.push_back(a);
    }

    dp.resize(1001, vector<int>(N, -1));

    for (int n : nodes[0].to)
    {
        dp[1][n] = nodes[n].val;
    }

    for (int i = 2; i <= 1000; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int f : nodes[j].from)
            {
                if (dp[i-1][f] == -1) continue;
                //if (dp[i-1][f] + nodes[j].val - (pow(i, 2) * C) <= 0) continue;
                dp[i][j] = max(dp[i][j], dp[i-1][f] + nodes[j].val);
            }
        }
    }

    int result = 0;
    for (int i = 1; i <= 1000; i++)
    {
        result = max(result, (int) (dp[i][0] - (pow(i, 2) * C)));
    }

    cout << result << endl;

    return 0;
}
