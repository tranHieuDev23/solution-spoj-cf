#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 10004
#define maxC 1000000007
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define mid ((l + r) >> 1)
#define lc (id << 1)
#define rc (lc + 1)

using namespace std;
int n, u[mn], v[mn], p[mn][15], h[mn], beg[mn], belong[mn];
int num, rig, up[mn], pos[mn], sz[mn], spe[mn], speE[mn];
vector< pair<int, int> > g[mn];
string s;

struct intervalTree
{
    int tree[mn << 2];

    void build(int l, int r, int id)
    {
        if (l == r)
        {
            tree[id] = up[l];
            return;
        }
        build(l, mid, lc);
        build(mid + 1, r, rc);
        tree[id] = max(tree[lc], tree[rc]);
    }

    void update(int l, int r, int id, int x, int v)
    {
        if (l > x || r < x)
            return;
        if (l == r)
        {
            tree[id] = v;
            return;
        }
        update(l, mid, lc, x, v);
        update(mid + 1, r, rc, x, v);
        tree[id] = max(tree[lc], tree[rc]);
    }

    int get(int l, int r, int id, int x, int y)
    {
        if (l > y || r < x)
            return -maxC;
        if (x <= l && r <= y)
            return tree[id];
        int a = get(l, mid, lc, x, y);
        int b = get(mid + 1, r, rc, x, y);
        return max(a, b);
    }
} t;

void dfs(int u)
{
    sz[u] = 1, spe[u] = 0, speE[u] = -maxC;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (v == p[u][0])
            continue;
        p[v][0] = u;
        FOR(j, 1, 14)
            p[v][j] = p[p[v][j - 1]][j - 1];
        h[v] = h[u] + 1;
        dfs(v);
        if (sz[v] > sz[spe[u]])
            spe[u] = v, speE[u] = g[u][i].S;
        sz[u] += sz[v];
    }
}

void hld(int u)
{
    if (!beg[num])
        beg[num] = u;
    belong[u] = num;
    pos[u] = ++ rig;
    if (spe[u])
    {
        hld(spe[u]);
        up[pos[spe[u]]] = speE[u];
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            if (v == p[u][0] || v == spe[u])
                continue;
            beg[++ num] = 0;
            hld(v);
            up[pos[v]] = g[u][i].S;
        }
    }
}

void querry1()
{
    int id, w;
    cin >> id >> w;
    int vert = (h[u[id]] > h[v[id]]? u[id] : v[id]);
    t.update(2, n, 1, pos[vert], w);
}

int goUp(int u, int height)
{
    int dif = h[u] - height;
    FOR(i, 0, 14)
    if ((dif >> i) & 1)
        u = p[u][i];
    return u;
}

int lca(int a, int b)
{
    if (h[a] > h[b])
        swap(a, b);
    b = goUp(b, h[a]);
    if (a == b)
        return a;
    FORD(i, 14, 0)
    if (p[a][i] != p[b][i])
    {
        a = p[a][i];
        b = p[b][i];
    }
    return p[a][0];
}

int get(int a, int b)
{
    int re = - maxC;
    while(belong[a] != belong[b])
    {
        re = max(re, t.get(2, n, 1, pos[beg[belong[a]]], pos[a]));
        a = p[beg[belong[a]]][0];
    }
    return max(re, t.get(2, n, 1, pos[b], pos[a]));
}

void querry2()
{
    int a, b; cin >> a >> b;
    int l = lca(a, b);
    int ans = -maxC;
    if (h[a] > h[l])
        ans = max(ans, get(a, goUp(a, h[l] + 1)));
    if (h[b] > h[l])
        ans = max(ans, get(b, goUp(b, h[l] + 1)));
    cout << ans << '\n';
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        g[i].clear();
    int c;
    FOR(i, 1, n - 1)
    {
        cin >> u[i] >> v[i] >> c;
        g[u[i]].pb(mp(v[i], c));
        g[v[i]].pb(mp(u[i], c));
    }
    beg[num = rig = 0] = 0;
}

void xuly()
{
    dfs(1);
    hld(1);
    t.build(2, n, 1);
    while(cin >> s)
    {
        if (s[0] == 'D')
            return;
        if (s[0] == 'C')
            querry1();
        else
            querry2();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    FOR(i, 1, t)
    {
        setup ();
        xuly ();
    }
    return 0;
}
