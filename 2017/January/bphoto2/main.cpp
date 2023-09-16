#include <bits/stdc++.h>

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

using namespace std;

int N;

class Node {
public:
  int val;
  Node* right = NULL;
  Node* left = NULL;
  int rightNum = 0;
  Node(int val) {
    this->val = val;
  }
};

int recursive(Node* n, int cur, int ans)
{
  if (cur > n->val)
  {
    n->rightNum++;
    if (n->right == NULL)
    {
      // put it there
      Node* v = new Node(cur);
      n->right = v;
      return ans;
    }

    return recursive(n->right, cur, ans);
  }

  // cur < n.val
  int newAns = ans + n->rightNum + 1;
  if (n->left == NULL)
  {
    // put it there
    Node* v = new Node(cur);
    n->left = v;
    return newAns;
  }

  return recursive(n->left, cur, newAns);
}

int main()
{
  freopen("bphoto.in", "r", stdin);
  freopen("bphoto.out", "w", stdout);

  cin >> N;
  vi cows(N);
  f(i, 0, N) {
    cin >> cows[i];
  }

  vi left(N); // stores how many are bigger on the left
  Node* root = new Node(cows[0]);

  f(i, 1, N)
  {
    int result = recursive(root, cows[i], 0);
    left[i] = result;
  }

  vi right(N);
  root = new Node(cows[N-1]);
  rf(i, N-1, 0)
  {
    int result = recursive(root, cows[i], 0);
    right[i] = result;
  }

  int c = 0;
  f(i, 0, N)
  {
    if (left[i]*2 < right[i] || right[i] * 2 < left[i])
    {
      c++;
    }
  }

  cout << c << endl;

  return 0;
}
