#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using namespace __gnu_pbds;
using namespace std;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

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

int main()
{
    freopen("sleepy.in", "r", stdin);
    freopen("sleepy.out", "w", stdout);

    cin >> N;

    vi arr(N);
    f(i, 0, N)
    {
        cin >> arr[i];
    }

    ordered_set os;
    int prev = INT_MAX;
    int last;
    rf(i, N, 0)
    {
        if (arr[i] < prev)
        {
            os.insert(arr[i]);
            prev = arr[i];
            last = i;
        } else
        {
            break;
        }
    }

    cout << last << endl;

    f(i, 0, last)
    {
        cout << last - i - 1 + os.order_of_key(arr[i]);
        if (i != last - 1)
        {
            cout << " ";
        } else
        {
            cout << endl;
        }

        os.insert(arr[i]);
    }

    return 0;
}
