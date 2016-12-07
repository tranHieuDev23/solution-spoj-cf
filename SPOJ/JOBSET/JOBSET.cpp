#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 510
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
struct edge
{
    int v, c, f;

    edge(int v = 0, int c = 0): v(v), c(c) {f = 0;}
};
int n, m, p[mn], maxProfit = 0;
int s, t, d[mn], mark[mn], h[mn];
int co = 0, q[mn], cur[mn];
vector<int> g[mn];
vector<edge> e;

void addEdge(int u, int v, int c)
{
    g[u].pb(e.size());
    e.pb(edge(v, c));
    g[v].pb(e.size());
    e.pb(edge(u, 0));
}

void setup()
{
    cin >> n;
    s = 0, t = n + 1;
    FOR(i, 1, n)
    {
        cin >> p[i];
        if (p[i] > 0)
            maxProfit += p[i], addEdge(s, i, p[i]);
        else
            addEdge(i, t, -p[i]);
    }
    cin >> m;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        addEdge(u, v, maxProfit + 1);
    }
}

bool bfs()
{
    int l = 1, r = 1;
    q[1] = s, mark[s] = ++ co, h[s] = 0;
    while(l <= r)
    {
        int u = q[l ++];
        cur[u] = 0;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int id = g[u][i];
            int v = e[id].v;
            if (mark[v] == co || e[id].f == e[id].c)
                continue;
            mark[v] = co;
            h[v] = h[u] + 1;
            q[++ r] = v;
        }
    }
    return mark[t] == co;
}

int dfs(int u, int low)
{
    if (u == t || low == 0)
        return low;
    for(; cur[u] < int(g[u].size()); cur[u] ++)
    {
        int id = g[u][cur[u]];
        int v = e[id].v;
        if (h[v] != h[u] + 1 || e[id].f == e[id].c)
            continue;
        int get = dfs(v, min(low, e[id].c - e[id].f));
        if (get)
        {
            e[id].f += get;
            e[id ^ 1].f -= get;
            return get;
        }
    }
    return 0;
}

void xuly()
{
    int maxFlow = 0;
    while(bfs())
        while(int x = dfs(s, maxC))
            maxFlow += x;
    cout << maxProfit - maxFlow;
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
