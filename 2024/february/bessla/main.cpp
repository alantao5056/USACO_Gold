#include <bits/stdc++.h>

using namespace std;

#define ll long long

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

int N, M, C, R, K;

struct Node
{
    int id;
    vector<pair<int, Node*>> nbs;
    vector<int> minD;
};

int main()
{
    //setIO("bessla");
    cin >> N >> M >> C >> R >> K;

    vector<Node> nodes(N);

    // first C charging
    for (int i = 0; i < N; i++)
    {
        nodes[i].id = i;
        nodes[i].minD.resize(C, INT_MAX);
    }

    // edges
    for (int i = 0; i < M; i++)
    {
        int a, b, d; cin >> a >> b >> d; a--; b--;
        nodes[a].nbs.push_back({d, &nodes[b]});
        nodes[b].nbs.push_back({d, &nodes[a]});
    }

    for (int i = 0; i < C; i++)
    {
        // start from this
        nodes[i].minD[i] = 0;
        priority_queue<pair<int, Node*>> pq;

        pq.push({0, &nodes[i]});

        while (!pq.empty())
        {
            int d = pq.top().first;
            Node* cur = pq.top().second;
            pq.pop();

            for (pair<int, Node*> nb : cur->nbs)
            {
                int newD = cur->minD[i] + nb.first;
                if (newD > R) continue;
                if (newD < nb.second->minD[i])
                {
                    nb.second->minD[i] = newD;
                    pq.push({newD, nb.second});
                }
            }
        }
    }

    int tot = 0;
    vector<int> result;
    for (int i = C; i < N; i++)
    {
        int cnt = 0;
        for (int j : nodes[i].minD)
        {
            if (j <= R) {cnt++;}
            if (cnt == K) {
                tot++;
                result.push_back(i);
                break;
            }
        }
    }

    cout << tot << endl;

    for (int r : result)
    {
        cout << r+1 << endl;
    }

    return 0;
}
