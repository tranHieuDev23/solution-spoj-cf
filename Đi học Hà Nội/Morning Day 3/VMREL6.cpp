#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 102
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn][mn], num[mn], low[mn], rig = 0;
int belong[mn], numScc = 0, out[mn], val[mn];
vector< pair<int, int> > g[mn], h[mn];
stack<int> st;
queue<int> q;

void addEdge(int u, int v, int x)
{
    if (x == 0)
        g[u].pb(mp(v, 0)), g[v].pb(mp(u, 0));
    if (x == -1)
        g[u].pb(mp(v, 1));
    if (x == 1)
        g[v].pb(mp(u, 1));
    if (x == -2)
        g[u].pb(mp(v, 0));
    if (x == 2)
        g[v].pb(mp(u, 0));
}

void setup()
{
    cin >> n;
    FOR(u, 1, n)
    FOR(v, 1, n)
    {
        cin >> a[u][v];
        if (u > v)
        {
            int absUV = abs(a[u][v]);
            int absVU = abs(a[v][u]);
            if (absUV == 2 && absVU == 2)
            {
                if (a[u][v] == a[v][u])
                    a[u][v] = a[v][u] = 0;
                continue;
            }
            if (absUV != 2 && absVU != 2)
                continue;
            if (absUV != 2)
                a[v][u] = - a[u][v];
            else
                a[u][v] = - a[v][u];
        }
    }
    FOR(u, 2, n)
    FOR(v, 1, u - 1)
        addEdge(u, v, a[u][v]);
}

void dfs(int u)
{
    num[u] = low[u] = ++ rig;
    st.push(u);
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }

    if (low[u] == num[u])
    {
        numScc ++;
        while(true)
        {
            int v = st.top();
            st.pop();
            num[v] = maxC;
            belong[v] = numScc;
            if (v == u)
                break;
        }
    }
}

void xuly()
{
    FOR(i, 1, n)
    if (!num[i])
        dfs(i);
    FOR(u, 1, n)
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (belong[u] == belong[v])
            continue;
        out[belong[u]] ++;
        h[belong[v]].pb(mp(belong[u], g[u][i].S));
    }

    FOR(i, 1, numScc)
    if (!out[i])
        q.push(i), val[i] = 1;
    int ans = 1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        ans = max(ans, val[u]);
        FOR(i, 0, int(h[u].size()) - 1)
        {
            int v = h[u][i].F;
            int w = h[u][i].S;
            val[v] = max(val[v], val[u] + w);
            if (-- out[v] == 0)
                q.push(v);
        }
    }
    cout << ans << '\n';
    FOR(u, 1, n)
        cout << val[belong[u]] << ' ';
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
