#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 31004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, trace[mn], pos[mn], high[mn];
int inShortest[mn], mark[mn], co = 0;
vector<int> g[mn];
queue<int> q, shortest;

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
        g[i].clear();
    memset(trace, 0, sizeof(int) * (n + 1));
    memset(pos, 0, sizeof(int) * (n + 1));
    memset(high, 0, sizeof(int) * (n + 1));
    co ++;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
    }
}

void bfs()
{
    trace[1] = -1;
    q.push(1);
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
                q.push(v);
            }
        }
    }
}

void findShortest(int u)
{
    if (u != 1)
        findShortest(trace[u]);
    shortest.push(u);
    pos[u] = high[u] = shortest.size();
    inShortest[u] = co;
}

void dfs(int u)
{
    mark[u] = co;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (inShortest[u] == co && inShortest[v] == co)
            continue;
        if (inShortest[v] != co && mark[v] != co)
            dfs(v);
        high[u] = max(high[u], high[v]);
    }
}

void xuly()
{
    bfs();
    findShortest(n);
    int ans = 0, top = 0;
    while(!shortest.empty())
    {
        int u = shortest.front();
        shortest.pop();
        if (pos[u] > top && u != 1)
        {
            ans = u;
            break;
        }
        if (mark[u] != co)
            dfs(u);
        top = max(top, high[u] - 1);
    }
    while(!shortest.empty())
        shortest.pop();
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    while(t --)
    {
        setup();
        xuly();
    }
    return 0;
}
