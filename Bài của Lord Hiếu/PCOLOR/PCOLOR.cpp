#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 102
#define mn2 10004
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
int n, w[mn][mn], b[mn][mn], c[mn][mn][4];
int addX[] = {-1, 0, 1, 0};
int addY[] = {0, 1, 0, -1};
int sumV = 0, m, s, t, mark[mn2];
int co = 0, d[mn2], cur[mn2];
vector<int> g[mn2];
vector<edge> e;
queue<int> q;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    FOR(j, 1, n)
        cin >> w[i][j];
    FOR(i, 1, n)
    FOR(j, 1, n)
        cin >> b[i][j];
    FOR(i, 1, n)
    FOR(j, 1, n)
    FOR(k, 0, 3)
        cin >> c[i][j][k];
}

void addEdge(int u, int v, int c)
{
    g[u].pb(e.size());
    e.pb(edge(v, c));
    g[v].pb(e.size());
    e.pb(edge(u, 0));
}

void buildGraph()
{
    m = n * n;
    s = 0, t = m + 1;
    FOR(i, 1, n)
    FOR(j, 1, n)
    {
        sumV += b[i][j] + w[i][j];
        int u = (i - 1) * n + j;
        addEdge(s, u, w[i][j]);
        addEdge(u, t, b[i][j]);
        FOR(k, 0, 3)
        {
            int x = i + addX[k];
            int y = j + addY[k];
            if (x < 1 || y < 1 || x > n || y > n)
                continue;
            int v = (x - 1) * n + y;
            addEdge(u, v, c[i][j][k]);
        }
    }
}

bool bfs()
{
    mark[s] = ++ co;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        cur[u] = 0;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int id = g[u][i];
            int v = e[id].v;
            if (mark[v] == co || e[id].f == e[id].c)
                continue;
            mark[v] = co;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
    return mark[t] == co;
}

int dfs(int u, int low)
{
    if (u == t)
        return low;
    for(; cur[u] < int(g[u].size()); cur[u] ++)
    {
        int id = g[u][cur[u]];
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
    buildGraph();
    int minCut = 0;
    while(bfs())
        while(int x = dfs(s, maxC))
            minCut += x;
    cout << sumV - minCut;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("PCOLOR.INP", "r", stdin);
    freopen("PCOLOR.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
