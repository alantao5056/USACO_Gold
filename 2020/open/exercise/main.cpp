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
#define fi first
#define se second

// FUNCTIONS
#define f(i,s,e) for(int i=s;i<e;i++)
#define cf(i,s,e) for(int i=s;i<=e;i++)
#define rf(i,e,s) for(int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

void setIO(string name) {
  ios_base::sync_with_stdio(0); cin.tie(0);
  freopen((name+".in").c_str(),"r",stdin);
  freopen((name+".out").c_str(),"w",stdout);
}

#define MAXN 1000000
int spf[MAXN];

void sieve()
{
    spf[1] = 1;
    for (int i = 2; i < MAXN; i++)
    {
        spf[i] = i;
    }
        // marking smallest prime factor for every
        // number to be itself.

    // separately marking spf for every even
    // number as 2
    for (int i = 4; i < MAXN; i += 2)
    {
        spf[i] = 2;
    }

    for (int i = 3; i * i < MAXN; i++) {
        // checking if i is prime
        if (spf[i] == i) {
            // marking SPF for all numbers divisible by i
            for (int j = i * i; j < MAXN; j += i)
            {

            // marking spf[j] if it is not
            // previously marked
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

bool isPrime(int number){

    if(number < 2) return false;
    if(number == 2) return true;
    if(number % 2 == 0) return false;
    for(int i=3; (i*i)<=number; i+=2){
        if(number % i == 0 ) return false;
    }
    return true;

}

ll getFactorization(int x)
{
    int orig = x;
    map<int, int> primes;
    while (x != 1) {
        primes[spf[x]]++;
        if (!isPrime(spf[x]))
        {
            cout << "NOOOOOO" << endl;
        }
        x = x / spf[x];
    }

    ll ret = 0;
    int product = 1;
    for (auto const& [key, val] : primes)
    {
        product *= pow(key, val);
        ret += pow(key, val);
    }

    if (product != orig) cout << "NOOOOOOOO" <<endl;
    return ret;
}

int N;
ll M;

int main() {
    setIO("exercise");

    cin >> N >> M;
    sieve();
    ll result = 0;
    cf(i, 1, pow(N, 3))
    {
        if (getFactorization(i) <= N)
        {
            result += i;
        }
        result %= M;
    }

    cout << result << endl;

    return 0;
}
