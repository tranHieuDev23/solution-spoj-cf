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

    edge(int v = 0, int c = 0): v(v), c(c) {f = 0;}
};
int n, m, s, t, mark[mn], num = 0, d[mn], pos[mn];
vector<edge> e;
vector<int> g[mn];
queue<int> q;

void setup()
{
    cin >> n >> m >> s >> t;
    int u, v, w;
    FOR(i, 1, m)
    {
        cin >> u >> v >> w;
        g[u].pb(e.size());
        e.pb(edge(v, w));
        g[v].pb(e.size());
        e.pb(edge(u, 0));
    }
}

bool bfs()
{
    mark[s] = ++ num;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        pos[u] = 0;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int id = g[u][i];
            int v = e[id].v;
            if (mark[v] == num || e[id].f == e[id].c)
                continue;
            mark[v] = num;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    return mark[t] == num;
}

int dfs(int u, int low)
{
    if (u == t || low == 0)
        return low;
    for(; pos[u] < int(g[u].size()); pos[u] ++)
    {
        int id = g[u][pos[u]];
        int v = e[id].v;
        if (d[v] != d[u] + 1 || e[id].f == e[id].c)
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
    long long ans = 0;
    while(bfs())
    {
        while(int x = dfs(s, maxC))
            ans += x;
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
