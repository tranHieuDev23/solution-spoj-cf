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
int n, m, logn, num[mn], low[mn], fin[mn];
int rig = 0, p[mn][18], child[mn], q;
bool isCut[mn];
vector<int> g[mn];

void setup()
{
    cin >> n >> m;
    logn = log2(n);
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    cin >> q;
}

void dfs(int u)
{
    num[u] = low[u] = ++ rig;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p[u][0])
            continue;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            p[v][0] = u;
            FOR(i, 1, logn)
                p[v][i] = p[p[v][i - 1]][i - 1];
            child[u] ++;
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
    }
    fin[u] = rig;
}

bool isAncestor(int u, int v)
{
    if (!u)
        return true;
    return (num[u] <= num[v] && num[v] <= fin[u]);
}

int closeLCA(int u, int v)
{
    FORD(i, logn, 0)
    if (!isAncestor(p[u][i], v))
        u = p[u][i];
    return u;
}

bool Query1()
{
    int a, b, g1, g2;
    cin >> a >> b >> g1 >> g2;
    if (g1 != p[g2][0] && g2 != p[g1][0])
        return true;
    if (g1 == p[g2][0])
        swap(g1, g2);
    if (low[g1] <= num[g2])
        return true;
    bool isAncestorA = isAncestor(g1, a);
    bool isAncestorB = isAncestor(g1, b);
    return isAncestorA == isAncestorB;
}

bool Query2()
{
    int a, b, c;
    cin >> a >> b >> c;
    if (!isCut[c])
        return true;
    bool isAncestorA = isAncestor(c, a);
    bool isAncestorB = isAncestor(c, b);
    if (!isAncestorA && !isAncestorB)
        return true;
    int la = closeLCA(a, c);
    int lb = closeLCA(b, c);
    bool upA = (low[la] < num[c]);
    bool upB = (low[lb] < num[c]);
    if (isAncestorA && isAncestorB)
        return la == lb || (upA && upB);
    if (isAncestorA)
        return upA;
    return upB;
}

void xuly()
{
    dfs(1);
    FOR(v, 2, n)
    {
        int u = p[v][0];
        if (low[v] >= num[u])
            isCut[u] |= (p[u] != 0) || (child[u] >= 2);
    }
    int t;
    while(q --)
    {
        cin >> t;
        bool ans = (t == 1? Query1(): Query2());
        cout << (ans? "yes\n" : "no\n");
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("NKPOLICE.INP", "r", stdin);
    freopen("NKPOLICE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
