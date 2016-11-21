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
int n, m, s, t, d[mn], trace[mn];
long long dis[mn];
vector< pair<int, long long> > g[mn];
priority_queue< pair<long long, int> > p;
vector<int> ans;

struct edge
{
    int u, v;
    long long h, d;

    bool operator < (const edge& x)
    {
        return h > x.h;
    }
} ed[mn];

int root(int x)
{
    if (d[x])
        return (d[x] = root(d[x]));
    return x;
}

void setup()
{
    cin >> n >> m >> s >> t;
    FOR(i, 1, m)
        cin >> ed[i].u >> ed[i].v >> ed[i].h >> ed[i].d;
}

void kruskal()
{
    sort(ed + 1, ed + m + 1);
    long long low = -1;
    FOR(i, 1, m)
    {
        if (low != -1 && ed[i].h != low)
            break;
        int &u = ed[i].u, &v = ed[i].v;
        long long &w = ed[i].d;
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
        int r1 = root(u), r2 = root(v);
        if (r1 == r2)
            continue;
        d[r1] = r2;
        if (low == -1)
            if (root(s) == root(t))
                low = ed[i].h;
    }
}

void dijiktra()
{
    memset(dis, 60, sizeof(long long) * (n + 1));
    dis[s] = 0;
    p.push(mp(0, s));
    while(!p.empty())
    {
        int u = p.top().S;
        long long w = - p.top().F;
        p.pop();
        if (dis[u] != w)
            continue;
        if (u == t)
            return;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            long long e = g[u][i].S;
            if (dis[v] <= w + e)
                continue;
            dis[v] = w + e;
            trace[v] = u;
            p.push(mp(-dis[v], v));
        }
    }
}

void getAns()
{
    while(t)
    {
        ans.pb(t);
        t = trace[t];
    }
    cout << ans.size() << '\n';
    FORD(i, int(ans.size()) - 1, 0)
        cout << ans[i] << ' ';
}

void xuly()
{
    kruskal();
    dijiktra();
    getAns();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("TUNNEL.INP", "r", stdin);
    freopen("TUNNEL.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
