#include <bits/stdc++.h>
using namespace std;

// TYPES
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vb vector<bool>
#define vc vector<char>
#define vs vector<string>
#define vii vector<vector<int>>
#define mii map<int, int>
#define si set<int>
#define sc set<char>

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

int N;
int i_[] = {-1, 0, 1, 0};
int j_[] = {0, 1, 0, -1};
vector<vb> grid(22, vb(22));
int dist[22][22][4][22][22][4]; // 0: up, 1: right, 2: down, 3: left

int main()
{
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);
    cin >> N;
    f(a, 0, N+2)
    {
        f(b, 0, N+2)
        {
            f(c, 0, 4)
            {
                f(d, 0, N+2)
                {
                    f(e, 0, N+2)
                    {
                        f(g, 0, 4)
                        {
                            dist[a][b][c][d][e][g] = INT_MAX;
                        }
                    }
                }
            }
        }
    }


    // border
    cf(i, 0, N+1)
    {
        grid[i][0] = true;
        grid[i][N+1] = true;
        grid[0][i] = true;
        grid[N+1][i] = true;
    }

    cf(i, 1, N)
    {
        string s;
        cin >> s;
        cf(j, 1, N)
        {
            grid[i][j] = s[j-1]=='H';
        }
    }

    dist[N][1][0][N][1][1] = 0;

    queue<array<int, 6>> q;
    q.push({N, 1, 0, N, 1, 1});

    while (!q.empty())
    {
        array<int, 6> cur = q.front();
        int x1 = cur[0];
        int y1 = cur[1];
        int d1 = cur[2];
        int x2 = cur[3];
        int y2 = cur[4];
        int d2 = cur[5];

        q.pop();

        if (x1 == 1 && y1 == N && x2 == 1 && y2 == N)
        {
            cout << dist[x1][y1][d1][x2][y2][d2] << endl;
            return 0;
        }

        f(i, 0, 4)
        {
            if (i == 2) continue;
            int newD1 = (d1+i)%4;
            int newX1 = x1+i_[newD1];
            int newY1 = y1+j_[newD1];

            if (grid[newX1][newY1] || (x1 == 1 && y1 == N)) {
                newX1 = x1;
                newY1 = y1;
            }

            int newD2 = (d2+i)%4;
            int newX2 = x2+i_[newD2];
            int newY2 = y2+j_[newD2];

            if (grid[newX2][newY2] || (x2 == 1 && y2 == N)) {
                newX2 = x2;
                newY2 = y2;
            }

            int incre = newD1 == d1 ? 1 : 2;

            int steps = dist[x1][y1][d1][x2][y2][d2];

            if (steps+incre < dist[newX1][newY1][newD1][newX2][newY2][newD2])
            {
                dist[newX1][newY1][newD1][newX2][newY2][newD2] = steps+incre;
                q.push({newX1, newY1, newD1, newX2, newY2, newD2});
            }
        }
    }

    return 0;
}
