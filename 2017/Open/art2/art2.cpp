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

int N;

int main() {
  freopen("art2.in", "r", stdin);
  freopen("art2.out", "w", stdout);

  bool works = false;
  cin >> N;
  vi arr(N);
  f(i, 0, N) {
    cin >> arr[i];
    if (arr[i] != 0) {
      works = true;
    }
  }

  if (!works) {
    // all zeros
    cout << -1 << endl;
    return 0;
  }

  vb end(N);
  si s;
  rf(i, N, 0) {
    if (!s.count(arr[i])) {
      end[i] = true;
      s.insert(arr[i]);
    }
  }

  vi layers(N, -1);
  vb visited(N);
  stack<int> st;
  si set;
  int result = 0;
  int curLayers = 0;

  f(i, 0, N) {
    if (arr[i] == 0) {
      if (st.size() > 0) {
        works = false;
        break;
      }
      continue;
    }

    if (set.count(arr[i])) {
      // is in set
      if (st.top() != arr[i]) {
        // layer below has an element in above layer
        works = false;
        break;
      }

      // it's current layer
      // check if end
      if(end[i]) {
        st.pop();
        curLayers--;
      }
    } else {
      // not in set
      if (visited[arr[i]]) {
        works = false;
        break;
      }

      // new start

      // check if end
      curLayers++;
      result = max(result, curLayers);
      if (!end[i]) {
        st.push(arr[i]);
        set.insert(arr[i]);
      } else {
        curLayers--;
      }
    }
  }

  if (works && st.size() == 0) {
    cout << result << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}