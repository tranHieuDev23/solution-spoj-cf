#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 102
#define maxC 1000000007
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define sz(x) (int(x.size()))

using namespace std;
struct edge
{
    int id, u, v, c, f;

    edge(int id = 0, int u = 0, int v = 0, int c = 0): id(id), u(u), v(v), c(c)
    {
        f = 0;
    }
};
int n, m, s, t, d[mn], mark[mn], num = 0;
int rs, rt, h[mn], pos[mn];
bool in[mn * mn];
pair< int , pair<int, int> > e[mn * mn];
vector<edge> ed;
vector<int> g[mn], ans;
queue<int> q;

void setup()
{
    cin >> n >> m;
    FOR(i, 1, m)
        cin >> e[i].S.F >> e[i].S.S >> e[i].F;
    cin >> s >> t;
    sort(e + 1, e + m + 1);
}

int root(int x)
{
    if (d[x])
        return (d[x] = root(d[x]));
    return x;
}

int maxTime()
{
    FORD(i, m, 1)
    {
        int r1 = root(e[i].S.F);
        int r2 = root(e[i].S.S);
        if (r1 == r2)
            continue;
        d[r1] = r2;
        if (root(s) == root(t))
            return e[i].F;
    }
    return 0;
}

void addEdge(int u, int v, int id)
{
    g[u].pb(sz(ed));
    ed.pb(edge(id, u, v, 1));
    g[v].pb(sz(ed));
    ed.pb(edge(id, v, u, 0));
}

void prepareFlow(int c)
{
    memset(d, 0, sizeof(int) * (n + 1));
    FORD(i, m, 1)
    {
        int r1 = root(e[i].S.F);
        int r2 = root(e[i].S.S);
        if (r1 == r2)
            continue;
        if (e[i].F > c)
            d[r1] = r2;
        else
        {
            addEdge(r1, r2, i);
            addEdge(r2, r1, i);
        }
    }
    rs = root(s);
    rt = root(t);
}

bool bfs()
{
    mark[rs] = ++ num;
    q.push(rs);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        pos[u] = 0;
        FOR(i, 0, sz(g[u]) - 1)
        {
            int id = g[u][i];
            int v = ed[id].v;
            if (mark[v] == num || ed[id].f == ed[id].c)
                continue;
            mark[v] = num;
            h[v] = h[u] + 1;
            q.push(v);
        }
    }
    return mark[rt] == num;
}

int dfs(int u, int low)
{
    if (u == rt || low == 0)
        return low;
    for(; pos[u] < sz(g[u]); pos[u] ++)
    {
        int id = g[u][pos[u]];
        int v = ed[id].v;
        if (h[v] != h[u] + 1 || ed[id].f == ed[id].c)
            continue;
        int get = dfs(v, min(low, ed[id].c - ed[id].f));
        if (get)
        {
            ed[id].f += get;
            ed[id ^ 1].f -= get;
            return get;
        }
    }
    return 0;
}

void markReach(int u)
{
    mark[u] = num;
    FOR(i, 0, sz(g[u]) - 1)
    {
        int id = g[u][i];
        int v = ed[id].v;
        if (mark[v] == num || ed[id].f == ed[id].c || !ed[id].c)
            continue;
        markReach(v);
    }
}

void xuly()
{
    int finT = maxTime();
    prepareFlow(finT);
    while(bfs())
        while(dfs(rs, maxC));
    num ++; markReach(rs);
    FOR(i, 0, sz(ed) - 1)
    {
        if (in[ed[i].id])
            continue;
        int u = ed[i].u;
        int v = ed[i].v;
        if ((mark[u] == num) == (mark[v] == num))
            continue;
        ans.pb(ed[i].id);
        in[ed[i].id] = true;
    }
    cout << sz(ans) << '\n';
    FOR(i, 0, sz(ans) - 1)
        cout << e[ans[i]].S.F << ' ' << e[ans[i]].S.S << '\n';
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
