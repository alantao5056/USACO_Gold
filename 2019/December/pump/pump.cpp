// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int N, M;

const int INF = 1e9;

int main() {
	freopen("pump.in", "r", stdin);
	freopen("pump.out", "w", stdout);

	cin >> N >> M;
	vector<vector<int>> cost(N, vector<int>(N, INF));
	vector<vector<int>> flow(N, vector<int>(N, 0));
	vector<vector<double>> ans(N, vector<double>(N, 0));

	for (int i = 0; i < N; i++) {
		cost[i][i] = 0;
		flow[i][i] = INF;
		ans[i][i] = INF;
	}

	for (int i = 0; i < M; i++) {
		int a, b, c, f; cin >> a >> b >> c >> f; a--; b--;

		cost[a][b] = c;
		cost[b][a] = c;
		flow[a][b] = f;
		flow[b][a] = f;
		ans[a][b] = (double) f/c;
		ans[b][a] = (double) f/c;
	}

	for (int k = 0; k < N; k++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int nc = cost[i][k] + cost[k][j];
				int nf = min(flow[i][k], flow[k][j]);
				double newAns = (double) (nf) / (nc);

				if (newAns > ans[i][j]) {
					ans[i][j] = newAns;
					cost[i][j] = nc;
					flow[i][j] = nf;
				}
			}
		}
	}

	cout << (int) (ans[0][N-1] * 1000000) << endl;
	
	return 0;
}
