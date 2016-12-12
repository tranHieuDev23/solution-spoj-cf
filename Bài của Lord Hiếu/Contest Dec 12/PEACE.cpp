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

int nextInt()
{
    char c = ' ';
    while(c == ' ' || c ==  '\n')
        c = getchar();
    int x = c - '0';
    while(true)
    {
        c = getchar();
        if (c == ' ' || c ==  '\n' || c == EOF)
            break;
        x = x * 10 + c - '0';
    }
    return x;
}

void printInt(int x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    bool okZero = false;
    for(int i = 1000000000; i; i /= 10)
    {
        int digit = x / i;
        x %= i;
        if (digit)
            okZero = true, putchar('0' + digit);
        else if (okZero)
            putchar('0');
    }
}

int n, logn, m, h[mn];
int p[mn][18], st[mn], ed[mn], rig = 0;
vector<int> g[mn];

void setup()
{
    n = nextInt(), m = nextInt();
    logn = log2(n);
    int u, v;
    FOR(i, 2, n)
    {
        u = nextInt(), v = nextInt();
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(int u)
{
    st[u] = ++ rig;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p[u][0])
            continue;
        p[v][0] = u;
        FOR(i, 1, logn)
            p[v][i] = p[p[v][i - 1]][i - 1];
        h[v] = h[u] + 1;
        dfs(v);
    }
    ed[u] = rig;
}

bool isChild(int u, int v)
{
    return st[v] <= st[u] && st[u] <= ed[v];
}

int lca(int u, int v)
{
    if (h[u] > h[v])
        swap(u, v);
    int dif = h[v] - h[u];
    FOR(i, 0, logn)
    if ((dif >> i) & 1)
        v = p[v][i];
    if (u == v)
        return u;
    FORD(i, logn, 0)
    if (p[u][i] != p[v][i])
    {
        u = p[u][i];
        v = p[v][i];
    }
    return p[u][0];
}

int query()
{
    int a = nextInt(), b = nextInt(), c = nextInt();
    int lbc = lca(b, c);
    if (!isChild(a, lbc))
        return lbc;
    int lab = lca(a, b);
    int lac = lca(a, c);
    return (h[lab] > h[lac]? lab : lac);
}

void xuly()
{
    dfs(1);
    while(m --)
        printInt(query()), putchar('\n');
}

int main()
{
    freopen("PEACE.INP", "r", stdin);
    freopen("PEACE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
