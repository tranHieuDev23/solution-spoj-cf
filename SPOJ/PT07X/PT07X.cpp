#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, dp[mn][2];
vector<int> g[mn];

void setup()
{
    int u, v;
    cin >> n;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(int u, int p)
{
    int one = 0, zero = 0;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p)
            continue;
        dfs(v, u);
        one += dp[v][1];
        zero += dp[v][0];
    }
    dp[u][0] = one + 1;
    dp[u][1] = min(one + 1, zero);
}

void xuly()
{
    dfs(1, 0);
    cout << dp[1][1];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    setup ();
    xuly ();
    return 0;
}
