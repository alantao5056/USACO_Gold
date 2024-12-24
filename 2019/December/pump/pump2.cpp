// Source: https://usaco.guide/general/io

// djikstra

#include <bits/stdc++.h>
#include <queue>
using namespace std;

int N, M;

const int INF = 1e9;

struct piii {
	int x, c, f;
	piii(int x, int c, int f) {
		this->x = x;
		this->c = c;
		this->f = f;
	}
};

int main() {
	freopen("pump.in", "r", stdin);
	freopen("pump.out", "w", stdout);

	cin >> N >> M;

	vector<vector<piii>> adj(N, vector<piii>());

	for (int i = 0; i < M; i++) {
		int a, b, c, f; cin >> a >> b >> c >> f; a--; b--;
		piii aa(b, c, f);
		piii bb(a, c, f);
		adj[a].push_back(aa);
		adj[b].push_back(bb);
	}

	vector<double> ans(N, 0);
	vector<int> flow(N, 0);
	vector<int> cost(N, INF);

	flow[0] = INF;
	cost[0] = 0;

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
	pq.push({0, 0});

	while (!pq.empty()) {
		pair<double, int> cur = pq.top(); pq.pop();

		for (piii p : adj[cur.second]) {
			int nf = min(flow[cur.second], p.f);
			int nc = cost[cur.second] + p.c;
			double newAns = (double) nf / nc;
			if (newAns > ans[p.x]) {
				ans[p.x] = newAns;
				flow[p.x] = nf;
				cost[p.x] = nc;
				pq.push({newAns, p.x});
			}
		}
	}

	cout << (int) (ans[N-1] * 1000000) << endl;

  return 0;
}
