#include <bits/stdc++.h>
using namespace std;

// TYPES
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define vb vector<bool>
#define vc vector<char>;
#define vs vector<string>;
#define mii map<int, int>
#define si set<int>
#define sc set<char>

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

int N, D;

struct Pie {
  public:
  int b;
  int e;
  int id;
  bool who;
  bool visited = false;
  int result = 1000000000;
  vi nbs;

  Pie(int b, int e, int id, bool who) {
    this->b = b;
    this->e = e;
    this->id = id;
    this->who = who;
  }
};

struct key1 {
  inline bool operator() (Pie& struct1, Pie& struct2) {
    return (struct1.e < struct2.e);
  }
};

struct key11
{
    bool operator() (const Pie & left, const Pie & right)
    {
        return left.e < right.e;
    }
    bool operator() (const Pie & left, float right)
    {
        return left.e < right;
    }
    bool operator() (float left, const Pie & right)
    {
        return left < right.e;
    }
};

struct key2 {
  inline bool operator() (Pie& struct1, Pie& struct2) {
    return (struct1.b < struct2.b);
  }
};

struct key22
{
    bool operator() (const Pie & left, const Pie & right)
    {
        return left.b < right.b;
    }
    bool operator() (const Pie & left, float right)
    {
        return left.b < right;
    }
    bool operator() (float left, const Pie & right)
    {
        return left < right.b;
    }
};

vector<Pie> e;
vector<Pie> b;

int main() {
  freopen("piepie.in", "r", stdin);
  freopen("piepie.out", "w", stdout);

  cin >> N >> D;

  vector<Pie> e(N, Pie(0, 0, 0, true));
  vector<Pie> b(N, Pie(0, 0, 0, false));

  f(i, 0, N) {
    int a1, a2;
    cin >> a1 >> a2;
    e[i].e = a1;
    e[i].b = a2;
    e[i].id = i;
  }

  f(i, 0, N) {
    int a1, a2;
    cin >> a1 >> a2;
    b[i].e = a1;
    b[i].b = a2;
    b[i].id = i;
  }

  sort(e.begin(), e.end(), key1());
  sort(b.begin(), b.end(), key2());

  f(i, 0, N) {
    if (e[i].visited) {
      cout << (e[i].result >= 1000000000 ? -1 : e[i].result) << endl;
      continue;
    }

    queue<Pie*> q;
    q.push(&e[i]);
    while (!q.empty()) {
      Pie* p = q.front();
      q.pop();
      if (p->who) { // elsie's
        if (p->b == 0) { // end
          // done
          p->result = 0;
          continue;
        }
        int low = lower_bound(b.begin(), b.end(), p->e, key22()) - b.begin();
        int hi = upper_bound(b.begin(), b.end(), p->e + D, key22()) - b.begin() -1;
        if (hi == b.size()) {
          hi--;
        }
        int result = 1000000000;
        cf(i, low, hi) {
          p->nbs.pb(i);
          if (!b[i].visited) {
            // add it
            b[i].visited = true;
            q.push(&b[i]);
          }
          result = min(result, b[i].result);
        }

        p->result = result + 1;
      } else { // bessie's
        if (p->e == 0) { // end
          // done
          p->result = 0;
          continue;
        }
        int low = lower_bound(e.begin(), e.end(), p->e, key11()) - e.begin();
        int hi = upper_bound(e.begin(), e.end(), p->e + D, key11()) - e.begin();
        if (hi == e.size()) {
          hi--;
        }
        int result = 1000000000;
        cf(i, low, hi) {
          if (!e[i].visited) {
            // add it
            e[i].visited = true;
            q.push(&e[i]);
          }
          result = min(result, e[i].result);
        }

        p->result = result + 1;
      }
    }

    cout << (e[i].result >= 1000000000 ? -1 : e[i].result) << endl;
  }

  return 0;
}