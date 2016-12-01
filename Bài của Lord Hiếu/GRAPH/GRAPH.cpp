#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 20004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, num[mn], low[mn], rig = 0;
int numChild[mn], numDepend[mn], p[mn], tplt = 0;
vector<int> g[mn];
bool isRoot[mn], cutVer[mn];

void setup()
{
    cin >> n >> m;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(int u)
{
    num[u] = low[u] = ++ rig;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p[u])
            continue;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            numChild[u] ++;
            p[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
}

void prepareCut()
{
    FOR(u, 1, n)
    if (!num[u])
    {
        tplt ++;
        isRoot[u] = true;
        dfs(u);
    }
    FOR(v, 1, n)
    if (!isRoot[v])
    {
        int u = p[v];
        if (low[v] >= num[u])
        {
            cutVer[u] |= (numChild[u] >= 2) || (!isRoot[u]);
            numDepend[u] ++;
        }
    }
}

int ans(int u)
{
    if (isRoot[u] && !numChild[u])
        return tplt - 1;
    if (!cutVer[u])
        return tplt;
    if (isRoot[u])
        return tplt + numDepend[u] - 1;
    return tplt + numDepend[u];
}

void xuly()
{
    prepareCut();
    FOR(u, 1, n)
        cout << ans(u) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("GRAPH.INP", "r", stdin);
    freopen("GRAPH.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
