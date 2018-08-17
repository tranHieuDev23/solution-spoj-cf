#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;

void getInt(int& x)
{
    char c = getchar();
    while(c == ' ' || c == '\n')
        c = getchar();
    x = c - '0';
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            break;
        x = x * 10 + c - '0';
    }
}

void printInt(int val)
{
    if (!val)
    {
        putchar('0');
        return;
    }
    bool okZero = false;
    for(int i = 100000; i; i /= 10)
    {
        int digit = val / i;
        val %= i;
        if (digit)
            okZero = true, putchar('0' + digit);
        else if (okZero)
            putchar('0');
    }
}

int n, k, siz[mn], spe[mn], meet[mn];
int deep[mn], ans[mn];
bool mark[mn];
vector<int> g[mn];

void setup()
{
    getInt(n), getInt(k);
    int v;
    FOR(u, 1, n)
    {
        getInt(meet[u]), getInt(v);
        if (v)
            g[u].pb(v), g[v].pb(u);
    }
    FOR(i, 1, k)
        deep[i] = - maxC;
}

void dfs(int u)
{
    mark[u] = true;
    siz[u] = 1, spe[u] = 0;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v])
            continue;
        dfs(v);
        if (siz[v] > siz[spe[u]])
            spe[u] = v;
        siz[u] += siz[v];
    }
    mark[u] = false;
}

void dfsSubtree(int u, int h)
{
    ans[meet[u]] = max(ans[meet[u]], h + deep[meet[u]]);
    mark[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v])
            continue;
        dfsSubtree(v, h + 1);
    }
    mark[u] = false;
}

void updateSubtree(int u, int h)
{
    deep[meet[u]] = max(deep[meet[u]], h);
    mark[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v])
            continue;
        updateSubtree(v, h + 1);
    }
    mark[u] = false;
}

void clean(int u)
{
    deep[meet[u]] = - maxC;
    mark[u] = true;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v])
            continue;
        clean(v);
    }
    mark[u] = false;
}

void solve(int u)
{
    dfs(u);
    int sizeTree = siz[u];
    while(siz[spe[u]] > (sizeTree >> 1))
        u = spe[u];

    mark[u] = true;
    deep[meet[u]] = 0;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v])
            continue;
        dfsSubtree(v, 1);
        updateSubtree(v, 1);
    }

    deep[meet[u]] = - maxC;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v])
            continue;
        clean(v);
    }

    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (mark[v])
            continue;
        solve(v);
    }
}

void xuly()
{
    solve(1);
    FOR(i, 1, k)
        printInt(ans[i]), putchar('\n');
}

int main()
{
    setup ();
    xuly ();
    return 0;
}
