#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second

int N, P;

struct Point
{
    bool start;
    Point *head;
    int x, y;
    int val;
};

vector<Point> points;
vector<Point*> points2;

struct comp
{
    inline bool operator() (const Point* p1, const Point* p2)
    {
        if (p1->x < p2->x) return true;
        if (p2->x < p1->x) return false;
        if (p1->y < p2->y) return true;
        if (p2->y < p1->y) return false;
        return p1->start;
    }
};


int main()
{
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);

    cin >> N >> P;

    points.resize(P*2);
    points2.resize(P*2);

    for (int i = 0; i < P; i++)
    {
        cin >> points[i*2].x >> points[i*2].y;
        points[i*2].start = true;
        cin >> points[i*2+1].x >> points[i*2+1].y;
        points[i*2+1].start = false;
        points2[i*2] = &points[i*2];
        points2[i*2+1] = &points[i*2+1];
        points[i*2+1].head = &points[i*2];
    }

    sort(points2.begin(), points2.end(), comp());

    map<int, int> m;
    m[0]=0;
    for (int i = 0; i < 2*P; i++)
    {
        if (points2[i]->start) // start
        {
            points2[i]->val = points2[i]->x + points2[i]->y + prev(m.upper_bound(points2[i]->y))->s;
        } else // end
        {
            int val = points2[i]->head->val - points2[i]->x - points2[i]->y;
            auto it = prev(m.upper_bound(points2[i]->y));
            if (it->s > val) // saves less than val
            {
                it++;
                while (it != end(m) && it->s > val)
                {
                    m.erase(it++);
                }
                m[points2[i]->y] = val;
            }
        }
    }

    cout << m.rbegin()->s + 2*N << endl;

    return 0;
}
