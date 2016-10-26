#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 10004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, s, t, pos[mn], hig[mn], trace[mn];
bool mark[mn];
vector<int> g[mn];
queue<int> q, way;

void setup()
{
    cin >> n >> m >> s >> t;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
    }
}

void bfs()
{
    trace[s] = s;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (!trace[v])
            {
                trace[v] = u;
                if (v == t)
                    return;
                q.push(v);
            }
        }
    }
}

void makeWay(int u)
{
    if (u == s)
    {
        way.push(u);
        pos[u] = hig[u] = 1;
        return;
    }
    makeWay(trace[u]);
    way.push(u);
    pos[u] = hig[u] = way.size();
}

void dfs(int u)
{
    mark[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (pos[v] && pos[u])
            continue;
        if (!mark[v] && !pos[v])
            dfs(v);
        hig[u] = max(hig[u], hig[v]);
    }
}

void xuly()
{
    bfs();
    makeWay(t);
    int top = 0, ans = 0;
    while(!way.empty())
    {
        int u = way.front();
        way.pop();
        ans += (pos[u] > top);
        if (!mark[u])
            dfs(u);
        top = max(top, hig[u] - 1);
    }
    cout << ans - 2;
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
