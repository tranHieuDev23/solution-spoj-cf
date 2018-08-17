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
int n, m, num[mn], low[mn];
int rig = 0, sz[mn], p[mn], rootScc[3];
vector<int> g[mn];
long long ans = 0;

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
    sz[u] = 1;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p[u])
            continue;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            p[v] = u;
            dfs(v);
            low[u] = min(low[u], low[v]);
            sz[u] += sz[v];
        }
    }
}

void caseOne()
{
    int numBridge = 0;
    FOR(v, 1, n)
    {
        int u = p[v];
        if (!u || low[v] <= num[u])
            continue;
        numBridge ++;
        ans += 1ll * sz[v] * (n - sz[v]) - 1;
    }
    int nonBridge = m - numBridge;
    long long selectVert = (1ll * n * (n - 1) >> 1) - m;
    ans += selectVert * nonBridge;
}

void caseTwo()
{
    int numBridge = 0;
    FOR(v, 1, n)
    {
        int u = p[v];
        if (!u || low[v] <= num[u])
            continue;
        numBridge ++;
    }
    long long selectVert = 1ll * sz[rootScc[1]] * sz[rootScc[2]];
    ans = selectVert * (m - numBridge);
}

void xuly()
{
    int scc = 0;
    FOR(u, 1, n)
    if (!num[u])
    {
        if (++ scc == 3)
        {
            cout << 0;
            return;
        }
        rootScc[scc] = u;
        dfs(u);
    }
    if (scc == 1)
        caseOne();
    else
        caseTwo();
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("REFORM.INP", "r", stdin);
    freopen("REFORM.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
