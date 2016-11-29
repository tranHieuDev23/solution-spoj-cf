#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 10004
#define mn2 100005
#define maxC 2000000007
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define reset(x, k, sz) memset(x, 0, sizeof(k) * (sz + 1))

using namespace std;
int n, m, cost[mn], d[mn], ans[mn];
int rAns, sz[2], maxE[2];
pair< pair<int, int> , int > g[2][mn2];
bool use[mn2];

void setup()
{
    cin >> n >> m;
    rAns = sz[0] = sz[1] = cost[0] = 0;
    FOR(i, 1, n - 1)
        cin >> cost[i];
    int u, v, c;
    FORD(i, n - 2, 0)
    {
        cin >> c;
        cost[i] += c;
    }
    FOR(i, 1, m)
    {
        cin >> u >> v >> c;
        c --;
        g[c][++ sz[c]] = mp(mp(u, v), i);
    }
}

int root(int u)
{
    if (d[u])
        return root(d[u] = root(d[u]));
    return u;
}

void calcMax(int group)
{
    reset(d, int, n);
    maxE[group] = 0;
    FOR(i, 1, sz[group])
    {
        int r1 = root(g[group][i].F.F);
        int r2 = root(g[group][i].F.S);
        if (r1 == r2)
            continue;
        d[r1] = r2;
        if (++ maxE[group] == n - 1)
            return;
    }
}

int getMin()
{
    calcMax(0);
    calcMax(1);
    int best = maxC, re = -1;
    FOR(i, n - 1 - maxE[1], maxE[0])
    if (best > cost[i])
    {
        best = cost[i];
        re = i;
    }
    return re;
}

void kruskal(int group, int lim, bool Set)
{
    if (!lim)
        return;
    FOR(i, 1, sz[group])
    if (!use[i])
    {
        int r1 = root(g[group][i].F.F);
        int r2 = root(g[group][i].F.S);
        if (r1 == r2)
            continue;
        d[r1] = r2;
        use[i] = Set;
        ans[++ rAns] = g[group][i].S;
        if (-- lim == 0)
            return;
    }
}

void xuly()
{
    int numA = getMin();
    int numB = n - 1 - numA;
    kruskal(0, n - 1 - maxE[1], true);
    reset(d, 0, n);
    FOR(i, 1, sz[0])
    if (use[i])
    {
        int r1 = root(g[0][i].F.F);
        int r2 = root(g[0][i].F.S);
        d[r1] = r2;
        numA --;
    }
    kruskal(0, numA, true);
    reset(use, bool, m);
    kruskal(1, numB, false);
    sort(ans + 1, ans + rAns + 1);
    FOR(i, 1, rAns)
        cout << ans[i] << ' ';
    cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("AZNET.INP", "r", stdin);
    freopen("FILE.OUT", "w", stdout);
    int t; cin >> t;
    while(t)
    {
        setup ();
        xuly ();
        t --;
    }
    return 0;
}
