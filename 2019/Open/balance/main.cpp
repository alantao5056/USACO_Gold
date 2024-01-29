#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

int N;
vector<bool> l;
vector<bool> r;

ll solve()
{
    int lp = -1;
    int l1 = 0;
    ll lt = 0;
    int lz = 0;
    ll rt = 0;
    int rz = 0;
    for (int i = N-1; i >= 0; i--)
    {
        if (l[i])
        {
            l1++;
            if (lp == -1) lp = i;
        }
        if (l[i])
        {
            lt += lz;
        } else
        {
            lz++;
        }

        if (r[i])
        {
            rt += rz;
        } else
        {
            rz++;
        }
    }

    int rp = -1;
    int r1 = 0;
    vector<int> lpre(N);
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            lpre[i] = l[i];
        } else
        {
            lpre[i] = lpre[i-1] + l[i];
        }
        if (!r[i])
        {
            r1++;
            if (rp == -1) rp = i;
        }
    }

    ll result = abs(lt-rt);
    ll swaps = 0;

    while (lp >= 0 && rp < N)
    {
        int s1 = (N - 1 - lp) + rp + 1;
        swaps += s1;
        lt -= (N - 1 - lp);
        rt -= rp;
        l1--;
        r1--;
        lt += l1;
        rt += r1;
        result = min(result, abs(lt-rt) + swaps);

        lp--;
        while (lp >= 0 && !l[lp])
        {
            lp--;
        }

        rp++;
        while (rp < N && r[rp])
        {
            rp++;
        }
    }

    return result;
}

ll solve2()
{
    int lp = -1;
    int l1 = 0;
    ll lt = 0;
    int lz = 0;
    ll rt = 0;
    int rz = 0;
    vector<int> rpre(N+1);
    for (int i = N-1; i >= 0; i--)
    {
        if (!l[i])
        {
            l1++;
            if (lp == -1) lp = i;
        }
        if (l[i])
        {
            lt += lz;
        } else
        {
            lz++;
        }

        rpre[i] = rpre[i+1];
        if (r[i])
        {
            rt += rz;
        } else
        {
            rpre[i]++;
            rz++;
        }
    }

    int rp = -1;
    int r1 = 0;
    vector<int> lpre(N);
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            lpre[i] = l[i];
        } else
        {
            lpre[i] = lpre[i-1] + l[i];
        }
        if (r[i])
        {
            r1++;
            if (rp == -1) rp = i;
        }
    }

    ll result = abs(lt-rt);
    ll swaps = 0;

    while (lp >= 0 && rp < N)
    {
        int s1 = (N - 1 - lp) + rp + 1;
        swaps += s1;
        // lt -= (N - 1 - lp);
        //rt += rp;
        l1--;
        r1--;
        lt -= lpre[lp];
        rt -= rpre[rp];
        result = min(result, abs(lt-rt) + swaps);

        lp--;
        while (lp >= 0 && !l[lp])
        {
            lp--;
        }

        rp++;
        while (rp < N && r[rp])
        {
            rp++;
        }
    }

    return result;
}

int main()
{
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        l.push_back(x);
    }

    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        r.push_back(x);
    }

    ll result1 = solve();
    ll result2 = solve2();

    cout << min(result1, result2) << endl;

    return 0;
}
