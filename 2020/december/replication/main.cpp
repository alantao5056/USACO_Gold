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

int main()
{
    setIO("replication");

    cin >> N >> D;

    vector<vector<bool>> grid(N, vector<bool>(N));
    vector<tuple<int, int, int, int>> every; // last one: 0: up   1: down   2: left   3:right    4: all
    deque<pair<int, int>> pos;
    deque<int> time2;
    for (int i = 0; i < N; i++)
    {
        string s; cin >> s;
        for (int j = 0; j < N; j++)
        {
            if (s[j] == '#')
            {
                grid[i][j] = false;
            } else if (s[j] == '.')
            {
                grid[i][j] = true;
            } else
            {
                pos.push_back({i, j});
                time2.push_back(0);
                every.push_back(make_tuple(i, j, 0, 4));
                grid[i][j] = true;
            }
        }
    }

    while (!time2.empty())
    {
        pair<int, int> ij = pos.front(); pos.pop_front();
        int i = ij.first;
        int j = ij.second;
        int t = time2.front(); time2.pop_front();
        int si = t/D;

        if (t%D == 0)
        {
            bool repl = true;
            for (int z = 0; z <= si; z++)
            {
                if (!grid[i+z][j+(si-z)] || !grid[i-z][j+(si-z)] || !grid[i+z][j-(si-z)] || !grid[i-z][j-(si-z)])
                {
                    repl = false;
                    break;
                }
            }
            // time2 to replicate
            if (repl)
            {
                pos.push_back({i,j});
                time2.push_back(t+1);
                every.push_back(make_tuple(i, j, si, 4));
            } else {
                continue;
            }
        }

        // up
        bool up = true;
        for (int z = 0; z <= si; z++)
        {
            if (!grid[i-z-1][j+(si-z)] || !grid[i-z-1][j-(si-z)])
            {
                up = false;
                break;
            }
        }
        if (up)
        {
            pos.push_back({i-1, j});
            time2.push_back(t+1);
            every.push_back(make_tuple(i-1, j, si, 0));
        }
        // down
        bool down = true;
        for (int z = 0; z <= si; z++)
        {
            if (!grid[i+z+1][j+(si-z)] || !grid[i+z+1][j-(si-z)])
            {
                down = false;
                break;
            }
        }
        if (down)
        {
            pos.push_back({i+1, j});
            time2.push_back(t+1);
            every.push_back(make_tuple(i+1, j, si, 1));
        }
        // left
        bool left = true;
        for (int z = 0; z <= si; z++)
        {
            if (!grid[i+z][j-(si-z)-1] || !grid[i-z][j-(si-z)-1])
            {
                left = false;
                break;
            }
        }

        if (left)
        {
            pos.push_back({i, j-1});
            time2.push_back(t+1);
            every.push_back(make_tuple(i, j-1, si, 2));
        }

        // right
        bool right = true;
        for (int z = 0; z <= si; z++)
        {
            if (!grid[i+z][j+(si-z)+1] || !grid[i-z][j+(si-z)+1])
            {
                right = false;
                break;
            }
        }
        if (right)
        {
            pos.push_back({i, j+1});
            time2.push_back(t+1);
            every.push_back(make_tuple(i, j+1, si, 3));
        }

    }

//    for (auto e : every)
//    {
//        cout << get<0>(e) << " " << get<1>(e) << " " << get<2>(e) << " " << get<3>(e) << endl;
//    }

    vector<vector<bool>> result(N, vector<bool>(N));
    for (auto e : every)
    {
        if (get<3>(e) == 4) // all
        {
            for (int i = 0; i <= get<2>(e); i++)
            {
                result[get<0>(e) + i][get<1>(e) + get<2>(e)-i] = true;
                result[get<0>(e) - i][get<1>(e) + get<2>(e)-i] = true;

                result[get<0>(e) + i][get<1>(e) - (get<2>(e)-i)] = true;
                result[get<0>(e) - i][get<1>(e) - (get<2>(e)-i)] = true;
            }
        } else if (get<3>(e) == 0) // up
        {
            for (int i = 0; i <= get<2>(e); i++)
            {
                result[get<0>(e) - i][get<1>(e) - (get<2>(e)-i)] = true;
                result[get<0>(e) - i][get<1>(e) + get<2>(e)-i] = true;
            }
        } else if (get<3>(e) == 1) // down
        {
            for (int i = 0; i <= get<2>(e); i++)
            {
                result[get<0>(e) + i][get<1>(e) - (get<2>(e)-i)] = true;
                result[get<0>(e) + i][get<1>(e) + get<2>(e)-i] = true;
            }
        } else if (get<3>(e) == 2) // left
        {
            for (int i = 0; i <= get<2>(e); i++)
            {
                result[get<0>(e) + i][get<1>(e) - (get<2>(e)-i)] = true;
                result[get<0>(e) - i][get<1>(e) - (get<2>(e)-i)] = true;
            }
        } else // right
        {
            for (int i = 0; i <= get<2>(e); i++)
            {
                result[get<0>(e) + i][get<1>(e) + get<2>(e)-i] = true;
                result[get<0>(e) - i][get<1>(e) + get<2>(e)-i] = true;
            }
        }
    }

    int total = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            total += result[i][j];
            //cout << result[i][j] << " ";
        }
        //cout << endl;
    }

    cout << total << endl;

    return 0;
}
