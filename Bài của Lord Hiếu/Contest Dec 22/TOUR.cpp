#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define mn2 2003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define bitPos(x) (1 << (x))

using namespace std;
int n, m, s, t, d1[mn], d2[mn];
int in[mn2], high[mn2], num[mn2], low[mn2], rig = 0;
vector< pair<int, int> > g1[mn], g2[mn], g[mn2];
priority_queue< pair<int, int> > p;
queue<int> q;

void setup()
{
    cin >> n >> s >> t;
    int u, v, d;
    cin >> m;
    FOR(i, 1, m)
    {
        cin >> u >> v >> d;
        g1[u].pb(mp(v, d));
        g1[v].pb(mp(u, d));
    }
    cin >> m;
    FOR(i, 1, m)
    {
        cin >> u >> v >> d;
        g2[u].pb(mp(v, d));
        g2[v].pb(mp(u, d));
    }
}

void dijiktra(vector< pair<int, int> >* vec, int* mang)
{
    memset(mang, 60, sizeof(int) * (n + 1));
    mang[t] = 0;
    p.push(mp(0, t));
    while(!p.empty())
    {
        int u = p.top().S;
        int w = - p.top().F;
        p.pop();
        if (w != mang[u])
            continue;
        FOR(i, 0, int(vec[u].size()) - 1)
        {
            int v = vec[u][i].F;
            int d = vec[u][i].S;
            if (mang[v] <= w + d)
                continue;
            mang[v] = w + d;
            p.push(mp(- mang[v], v));
        }
    }
}

void constructGraph()
{
    FOR(u, 1, n)
    {
        FOR(i, 0, int(g1[u].size()) - 1)
        {
            int v = g1[u][i].F;
            int d = g1[u][i].S;
            if (d1[v] < d1[u])
                g[u].pb(mp(v + n, d));
        }

        FOR(i, 0, int(g2[u].size()) - 1)
        {
            int v = g2[u][i].F;
            int d = g2[u][i].S;
            if (d2[v] < d2[u])
                g[u + n].pb(mp(v, d));
        }
    }
}

void checkCycle(int u)
{
    num[u] = low[u] = ++ rig;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        in[v] ++;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            checkCycle(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] < num[u])
    {
        cout << -1;
        exit(0);
    }
    num[u] = maxC;
}

void calcAns()
{
    high[s] = 0;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int d = g[u][i].S;
            high[v] = max(high[v], high[u] + d);
            if (-- in[v] == 0)
                q.push(v);
        }
    }
}

void xuly()
{
    dijiktra(g1, d1);
    dijiktra(g2, d2);
    constructGraph();
    checkCycle(s);
    calcAns();
    cout << max(high[t], high[t + n]);
}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("TOUR.INP", "r", stdin);
    freopen("TOUR.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
