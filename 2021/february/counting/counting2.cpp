#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int Q;

vector<ll> full(40);
vector<ll> po3(40);

void gen_full(int k, ll dif) {
  // generates all of the possible k with given dif
  // base case
  if (k == 0) {
    full[k] = (dif == 0);
    return;
  }

  if (dif < po3[k-1]) {
    // triple hit
    gen_full(k-1, dif);
    full[k] = 3*full[k-1];
  } else {
    // dif > po3[k-1]
    ll newDif = abs(dif - 2*po3[k-1]);
    gen_full(k-1, newDif);
    full[k] = full[k-1];
  }
}

ll rec(ll x, ll y, int k) {
  if (x < 0 || y < 0) return 0;
  x %= po3[k], y %= po3[k];
  if (x < y) swap(x, y);
  if (k == 0) return 1;
  
  // single hit
  if (x-y > po3[k-1]) {
    if (x < 2*po3[k-1]) return 0;
    if (y < po3[k-1]) return rec(x, y, k-1);
    if (y >= po3[k-1]) return full[k-1];
  }
  // multiple hit
  if (x < po3[k-1]) return rec(x, y, k-1);
  if (y < po3[k-1]) return full[k-1];
  if (x < 2*po3[k-1]) return full[k-1] + rec(x, y, k-1);
  if (y < 2*po3[k-1]) return 2* full[k-1];
  // triple partial hit
  return 2*full[k-1] + rec(x, y, k-1);
}

int main() {
  // freopen("counting.in", "r", stdin);
  // freopen("counting.out", "w", stdout);

  cin >> Q;

  // initialize po3
  po3[0] = 1;
  for (int i = 1; i < 40; i++) {
    po3[i] = po3[i-1] * 3;
  } 

  // read queries
  for (int i = 0; i < Q; i++) {
    ll d, x, y;
    cin >> d >> x >> y;
    
    if (x < y) swap(x, y);
    gen_full(39, x-y);
    cout << rec(x+d, y+d, 39) - rec(x-1, y-1, 39) << endl;
    // for (int j = 0; j < 40 ; j++) {
    //   cout << full[j] << endl;
    // }
    // cout << endl;
  }
  return 0;
}