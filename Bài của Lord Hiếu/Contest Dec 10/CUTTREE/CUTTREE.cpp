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
int n, k, dp[mn][mn][2];
vector<int> g[mn];

void setup()
{
    cin >> n >> k;
    int u, v;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void add(int& a, int const b)
{
    if ((a += b) >= maxC)
        a -= maxC;
}

int mul(int const a, int const b)
{
    return 1ll * a * b % maxC;
}

int temp[mn][2];

void dfs(int u, int p)
{
    dp[u][1][1] = 1;
    dp[u][0][0] = 1;

    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p)
            continue;
        dfs(v, u);

        FOR(x, 0, k)
        FOR(y, 0, 1)
            temp[x][y] = dp[u][x][y];

        FOR(x, 0, k)
        {
            dp[u][x][1] = 0;
            FOR(y, 0, x)
            {
                add(dp[u][x][1], mul(temp[y][1], dp[v][x - y][0]));
                add(dp[u][x][1], mul(temp[y][1], dp[v][x - y + 1][1]));
            }
            dp[u][x][0] = 0;
            FOR(y, 0, x)
            {
                add(dp[u][x][0], mul(temp[y][0], dp[v][x - y][0]));
                add(dp[u][x][0], mul(temp[y][0], dp[v][x - y][1]));
            }
        }
    }
}

void xuly()
{
    dfs(1, 0);
    int ans = 0;
    add(ans, dp[1][k][1]);
    add(ans, dp[1][k][0]);
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("CUTTREE.INP", "r", stdin);
    freopen("CUTTREE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
