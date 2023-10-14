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
ll M;

bool valid(vector<pii>& meals, int spice)
{
    ll cur = 0;

    f(i, 0, N)
    {
        if (meals[i].second > spice)
        {
            if (cur >= M)
            {
                return true;
            }
            cur = 0;
        } else
        {
            cur += meals[i].first;
        }
    }

    return cur >= M;
}

int main() {
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);

    cin >> N;
    cin >> M;

    vector<pii> meals(N, {0, 0});
    f(i, 0, N)
    {
        cin >> meals[i].first >> meals[i].second;
    }

    int low = 0;
    int high = 1000000000;

    while (low < high) { // notice we do not compare element at mid with our target
        int mid = low + (high - low) / 2;
        if (valid(meals, mid))
            high = mid;
        else
            low = mid + 1;
    }

    cout << low << endl;

    return 0;
}
