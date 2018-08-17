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
int n, m, logn, p[mn][15], h[mn], num[mn];
vector< pair<int, int> > g[mn];

void setup()
{
    cin >> n >> m;
    logn = log2(n);
    int x, k;
    FOR(i, 2, n)
    {
        cin >> x >> k;
        g[x].pb(mp(i, k));
    }
}

void dfs(int u)
{
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        p[v][0] = u;
        FOR(j, 1, logn)
            p[v][j] = p[p[v][j - 1]][j - 1];
        h[v] = h[u] + 1;
        num[v] = num[u] + (g[u][i].S == 2);
        dfs(v);
    }
}

int lca(int a, int b)
{
    if (h[a] > h[b])
        swap(a, b);
    int dif = h[b] - h[a];
    FOR(i, 0, logn)
    if ((dif >> i) & 1)
        b = p[b][i];
    if (a == b)
        return a;
    FORD(i, logn, 0)
    if (p[a][i] != p[b][i])
    {
        a = p[a][i];
        b = p[b][i];
    }
    return p[a][0];
}

void xuly()
{
    dfs(1);
    int a, b;
    FOR(i, 1, m)
    {
        cin >> a >> b;
        int l = lca(a, b);
        int numTwo = num[a] + num[b] - (num[l] << 1);
        cout << (numTwo? "YES\n" : "NO\n");
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
