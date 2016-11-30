#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;

struct edge
{
    int v, f, c;

    edge(int v = 0, int c = 0): v(v), c(c)
    {
        f = 0;
    }
};
int n, m, s, t;
vector<int> g[mn];
vector<edge> e;
int trace[mn], traceE[mn], minG[mn], Queue[mn];

void addEdge(int u, int v, int c)
{
    g[u].pb(e.size());
    e.pb(edge(v, c));
    g[v].pb(e.size());
    e.pb(edge(u, 0));
}

void setup()
{
    cin >> n >> m >> s >> t;
    int u, v, c;
    FOR(i, 1, m)
    {
        cin >> u >> v >> c;
        addEdge(u, v, c);
    }
}

bool findArgumentPath()
{
    memset(minG, 60, sizeof(minG));
    memset(trace, 0, sizeof(trace));
    trace[s] = s;
    int l = 1, r = 1;
    Queue[1] = s;
    while(l <= r)
    {
        int u = Queue[l ++];
        if (u == t)
            return true;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int id = g[u][i];
            if (e[id].f == e[id].c)
                continue;
            int v = e[id].v;
            if (trace[v])
                continue;
            trace[v] = u;
            traceE[v] = id;
            minG[v] = min(minG[u], e[id].c - e[id].f);
            Queue[++ r] = v;
        }
    }
    return false;
}

void increasing(int val)
{
    int v = t;
    while(v != s)
    {
        int id = traceE[v];
        e[id].f += val;
        e[id ^ 1].f -= val;
        v = trace[v];
    }
}

void xuly()
{
    long long ans = 0;
    while(findArgumentPath())
    {
        ans += minG[t];
        increasing(minG[t]);
    }
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
