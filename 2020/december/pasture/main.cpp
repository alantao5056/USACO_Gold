#include <bits/stdc++.h>

using namespace std;

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

int N;

int main()
{
    //setIO("pasture");

    cin >> N;

    vector<pair<int, int>> grid(N);
    for (int i = 0; i < N; i++)
    {
        cin >> grid[i].first >> grid[i].second;
    }

    sort(grid.begin(), grid.end());


    int tot = grid.size()+1;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int side = grid[j].first - grid[i].first;

            if (side < abs(grid[j].second - grid[i].second))
            {
                continue;
            }

            int a, b; // a is more y val
            if (grid[i].second < grid[j].second)
            {
                a = i;
                b = j;
            } else
            {
                b = i;
                a = j;
            }

            vector<int> ys;
            for (int k = i; k <= j; k++)
            {
                ys.push_back(grid[k].second);
            }

            sort(ys.begin(), ys.end());

            int stop = lower_bound(ys.begin(), ys.end(), grid[a].second) - ys.begin();

            // get e;
            int e = upper_bound(ys.begin(), ys.end(), grid[b].second) - ys.begin();
            int e_ = grid[b].second;

            // get s;
            int s = upper_bound(ys.begin(), ys.end(), grid[b].second - side) - ys.begin();
            int s_ = grid[b].second - side;

            while (s <= stop)
            {
                tot++;
                int sd = ys[s] - s_;
                int ed = e==ys.size() ? INT_MAX : (ys[e] - e_);

                if (sd < ed)
                {
                    s_ = ys[s];
                    s++;
                    e_ += sd;
                } else if (sd > ed)
                {
                    e_ = ys[e];
                    e++;
                    s_ += ed;
                } else
                {
                    tot++;
                    e_ = ys[e];
                    s_ = ys[s];
                    e++;
                    s++;
                }
            }
        }
    }

    sort(grid.begin(), grid.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int side = grid[j].second - grid[i].second;

            if (side <= abs(grid[j].first - grid[i].first))
            {
                continue;
            }

            int a, b; // a is more y val
            if (grid[i].first < grid[j].first)
            {
                a = i;
                b = j;
            } else
            {
                b = i;
                a = j;
            }

            vector<int> ys;
            for (int k = i; k <= j; k++)
            {
                ys.push_back(grid[k].first);
            }

            sort(ys.begin(), ys.end());

            int stop = lower_bound(ys.begin(), ys.end(), grid[a].first) - ys.begin();

            // get e;
            int e = upper_bound(ys.begin(), ys.end(), grid[b].first) - ys.begin();
            int e_ = grid[b].first;

            // get s;
            int s = upper_bound(ys.begin(), ys.end(), grid[b].first - side) - ys.begin();
            int s_ = grid[b].first - side;

            while (s <= stop)
            {
                tot++;
                int sd = ys[s] - s_;
                int ed = e==ys.size() ? INT_MAX : (ys[e] - e_);

                if (sd < ed)
                {
                    s_ = ys[s];
                    s++;
                    e_ += sd;
                } else if (sd > ed)
                {
                    e_ = ys[e];
                    e++;
                    s_ += ed;
                } else
                {
                    //tot++;
                    e_ = ys[e];
                    s_ = ys[s];
                    e++;
                    s++;
                }
            }
        }
    }

    cout << tot << endl;

    return 0;
}
