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

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

int N;

/*

this problem is about combinatorics

the main concern in this problem is the concern of overcounting
counting every cow with favorite ice cream flavor x doesn't really work.
because a cow can have favorite ice cream flavors x and y
so counting x and then counting y can result in overcounting

the key in this problem is to take advantage of the small amount of ice cream flavor a cow can have.
If we only have 5 ice cream flavors, it is possible to get all subsets of these flavors
then we can add all the subsets into a map and count the amount of cows with favorite ice cream flavors {x1, x2, ...}
we can then use a bit of math to get the final answer.

see PIE (Principle of Inclusion/Exclusion)

*/

int main() {
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);

    cin >> N;

    vector<map<array<int, 5>, int>> counts(6);

    f(i, 0, N)
    {
        array<int, 5> cur;
        cin >> cur[0] >> cur[1] >> cur[2] >> cur[3] >> cur[4];

        sort(cur.begin(), cur.end());

        counts[5][cur]++;

        f(a, 0, 5)
        {
            counts[1][{cur[a]}]++;
            f(b, a+1, 5)
            {
                counts[2][{cur[a], cur[b]}]++;
                f(c, b+1, 5)
                {
                    counts[3][{cur[a], cur[b], cur[c]}]++;
                    f(d, c+1, 5)
                    {
                        counts[4][{cur[a], cur[b], cur[c], cur[d]}]++;
                    }
                }
            }
        }
    }


    ll ans = 0;
    cf(i, 1, 5)
    {
        for (auto &[k, v] : counts[i])
        {
            ll pairs = (ll) v * (v-1) / 2;
            if (i % 2 == 0)
            {
                ans -= pairs;
            } else
            {
                ans += pairs;
            }
        }
    }

    cout << ((ll) N * (N-1) / 2) - ans << endl;

    return 0;
}
