#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 802
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int p, n, m, t[mn], d[mn], c[mn][mn];
vector< pair<int, int> > g[mn];
priority_queue< pair< int, pair<int, int> > > pri;
bool mark[mn];
queue<int> q;

void setup()
{
    cin >> p >> n >> m;
    FOR(i, 1, n)
        cin >> t[i];
    int u, v, w;
    FOR(i, 1, m)
    {
        cin >> u >> v >> w;
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }
}

void query1()
{
    int ans = 0;
    mark[1] = true;
    q.push(1);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        ans = max(ans, t[u]);
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int w = g[u][i].S;
            if (mark[v] || w > t[1])
                continue;
            mark[v] = true;
            q.push(v);
        }
    }
    cout << ans;
}

void query2()
{
    memset(c, 60, sizeof(c));
    c[1][1] = 0;
    pri.push(mp(0, mp(1, 1)));
    while(!pri.empty())
    {
        int u = pri.top().S.F;
        int z = pri.top().S.S;
        int w = - pri.top().F;
        pri.pop();
        if (w != c[u][z])
            continue;
        if (u == n)
        {
            cout << w;
            return;
        }
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int e = g[u][i].S;
            if (e > t[z])
                continue;
            if (c[v][z] <= w + e)
                continue;
            c[v][z] = w + e;
            pri.push(mp(- c[v][z], mp(v, z)));
        }
        if (t[u] > t[z] && c[u][u] > w)
        {
            c[u][u] = w;
            pri.push(mp(- w, mp(u, u)));
        }
    }
}

void xuly()
{
    if (p == 1)
        query1();
    else
        query2();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("DRAGON.INP", "r", stdin);
    freopen("DRAGON.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
