#include <bits/stdc++.h>

using namespace std;

void setIO(string name) {
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen((name+".in").c_str(),"r",stdin);
    freopen((name+".out").c_str(),"w",stdout);
}

int ci(char c)
{
    return ((int) c) - 97;
}

int main()
{
    setIO("uddered");

    vector<set<char>> l(26);
    vector<set<char>> r(26);

    string abc = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 26; i++)
    {
        l[i].insert(abc[i]);
        r[i].insert(abc[i]);
    }

    string s;
    cin >> s;
    int N = s.size();

    int result = 1;
    int prev = 0;

    for (int i = 1; i < N; i++)
    {
        bool flag = false;
        for (int j = i-1; j >= prev; j--) {
            if (r[ci(s[i])].find(s[j]) != r[ci(s[i])].end() || l[ci(s[j])].find(s[i]) != l[ci(s[j])].end())
            {
                //cout << s.substr(prev, i-prev) << endl;
                prev = i;
                result++;
                flag = true;
                break;
            }
        }

        if (flag) continue;

        for (int j = i-1; j >= prev; j--)
        {
            r[ci(s[j])].insert(s[i]);
            for (char c : l[ci(s[j])]) {
                l[ci(s[i])].insert(c);
            }
        }
    }

    cout << result << endl;

    return 0;
}
