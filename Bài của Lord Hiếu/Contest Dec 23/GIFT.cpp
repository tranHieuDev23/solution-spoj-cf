#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 5005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, s[mn], dp[mn][mn], high[mn];
vector<int> g[mn];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> s[i];
    int u, v;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    memset(dp, 60, sizeof(dp));
}

void dfs(int u, int p)
{
    vector<int> child = vector<int>();
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p)
            continue;
        dfs(v, u);
        child.pb(v);
    }

    if (child.size() == 0)
    {
        dp[u][0] = s[u];
        dp[u][1] = abs(s[u] - 1);
        high[u] = 1;
        return;
    }

    if (child.size() == 1)
    {
        int v = child[0];
        FOR(i, 0, high[v])
            dp[u][i] = dp[v][i] + abs(s[u] - i);
        high[u] = high[v];
        return;
    }

    int v1 = child[0], v2 = child[1];
    FOR(i, 0, high[v1])
    FOR(j, 0, high[v2])
        dp[u][i + j] = min(dp[u][i + j], dp[v1][i] + dp[v2][j] + abs(s[u] - i - j));
    high[u] = high[v1] + high[v2];
}

void xuly()
{
    dfs(1, 0);
    int ans = maxC;
    FOR(i, 0, mn - 1)
        ans = min(ans, dp[1][i]);
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("GIFT.INP", "r", stdin);
    freopen("GIFT.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
