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

int N, K;

int main() {
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);

    cin >> N >> K;
    vector<vi> prefix(206, vi(206));
    f(i, 0, N)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1+=5; y1+=5; x2+=5; y2+=5;
        prefix[x1][y1]++;
        prefix[x1][y2+1]--;
        prefix[x2+1][y1]--;
        prefix[x2+1][y2+1]++;
    }

    vector<vi> barn(206, vi(206));

    f(i, 1, 206)
    {
        f(j, 1, 206)
        {
            barn[i][j] = prefix[i][j] + barn[i-1][j] + barn[i][j-1] - barn[i-1][j-1];
//            cout << barn[i][j] << " ";
        }
//        cout << endl;
    }

    f(i, 1, 206)
    {
        f(j, 1, 206)
        {

        }
    }

    return 0;
}
