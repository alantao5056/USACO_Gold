#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

class Node
{
public:
    int id;
    vector<int> nbs;
    vector<pair<int, int>> fc;

    Node(int id)
    {
        this->id = id;
    }
};

int N, M;
vector<Node> nodes;

ll minDist(int minFlow)
{
    vector<int> dist(N, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty())
    {
        const auto [d, cur] = pq.top();
        pq.pop();
        if (d != dist[cur]) continue; // already updated
        for (int i = 0; i < nodes[cur].nbs.size(); i++)
        {
            if (nodes[cur].fc[i].first < minFlow) continue; // ignore these
            int newDist = d + nodes[cur].fc[i].second;
            if (newDist < dist[nodes[cur].nbs[i]])
            {
                dist[nodes[cur].nbs[i]] = newDist;
                pq.push({newDist, nodes[cur].nbs[i]});
            }
        }
    }

    return (ll) (((double) minFlow/dist[N-1]) * 1000000);
}

int main()
{
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);

    cin >> N >> M;


    for (int i = 0; i < N; i++)
    {
        nodes.push_back(Node(i));
    }

    for (int i = 0; i < M; i++)
    {
        int from, to, flow, cost;
        cin >> from >> to >> cost >> flow;
        from--; to--;

        nodes[from].nbs.push_back(to);
        nodes[from].fc.push_back({flow, cost});
        nodes[to].nbs.push_back(from);
        nodes[to].fc.push_back({flow, cost});
    }

    ll result = 0;
    for (int i = 1; i <= 1000; i++)
    {
        result = max(result, minDist(i));
    }

    cout << result << endl;

    return 0;
}
