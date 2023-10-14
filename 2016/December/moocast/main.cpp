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

bool canReach(int a1, int b1, int a2, int b2, int x)
{
    return pow(abs(a1 - a2), 2) + pow(abs(b1 - b2), 2) <= x;
}

bool isValid(vi& cows1, vi& cows2, int x)
{
    vb visited(N);
    queue<int> q1;
    queue<int> q2;
    q1.push(cows1[0]);
    q2.push(cows2[0]);
    visited[0] = true;

    while (!q1.empty())
    {
        int a = q1.front();
        int b = q2.front();
        q1.pop();
        q2.pop();

        f(i, 0, N)
        {
            if (!visited[i])
            {
                if (canReach(a, b, cows1[i], cows2[i], x))
                {
                    q1.push(cows1[i]);
                    q2.push(cows2[i]);
                    visited[i] = true;
                }
            }
        }
    }

    f(i, 0, N)
    {
        if (!visited[i])
        {
            return false;
        }
    }

    return true;
}

int main() {
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);

    cin >> N;

    vi cows1(N);
    vi cows2(N);

    f(i, 0, N)
    {
        int a, b;
        cin >> a >> b;
        cows1[i] = a;
        cows2[i] = b;
    }

    int low = 1;
    int high = 125000000;

    while (low < high) { // notice we do not compare element at mid with our target
        int mid = low + (high - low) / 2;
        if (isValid(cows1, cows2, mid))
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }

    cout << low << endl;
    return 0;
}
