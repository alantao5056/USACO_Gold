#include <bits/stdc++.h>
using namespace std;

// TYPES
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vii vector<pii>
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

int N;
vii hair;
vi val;

vii mSort(vii arr)
{
    vii newArr;
    if (arr.size() == 1)
    {
        newArr.pb(arr[0]);
        return newArr;
    }

    int half = arr.size()/2;
    vii left(arr.begin(), arr.begin() + half);
    vii right(arr.begin() + half, arr.end());
    vii left2 = mSort(left);
    vii right2 = mSort(right);
    int lp = 0;
    int rp = 0;

    while (lp < left2.size() && rp < right2.size())
    {
        if (left2[lp].fi > right2[rp].fi)
        {
            newArr.pb(left2[lp]);
            lp++;
        } else
        {
            newArr.pb(right2[rp]);
            val[right2[rp].se] += lp;
            rp++;
        }
    }
    while (lp < left2.size())
    {
        newArr.pb(left2[lp]);
        lp++;
    }
    while (rp < right2.size())
    {
        newArr.pb(right2[rp]);
        val[right2[rp].se] += lp;
        rp++;
    }
    return newArr;
}

int main() {
    setIO("haircut");

    cin >> N;
    hair.resize(N);
    val.resize(N);

    f(i, 0, N)
    {
        cin >> hair[i].fi;
        hair[i].se = i;
    }

    mSort(hair);
    sort(hair.begin(), hair.end());

    ll tot = 0;
    int lines = 0;
    cf(i, 0, hair[0].fi)
    {
        cout << 0 << endl;
        lines++;
    }
    f(i, 0, N-1)
    {
        tot += val[hair[i].se];
        f(j, hair[i].fi, hair[i+1].fi)
        {
            if (lines == N) break;
            cout << tot << endl;
            lines++;
        }
    }

    while (lines < N)
    {
        cout << tot << endl;
        lines++;
    }

    return 0;
}
