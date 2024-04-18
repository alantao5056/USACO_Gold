#include <bits/stdc++.h>

typedef long long ll;
using namespace std;

int N;
int MOD = 1e9 + 7;
string s;

void setIO(string name) {
 ios_base::sync_with_stdio(0); cin.tie(0);
 freopen((name+".in").c_str(),"r",stdin);
 freopen((name+".out").c_str(),"w",stdout);
}

int main()
{
   setIO("genetics");
   cin >> s;
   int N = s.size();

   vector<int> g(N);
   vector<vector<int>> acgt(4, vector<int>());
   for (int i = 0; i < N; i++)
   {
	   if (s[i] == 'A')
	   {
		   g[i] = 0;
		   acgt[0].push_back(i);
	   } else if (s[i] == 'C')
	   {
		   g[i] = 1;
		   acgt[1].push_back(i);
	   } else if (s[i] == 'G')
	   {
		   g[i] = 2;
		   acgt[2].push_back(i);
	   } else if (s[i] == 'T')
	   {
		   g[i] = 3;
		   acgt[3].push_back(i);
	   } else
	   {
		   g[i] = 4;
		   acgt[0].push_back(i);
		   acgt[1].push_back(i);
		   acgt[2].push_back(i);
		   acgt[3].push_back(i);
	   }
   }

   vector<int> repeat(N);
   for (int i = 1; i < N; i++)
   {
	   if (g[i] == g[i-1])
	   {
		   repeat[i]++;
	   }
   }

   vector<ll> four(N, 1);
   for (int i = 0; i < N; i++)
   {
	   if (g[i] != 4) continue;
	   int left = i > 0 ? g[i-1] : -1;
	   int right = i < N-1 ? g[i+1] : -2;

	   if (left < 0 && right < 0)
	   {
		   four[i] = 4;
	   } else if (left < 0 || right < 0)
	   {
		   four[i] = 3;
	   } else if (left == right)
	   {
		   four[i] = 3;
	   } else
	   {
		   four[i] = 2;
	   }
   }

   for (int i = 1; i < N; i++)
   {
	   repeat[i] += repeat[i-1];
	   four[i] *= four[i-1];
	   four[i] %= MOD;
   }

   vector<vector<ll>> dp(N, vector<ll>(4));
   for (int i = 0; i < N; i++)
   {
	   for (int j = 0; j < 4; j++)
	   {
		   int p = upper_bound(acgt[j].begin(), acgt[j].end(), i) - acgt[j].begin() - 1;
		   ll cnt = 0;
		   while (p >= 0)
		   {
			   // if repeat
			   if (repeat[i] != repeat[acgt[j][p]])
			   { // repeat
				   break;
			   }

			   ll mult = four[i]/four[acgt[j][p]];
			   mult %= MOD;
			   if (acgt[j][p] > 0)
			   {
				   if (g[i] == 4)
				   {
					   for (int k = 0; k < 4; k++)
					   {
						   cnt += (dp[acgt[j][p]-1][k] * mult) % MOD;
					   }
				   } else
				   {
					   cnt += (dp[acgt[j][p]-1][g[i]] * mult) % MOD;
				   }
				   cnt %= MOD;
			   } else
			   {
				   cnt += mult; // ++
				   cnt %= MOD;
			   }
			   p--;
		   }
		   dp[i][j] = cnt;
	   }
   }

   // for (int j = 0; j < 4; j++)
   // {
   //	 for (int i = 0; i < N; i++)
   //	 {
   //		 cout << dp[i][j] << " ";
   //	 }
   //	 cout << endl;
   // }

   ll tot = 0;
   for (int i = 0; i < 4; i++)
   {
	   tot += dp[N-1][i];
	   tot %= MOD;
   }

   cout << tot << endl;

   return 0;
}
