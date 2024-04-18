#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

struct Point {
  int pos;
  bool start;
  int other;
};

struct less_than_key
{
    inline bool operator() (const Point& struct1, const Point& struct2)
    {
        return (struct1.pos < struct2.pos);
    }
};

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int N;

int main() {
  freopen("grass.in", "r", stdin);
  freopen("grass.out", "w", stdout);

  cin >> N;

  vector<Point> points;

  for (int i = 0; i < N; i++) {
    int a, b, c;
    cin >> a >> b >> c;

    Point p = Point();
    p.pos = a;
    p.start = true;
    p.other = b;

    Point p2 = Point();
    p2.pos = b;
    p2.start = false;
    p2.other = a;

    points.push_back(p);
    points.push_back(p2);
  }

  sort(points.begin(), points.end(), less_than_key());

  ordered_set os;

  os.insert(4);
  os.insert(4);
  os.erase(4);
  cout << *os.find_by_order(0) << endl;

  for (Point p : points) {
    if (p.start) {
      
    } else {

    }
  }
  
  return 0;
}