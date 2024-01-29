#include <bits/stdc++.h>

using namespace std;

int N, M, K;
vector<vector<int>> to;
vector<int> S;

int main()
{
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    cin >> N >> M >> K;

    string s;
    cin >> s;
    S.resize(N+1);
    for (int i = 1; i <= N; i++)
    {
        S[i] = (int) s[i-1] - 96;
    }

    to.resize(M+1);
    for (int i = 0; i <= M; i++)
    {
        to[i].resize(M+1);
    }
    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> to[i][j];
        }
    }

    // run dijkstras
    vector<vector<int>> dist(M+1, vector<int>(M+1, INT_MAX));
    for (int i = 1; i <= M; i++)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[i][i] = 0;
        pq.push({0, i});

        while (!pq.empty())
        {
            pair<int, int> cur = pq.top(); pq.pop();

            for (int j = 1; j <= M; j++)
            {
                int curDist = to[cur.second][j] + cur.first;
                if (curDist < dist[i][j])
                {
                    dist[i][j] = curDist;
                    pq.push({curDist, j});
                }
            }
        }
    }

    vector<vector<int>> prefix(M+1, vector<int>(N+1));
    for (int i = 1; i <= M; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            prefix[i][j] += prefix[i][j-1];
            prefix[i][j] += dist[S[j]][i];
        }
    }

//    for (int i = 1; i <= M; i++)
//    {
//        for (int j = 1; j <= M; j++)
//        {
//            cout << dist[i][j] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;

    // dp
    vector<vector<int>> dp(M+1, vector<int>(N+1, 1000000000));

    for (int i = 0; i <= M; i++)
    {
        dp[i][0] = 0;
    }

    for (int j = K; j <= N; j++)
    {
        for (int i = 1; i <= M; i++)
        {
            // block of K
            int mini = 1000000000;
            for (int z = 1; z <= M; z++)
            {
                mini = min(mini, dp[z][j-K]);
            }
            dp[i][j] = min(dp[i][j], mini + (prefix[i][j] - prefix[i][j-K]));
            // add from prev
            dp[i][j] = min(dp[i][j], dp[i][j-1] + dist[S[j]][i]);
        }
    }

//    for (int i = 1; i <= M; i++)
//    {
//        for (int j = 1; j <= N; j++)
//        {
//            cout << dp[i][j] << " ";
//        }
//
//        cout << endl;
//    }

    int result = INT_MAX;
    for (int i = 1; i <= M; i++)
    {
        result = min(result, dp[i][N]);
    }

    cout << result << endl;

    return 0;
}
