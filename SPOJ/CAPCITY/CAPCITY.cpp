#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, num[mn], low[mn], belong[mn];
int rig = 0, numScc = 0, zeroOut, out[mn];
vector<int> g[mn], scc[mn];
stack<int> st;

void setup()
{
    cin >> n >> m;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
    }
}

void dfs(int u)
{
    num[u] = low[u] = ++ rig;
    st.push(u);
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
    if (num[u] == low[u])
    {
        numScc ++;
        while(true)
        {
            int v = st.top();
            st.pop();
            num[v] = maxC;
            belong[v] = numScc;
            scc[numScc].pb(v);
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
    zeroOut = numScc;
    FOR(u, 1, n)
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (belong[u] != belong[v])
        {
            if (out[belong[u]] == 0)
                zeroOut --;
            out[belong[u]] ++;
        }
    }
    if (zeroOut > 1)
        cout << 0;
    else
    FOR(i, 1, numScc)
    if (out[i] == 0)
    {
        cout << scc[i].size() << '\n';
        sort(scc[i].begin(), scc[i].end());
        FOR(j, 0, int(scc[i].size()) - 1)
            cout << scc[i][j] << ' ';
    }
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
