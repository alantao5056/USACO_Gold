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

int main() {
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);

    cin >> N;
    vi dishes(N);
    f(i, 0, N)
    {
        cin >> dishes[i];
    }

    map<int, stack<int>> m;
    int curMax = 0;
    int i = 0;
    bool flag = false;
    for (; i < N; i++)
    {
        if (dishes[i] < curMax)
        {
            flag = true;
            break;
        }
        auto it = m.lower_bound(dishes[i]);

        if (it == m.end())
        {
            // biggest so form new
            stack<int> s;
            m[dishes[i]] = s;
        } else
        {
            while (!m[it->first].empty() && m[it->first].top() < dishes[i])
            {
                curMax = max(curMax, m[it->first].top());
                m[it->first].pop();
            }
            m[it->first].push(dishes[i]);
        }
    }

    cout << i << endl;

    return 0;
}
