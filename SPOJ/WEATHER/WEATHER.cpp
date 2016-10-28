#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 105
#define mn2 5003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, num[mn], low[mn], rig = 0, tplt = 0, belong[mn], sz[mn];
long long ans = 0;
stack<int> st;
vector<int> g[mn], h[mn];

void setup()
{
    cin >> n >> m;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(int u, int p)
{
    num[u] = low[u] = ++ rig;
    st.push(u);
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p)
            continue;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == num[u])
    {
        tplt ++;
        while(true)
        {
            int v = st.top();
            st.pop();
            belong[v] = tplt;
            sz[tplt] ++;
            if (v == u)
                break;
        }
    }
}

void dfs2(int u, int e, int s, int p)
{
    ans += e * sz[u] * sz[s];
    FOR(i, 0, int(h[u].size()) - 1)
    {
        int v = h[u][i];
        if (v == p)
            continue;
        dfs2(v, e + 1, s, u);
    }
}

void xuly()
{
    dfs(1, 0);
    FOR(u, 1, n)
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (belong[u] < belong[v])
        {
            h[belong[u]].pb(belong[v]);
            h[belong[v]].pb(belong[u]);
        }
    }
    FOR(i, 1, tplt)
        dfs2(i, 0, i, 0);
    cout << (ans >> 1);
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
