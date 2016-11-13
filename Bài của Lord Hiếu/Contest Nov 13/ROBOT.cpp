#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 502
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, d[mn], refuel[mn], remain[mn];
vector< pair< int, pair<int, int> > > g[mn];
priority_queue< pair<int, int> > p;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> refuel[i];
    cin >> m;
    int u, v, t, c;
    FOR(i, 1, m)
    {
        cin >> u >> v >> t >> c;
        g[u].pb(mp(v, mp(t, c)));
        g[v].pb(mp(u, mp(t, c)));
    }
}

void IJK()
{
    memset(d, 1, sizeof(int) * (n + 1));
    d[1] = 0;
    p.push(mp(0, 1));
    while(!p.empty())
    {
        int u = p.top().S;
        int w = - p.top().F;
        p.pop();
        if (w > d[u])
            continue;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int t = g[u][i].S.F;
            if (w + t >= d[v])
                continue;
            d[v] = w + t;
            p.push(mp(- d[v], v));
        }
    }
}

bool check(int w)
{
    memset(remain, -1, sizeof(int) * (n + 1));
    remain[1] = w;
    p.push(mp(0, 1));
    while(!p.empty())
    {
        int u = p.top().S;
        p.pop();
        if (refuel[u])
            remain[u] = w;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            if (d[v] != d[u] + g[u][i].S.F)
                continue;
            if (remain[u] < g[u][i].S.S)
                continue;
            if (remain[v] == -1)
                p.push(mp(- d[v], v));
            remain[v] = max(remain[v], remain[u] - g[u][i].S.S);
        }
    }
    return remain[n] != -1;
}

void xuly()
{
    IJK();
    int l = 0, r = maxC;
    while(r - l > 1)
    {
        int g = ((l + r) >> 1);
        if (check(g))
            r = g;
        else
            l = g;
    }
    cout << r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("ROBOT.INP", "r", stdin);
    freopen("ROBOT.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
