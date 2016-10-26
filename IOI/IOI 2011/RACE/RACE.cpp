#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define mn2 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, k, sz[mn], spe[mn], best[mn2];
int mark[mn2], num = 0, ans = maxC;
bool done[mn];
vector< pair<int, int> > g[mn];

void setup()
{
    cin >> n >> k;
    int u, v, w;
    FOR(i, 1, n - 1)
    {
        cin >> u >> v >> w;
        u ++, v ++;
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }
}

void dfs(int u)
{
    sz[u] = 1, spe[u] = 0;
    done[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (done[v])
            continue;
        dfs(v);
        if (sz[v] > sz[spe[u]])
            spe[u] = v;
        sz[u] += sz[v];
    }
    done[u] = false;
}

int getCentroid(int u)
{
    int siz = (sz[u] >> 1);
    while(sz[spe[u]] > siz)
        u = spe[u];
    return u;
}

void digDown(int u, int sumL, int h)
{
    if (sumL >= k)
    {
        if (sumL == k)
            ans = min(ans, h);
        return;
    }
    int other = k - sumL;
    if (mark[other] != num)
        mark[other] = num, best[other] = maxC;
    ans = min(ans, best[other] + h);
    done[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (done[v])
            continue;
        digDown(v, sumL + g[u][i].S, h + 1);
    }
    done[u] = false;
}

void update(int u, int sumL, int h)
{
    if (sumL >= k)
        return;
    if (mark[sumL] != num)
        mark[sumL] = num, best[sumL] = maxC;
    best[sumL] = min(best[sumL], h);
    done[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (done[v])
            continue;
        update(v, sumL + g[u][i].S, h + 1);
    }
    done[u] = false;
}

void deal(int u)
{
    num ++;
    dfs(u);
    u = getCentroid(u);
    done[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (done[v])
            continue;
        int w = g[u][i].S;
        digDown(v, w, 1);
        update(v, w, 1);
    }
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (!done[v])
            deal(v);
    }
}

void xuly()
{
    deal(1);
    if (ans == maxC)
        cout << -1;
    else
        cout << ans;
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
