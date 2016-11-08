#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 7503
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)

using namespace std;
int n, m, x, y, d[mn];
vector<int> g[mn], ans;
queue<int> q;
bool mark[mn], mark2[mn];

void setup()
{
    cin >> n >> m >> x >> y;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void bfs()
{
    mark[x] = true;
    q.push(x);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (mark[v])
                continue;
            mark[v] = true;
            d[v] = d[u] + 1;
            q.push(v);
        }
    }
}

void findAns()
{
    mark2[y] = true;
    q.push(y);
    while(!q.empty())
    {
        int sz = q.size();
        if (sz == 1)
            ans.pb(q.front());
        while(sz --)
        {
            int u = q.front();
            q.pop();
            FOR(i, 0, int(g[u].size()) - 1)
            {
                int v = g[u][i];
                if (mark2[v] || d[v] != d[u] - 1)
                    continue;
                mark2[v] = true;
                q.push(v);
            }
        }
    }
}

void xuly()
{
    bfs();
    findAns();
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    FOR(i, 0, int(ans.size()) - 1)
        cout << ans[i] << ' ';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("GRAPH.INP", "r", stdin);
    freopen("GRAPH.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
