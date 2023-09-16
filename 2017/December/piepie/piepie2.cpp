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
  bool who;
  int e;
  int b;
  int dist = -1;

  Pie(bool who, int e, int b) {
    this->who = who;
    this->e = e;
    this->b = b;
  }
};

struct comp1 {
  inline bool operator() (const Pie* p1, const Pie* p2) const {
    return (p1->e < p2->e);
  }
};

struct comp2 {
  inline bool operator() (const Pie* p1, const Pie* p2) const {
    return (p1->b < p2->b);
  }
};

int main() {
  freopen("piepie.in", "r", stdin);
  freopen("piepie.out", "w", stdout);

  cin >> N >> D;
  vector<Pie> e2(N, Pie(true, 0, 0));
  vector<Pie> b2(N, Pie(false, 0, 0));
  multiset<Pie*, comp2> e;
  multiset<Pie*, comp1> b;
  queue<Pie*> q;

  f(i, 0, N) {
    int curE, curB;
    cin >> curE >> curB;
    e2[i].e = -curE;
    e2[i].b = -curB;
  }
  
  f(i, 0, N) {
    int curE, curB;
    cin >> curE >> curB;
    b2[i].e = -curE;
    b2[i].b = -curB;
  }

  f(i, 0, N) {
    Pie* p = &e2[i];
    if (p->b == 0) {
      p->dist = 1;
      q.push(p);
    } else {
      e.insert(p);
    }
  }

  f(i, 0, N) {
    Pie* p = &b2[i];
    if (p->e == 0) {
      p->dist = 1;
      q.push(p);
    } else {
      b.insert(p);
    }
  }

  // Pie dummy = Pie(false, 0, 0);
  while (!q.empty()) {
    Pie* p = q.front();
    q.pop();

    if (p->who) { // elsie
      // dummy.e = p->e-D;
      while (true) {
        auto itr = b.lower_bound(p);
        auto p2 = *itr;
        if (itr == b.end() || p2->e > p->e + D) {
          break;
        }
        p2->dist = p->dist + 1;
        q.push(p2);
        b.erase(itr);
      }
    } else { // bessie
      // dummy.b = p->b-D;
      while (true) {
        auto itr = e.lower_bound(p);
        auto p2 = *itr;
        if (itr == e.end() || p2->b > p->b + D) {
          break;
        }
        p2->dist = p->dist + 1;
        q.push(p2);
        e.erase(itr);
      }
    }
  }

  f(i, 0, N) {
    cout << e2[i].dist << endl;
  }

  return 0;
}