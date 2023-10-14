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

int N, B;

struct Snow
{
    int val;
    Snow* next;
    int nextDist = 1;
    Snow* prev;
    int prevDist = 1;

    Snow(int val)
    {
        this->val = val;
    }
};

struct Boot
{
    int depth;
    int step;
    bool result;
    int idx;

    Boot(int depth, int step, int idx)
    {
        this->depth = depth;
        this->step = step;
        this->idx = idx;
    }
};

struct comp
{
    inline bool operator() (const Snow &s1, const Snow &s2)
    {
        return (s1.val > s2.val);
    }
};

struct comp2
{
    inline bool operator() (const Boot &b1, const Boot &b2)
    {
        return (b1.depth > b2.depth);
    }
};

struct comp3
{
    inline bool operator() (const Boot &b1, const Boot &b2)
    {
        return (b1.idx < b2.idx);
    }
};

int main() {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    cin >> N >> B;
    vector<Snow> snow;
    f(i, 0, N)
    {
        int val;
        cin >> val;
        Snow cur = Snow(val);
        snow.pb(cur);
    }

    snow[0].prev = NULL;
    snow[0].next = &snow[1];
    snow[0].val = -1;
    snow[N-1].next = NULL;
    snow[N-1].prev = &snow[N-2];
    snow[N-1].val = -1;

    f(i, 1, N-1)
    {
        snow[i].prev = &snow[i-1];
        snow[i].next = &snow[i+1];
    }

    sort(snow.begin(), snow.end(), comp());

    vector<Boot> boots;
    f(i, 0, B)
    {
        int a, b;
        cin >> a >> b;
        Boot boot = Boot(a, b, i);
        boots.pb(boot);
    }

    sort(boots.begin(), boots.end(), comp2());

    int b = 0;
    int s = 0;
    int maxStep = 1;

    while (b < boots.size())
    {
        while (snow[s].val > boots[b].depth)
        {
            // remove snow[s]
            Snow* next = snow[s].next;
            Snow* prev = snow[s].prev;
            next->prev = prev;
            next->prevDist = snow[s].prevDist + snow[s].nextDist;
            maxStep = max(maxStep, next->prevDist);
            prev->next = next;
            prev->nextDist = snow[s].prevDist + snow[s].nextDist;
            maxStep = max(maxStep, prev->nextDist);

            s++;
        }

        if (boots[b].step >= maxStep)
        {
            // true
            boots[b].result = true;
        } else
        {
            boots[b].result = false;
        }
        b++;
    }

    sort(boots.begin(), boots.end(), comp3());

    f(i, 0, B)
    {
        cout << boots[i].result << endl;
    }

    return 0;
}
