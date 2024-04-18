#include <bits/stdc++.h>

using namespace std;

void setIO(string name) {
  ios_base::sync_with_stdio(0); cin.tie(0);
  freopen((name+".in").c_str(),"r",stdin);
  freopen((name+".out").c_str(),"w",stdout);
}

int N, D;
int i_[4] = {1, 0, -1, 0};
int j_[4] = {0, 1, 0, -1};

struct Cell
{
    int i, j;
    bool isRock = false;
    bool isStart = false;
    bool ans = false;
    int rockDist = -1;
    int sourceDist = -1;
};

vector<vector<Cell>> grid;

Cell* dr(Cell* c, int k)
{
    int i2 = c->i+i_[k];
    int j2 = c->j+j_[k];
    if (i2 < 0 || i2 >= N || j2 < 0 || j2 >= N) return NULL;
    return &grid[i2][j2];
}

int main()
{
    //setIO("replication");
    cin >> N >> D;

    // initialize grid
    grid.resize(N, vector<Cell>(N));
    deque<Cell*> q;
    deque<Cell*> q2;
    for (int i = 0; i < N; i++)
    {
        string s; cin >> s;
        for (int j = 0; j < N; j++)
        {
            grid[i][j].i = i;
            grid[i][j].j = j;
            if (s[j] == '#')
            {
                grid[i][j].isRock = true;
                grid[i][j].rockDist = 0;
                q.push_back(&grid[i][j]);
            } else if (s[j] == 'S')
            {
                grid[i][j].isStart = true;
                grid[i][j].sourceDist = 0;
                q2.push_back(&grid[i][j]);
            }
        }
    }

    // calculate rockdist
    while (!q.empty())
    {
        Cell* cur = q.front(); q.pop_front();

        for (int k = 0; k < 4; k++)
        {
            Cell* to = dr(cur, k);

            if (to == NULL) continue;
            if (to->isRock || to->rockDist != -1) continue;
            int newDist = cur->rockDist + 1;
            to->rockDist = newDist;
            q.push_back(to);
        }
    }

    // simulate going from a start
    priority_queue<pair<int, Cell*>> pq;
    while (!q2.empty())
    {
        Cell* cur = q2.front(); q2.pop_front();
        cur->ans = true;
        pq.push({cur->rockDist-1, cur});

        if (cur->sourceDist >= cur->rockDist * D) continue;

        for (int k = 0; k < 4; k++)
        {
            Cell* to = dr(cur, k);

            if (to->isRock) continue;
            if (to->sourceDist != -1) continue;
            if (cur->sourceDist + 1 > to->rockDist * D) continue;

            to->sourceDist = cur->sourceDist + 1;
            q2.push_back(to);
        }
    }

    // last simulation BFS get all ans
    while (!pq.empty())
    {
        pair<int, Cell*> pic = pq.top(); pq.pop();
        int dist = pic.first;
        Cell* cur = pic.second;

        for (int k = 0; k < 4; k++)
        {
            Cell* to = dr(cur, k);

            if (to->isRock) continue;
            if (to->ans) continue;
            if (dist-1 < 0) continue;
            to->ans = true;
            pq.push({dist-1, to});
        }
    }

    int result = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j].ans) result++;
        }
    }

    cout << result << endl;

    return 0;
}
