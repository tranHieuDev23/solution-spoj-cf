#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 5003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, f[mn], dp[mn][mn], sumDp[mn];
string s;
vector<int> duplicate[mn];

void setup()
{
    cin >> n >> s;
    m = s.size();
}

int add(int const a, int const b)
{
    int ret = a + b;
    if (ret < 0)
        ret += maxC;
    if (ret >= maxC)
        ret -= maxC;
    return ret;
}

void prepare()
{
    f[0] = -1, f[1] = 0;
    int id = 0;
    FOR(i, 2, m)
    {
        while(id != -1 && s[i - 1] != s[id])
            id = f[id];
        f[i] = ++ id;
        duplicate[f[i]].pb(i);
    }
}

void xuly()
{
    prepare();
    dp[m][m] = sumDp[m] = 1;
    FOR(i, m + 1, n)
    FOR(j, 1, m)
    {
        dp[i][j] = sumDp[i - j];
        FOR(k, 0, int(duplicate[j].size()) - 1)
        {
            int x = duplicate[j][k];
            dp[i][j] = add(dp[i][j], - sumDp[i - x]);
        }
        sumDp[i] = add(sumDp[i], dp[i][j]);
    }
    cout << sumDp[n];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("WORDS.INP", "r", stdin);
    freopen("WORDS.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
