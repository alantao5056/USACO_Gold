#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXP = 1234;
const int MAXN = 10005;

LL res[MAXP][MAXN];  // result for permutations of length n restricted to using the first p primes

int n; LL m;

LL mul(LL x, LL y) {
    return (x * y) % m;
}

LL add(LL x, LL y) {
    x += y;
    if (x >= m) x -= m;
    return x;
}

LL sub(LL x, LL y) {
    x -= y;
    if (x < 0) x += m;
    return x;
}

int main() {
    freopen("exercise.in","r",stdin);
    freopen("exercise.out","w",stdout);
    cin >> n >> m;

    vector<int> composite(n+1);
    vector<int> primes;

    for (int i = 2; i <= n; i++) {
        if (!composite[i]) {
            primes.push_back(i);
            for (int j = 2*i; j <= n; j += i) {
                composite[j] = 1;
            }
        }
    }

    if (primes.size() == 0) {
        cout << "1\n";
        return 0;
    }

    for (int j = 0; j <= n; j++) res[0][j] = 1;  // identities

    for (int i = 1; i <= primes.size(); i++) {
        for (int j = 0; j <= n; j++) {
            res[i][j] = res[i-1][j];

            int pp = primes[i-1];
            while (pp <= j) {
                res[i][j] = add(res[i][j], mul(pp, res[i-1][j-pp]));
                pp *= primes[i-1];
            }
        }
    }

    cout << res[primes.size()][n] << "\n";
}
