#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 102
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, k, val[mn], dp[mn][mn];
int ans = 0, mark[mn], co = 0;
vector<int> g[mn];

void setup()
{
    cin >> n >> k;
    int m, v;
    FOR(u, 1, n)
    {
        cin >> val[u] >> m;
        FOR(i, 1, m)
        {
            cin >> v;
            g[u].pb(v);
        }
    }
}

int temp[mn];

void calcDp(int u)
{
    mark[u] = co;
    dp[u][0] = 0;
    FOR(i, 1, k)
        dp[u][i] = val[u];
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v] == co)
            continue;
        calcDp(v);
        FOR(i, 0, k)
            temp[i] = dp[u][i];
        dp[u][0] = 0;
        FOR(i, 1, k)
        {
            dp[u][i] = val[u];
            FOR(j, 1, i)
                dp[u][i] = max(dp[u][i], temp[j] + dp[v][i - j]);
        }
    }
}

void xuly()
{
    FOR(u, 1, n)
    {
        co ++;
        calcDp(u);
        ans = max(ans, dp[u][k]);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("OPTION.INP", "r", stdin);
    freopen("OPTION.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
