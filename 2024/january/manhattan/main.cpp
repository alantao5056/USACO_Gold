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
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define fi first
#define se second

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

int N, Q;

int main() {
    //setIO("manhattan");

    cin >> N >> Q;

    // original input
    vi h;
    vi v;
    f(i, 0, N)
    {
        string a;
        int b;
        cin >> a >> b;

        if (a == "H")
        {
            h.pb(b);
        } else
        {
            v.pb(b);
        }
    }

    sort(h.begin(), h.end());
    sort(v.begin(), v.end());

    // difference
    vi h2(h.size()-1);

    f(i, 0, h.size()-1)
    {
        h2[i] = h[i+1] - h[i];
    }

    vi v2(v.size()-1);
    f(i, 0, v.size()-1)
    {
        v2[i] = v[i+1] - v[i];
    }

    // chunks sum. (e, e, e, o)  (e, e, o) (o)
    int sum = 0;
    vi h3;
    f(i, 0, h2.size())
    {
        sum += h2[i];
        if (h2[i] % 2 != 0)
        {
            h3.pb(sum);
            sum = 0;
        }
    }

    sum = 0;
    vi v3;
    f(i, 0, v2.size())
    {
        sum += v2[i];
        if (v2[i] % 2 != 0)
        {
            v3.pb(sum);
            sum = 0;
        }
    }

    f(i, 0, Q)
    {
        int x, y, d;
        cin >> x >> y >> d;
        int lx = lower_bound(v.begin(), v.end(), x) - v.begin();
        int ly = lower_bound(h.begin(), h.end(), y) - h.begin();
        if (lx >= v.size()) // x out of bounds
        {
            cout << x + d << " " << y << endl;
            continue;
        }
        if (ly >= h.size()) // y out of bounds
        {
            cout << x << " " << y + d << endl;
            continue;
        }

        bool direct = true; // true = up     false = right
        if (v[lx] == x && h[ly] == y) // on intersection
        {

        } else if (v[lx] == x) // on vertical road
        {
            int dis = h[ly] - y;
            if (d <= dis)
            {
                cout << x << " " << y + d << endl;
               continue;
            }

            y += dis;
            d -= dis;
            direct = (dis % 2 == 0);
        } else // on horizontal road
        {
            int dis = v[lx] - x;
            if (d <= dis)
            {
               cout << x + d << " " << y << endl;
               continue;
            }

            x += dis;
            d -= dis;
            direct = (dis % 2 == 0);
        }

        bool flag = false;
        while (true)
        {
            if (direct) // up
            {
                if (ly >= h2.size()) break;
                if (h2[ly] >= d)
                {
                    cout << x << " " << y + d << endl;
                    flag = true;
                    break;
                }
                d -= h2[ly];
                y += h2[ly];
                if (h2[ly] % 2 != 0)
                {
                    direct = false;
                }
                ly++;
            } else // right
            {
                if (lx >= v2.size()) break;
                if (v2[lx] >= d)
                {
                    cout << x + d << " " << y << endl;
                    flag = true;
                    break;
                }
                d -= v2[lx];
                x += v2[lx];
                if (v2[lx] % 2 != 0)
                {
                    direct = true;
                }
                lx++;
            }
        }

        if (flag)
        {
            continue;
        }

        if (!direct) // going right
        {
            cout << x + d << " " << y << endl;
            continue;
        }

        // going up
        cout << x << " " << y + d << endl;
    }

    return 0;
}
