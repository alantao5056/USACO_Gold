#include <bits/stdc++.h>

using namespace std;
#define ll long long

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

int N;

int main()
{
    //setIO("exchange");

    cin >> N;
    vector<int> milk(N);
    vector<int> curMilk(N);
    ll tot = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> milk[i];
        curMilk[i] = milk[i];
        tot += milk[i];
    }

    for (int i = 0; i < N; i++)
    {
        vector<int> newMilk(N);

        for (int j = 0; j < N; j++)
        {
            int prev = curMilk[(j-1) == -1 ? N-1 : j-1];
            if (prev > milk[j])
            {
                tot -= prev - milk[j];
                newMilk[j] = milk[j];
            } else
            {
                newMilk[j] = prev;
            }
        }
        cout << tot << endl;
        curMilk = newMilk;
    }

    return 0;
}
