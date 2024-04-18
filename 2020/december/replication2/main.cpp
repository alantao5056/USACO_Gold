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
vector<vector<int>> grid; // closest wall
vector<vector<int>> grid2; // replication
vector<vector<bool>> grid3; // result
vector<pair<int, int>> start;

void recursive(int i, int j, int t)
{
    int si = t/D;

    // replicate
    if (t%D == 0)
    {
        if (grid[i][j] > si) // ok
        {
            grid2[i][j] = max(grid2[i][j], si);
        } else
        {
            return;
        }
    }

    // move
    for (int k = 0; k < 4; k++)
    {
        int i2 = i + i_[k];
        int j2 = j + j_[k];

        if (grid[i2][j2] > si) // ok
        {
            grid2[i2][j2] = max(grid2[i2][j2], si);
            recursive(i2, j2, t+1);
        }
    }
}

int main()
{
    setIO("replication");
    cin >> N >> D;

    grid.resize(N, vector<int>(N, 1e9));
    grid2.resize(N, vector<int>(N, -1));

    for (int i = 0; i < N; i++)
    {
        string s; cin >> s;
        for (int j = 0; j < N; j++)
        {
            if (s[j] == '#') {
                grid[i][j] = 0;
            }
            else if (s[j] == 'S')
            {
                grid[i][j] = -1;
                start.push_back({i, j});
            }
            else // s[j] == '.'
            {
                grid[i][j] = -1;
            }
        }
    }

    for (int i = 1; i < N-1; i++)
    {
        for (int j = 1; j < N-1; j++)
        {
            if (grid[i][j] == -1)
            {
                grid[i][j] = min(grid[i-1][j], grid[i][j-1]) + 1;
            }
        }
    }

    for (int i = N-2; i > 0; i--)
    {
        for (int j = N-2; j > 0; j--)
        {
            grid[i][j] = min(grid[i][j], min(grid[i+1][j], grid[i][j+1])+1);
        }
    }

//    for (int i = 0; i < N; i++)
//    {
//        for (int j = 0; j < N; j++)
//        {
//            cout << grid[i][j] << " ";
//        }
//        cout << endl;
//    }

    for (auto p : start)
    {
        int i = p.first;
        int j = p.second;
        recursive(i, j, 0);
    }

//    for (int i = 0; i < N; i++)
//    {
//        for (int j = 0; j < N; j++)
//        {
//            cout << grid2[i][j] << " ";
//        }
//        cout << endl;
//    }

    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 1; i < N-1; i++)
    {
        for (int j = 1; j < N-1; j++)
        {
            if (grid2[i][j] != -1)
            {
                pq.push({grid2[i][j], {i, j}});
            }
        }
    }


    while (!pq.empty())
    {
        auto ij = pq.top(); pq.pop();
        int i = ij.second.first;
        int j = ij.second.second;

        for (int k = 0; k < 4; k++)
        {
            int i2 = i + i_[k];
            int j2 = j + j_[k];
            if (grid2[i][j]-1 > grid2[i2][j2])
            {
                grid2[i2][j2] = grid2[i][j]-1;
                pq.push({grid2[i2][j2], {i2, j2}});
            }
        }
    }

    int result = 0;
    for (int i = 1; i < N-1; i++)
    {
        for (int j = 1; j < N-1; j++)
        {
            if (grid2[i][j] != -1)
            {
                result++;
            }
        }
    }

    cout << result << endl;

    return 0;
}
