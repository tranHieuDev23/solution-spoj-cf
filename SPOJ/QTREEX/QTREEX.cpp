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
int n, logn, w[mn], sz[mn], spe[mn], p[mn][15], h[mn], conV[mn];
int con[mn], up[mn], beg[mn], belong[mn], pos[mn], num, rig;
vector< pair<int, int> > g[mn];
string s;

struct interval
{
    int Min[mn << 2], Max[mn << 2];
    bool f[mn << 2];

    void better(int id)
    {
        Min[id] = min(Min[lc], Min[rc]);
        Max[id] = max(Max[lc], Max[rc]);
    }

    void rev(int id)
    {
        swap(Min[id], Max[id]);
        Min[id] *= -1, Max[id] *= -1;
    }

    void build(int l, int r, int id)
    {
        f[id] = false;
        if (l == r)
        {
            Min[id] = Max[id] = up[conV[l]];
            return;
        }
        build(l, mid, lc);
        build(mid + 1, r, rc);
        better(id);
    }

    void push(int id)
    {
        if (!f[id])
            return;
        rev(lc), rev(rc);
        f[lc] = !f[lc];
        f[rc] = !f[rc];
        f[id] = false;
    }

    void change(int l, int r, int id, int x, int val)
    {
        if (l > x || r < x)
            return;
        if (l == r)
        {
            Min[id] = Max[id] = val;
            return;
        }
        push(id);
        change(l, mid, lc, x, val);
        change(mid + 1, r, rc, x, val);
        better(id);
    }

    void negat(int l, int r, int id, int x, int y)
    {
        if (l > y || r < x)
            return;
        if (x <= l && r <= y)
        {
            rev(id);
            f[id] = !f[id];
            return;
        }
        push(id);
        negat(l, mid, lc, x, y);
        negat(mid + 1, r, rc, x, y);
        better(id);
    }

    int getMax(int l, int r, int id, int x, int y)
    {
        if (l > y || r < x)
            return - maxC;
        if (x <= l && r <= y)
            return Max[id];
        push(id);
        int a = getMax(l, mid, lc, x, y);
        int b = getMax(mid + 1, r, rc, x, y);
        return max(a, b);
    }
} t;

void dfs(int u)
{
    sz[u] = 1, spe[u] = 0;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (v == p[u][0])
            continue;
        p[v][0] = u;
        FOR(j, 1, logn)
            p[v][j] = p[p[v][j - 1]][j - 1];
        h[v] = h[u] + 1;
        int id = g[u][i].S;
        con[id] = v;
        up[v] = w[id];
        dfs(v);
        if (sz[v] > sz[spe[u]])
            spe[u] = v;
        sz[u] += sz[v];
    }
}

void hld(int u)
{
    if (beg[num] == -1)
        beg[num] = u;
    belong[u] = num;
    pos[u] = ++ rig;
    conV[rig] = u;
    if (spe[u])
    {
        hld(spe[u]);
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            if (v == p[u][0] || v == spe[u])
                continue;
            beg[++ num] = -1;
            hld(v);
        }
    }
}

void update(int a, int b)
{
    while(belong[a] != belong[b])
    {
        t.negat(2, rig, 1, pos[beg[belong[a]]], pos[a]);
        a = p[beg[belong[a]]][0];
    }
    t.negat(2, rig, 1, pos[b], pos[a]);
}

int get(int a, int b)
{
    int re = -maxC;
    while(belong[a] != belong[b])
    {
        re = max(re, t.getMax(2, rig, 1, pos[beg[belong[a]]], pos[a]));
        a = p[beg[belong[a]]][0];
    }
    re = max(re, t.getMax(2, rig, 1, pos[b], pos[a]));
    return re;
}

void setup()
{
    cin >> n;
    logn = log2(n);
    FOR(i, 1, n)
        g[i].clear();
    int u, v;
    FOR(i, 1, n - 1)
    {
        cin >> u >> v >> w[i];
        g[u].pb(mp(v, i));
        g[v].pb(mp(u, i));
    }
}

int Up(int u, int height)
{
    int dif = h[u] - height;
    FOR(i, 0, logn)
    if ((dif >> i) & 1)
        u = p[u][i];
    return u;
}

int lca(int a, int b)
{
    if (h[a] > h[b])
        swap(a, b);
    b = Up(b, h[a]);
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

void querryC()
{
    int id, v; cin >> id >> v;
    t.change(2, rig, 1, pos[con[id]], v);
}

void querryN()
{
    int a, b; cin >> a >> b;
    int l = lca(a, b);
    if (a != l)
        update(a, Up(a, h[l] + 1));
    if (b != l)
        update(b, Up(b, h[l] + 1));
}

void querryQ()
{
    int a, b; cin >> a >> b;
    if (a == b)
    {
        cout << "0\n";
        return;
    }
    int l = lca(a, b);
    int ans = - maxC;
    if (a != l)
        ans = max(ans, get(a, Up(a, h[l] + 1)));
    if (b != l)
        ans = max(ans, get(b, Up(b, h[l] + 1)));
    cout << ans << '\n';
}

void xuly()
{
    beg[num = rig = 0] = -1;
    dfs(1);
    hld(1);
    t.build(2, rig, 1);
    while(cin >> s)
    {
        if (s[0] == 'D')
            return;
        if (s[0] == 'C')
            querryC();
        if (s[0] == 'N')
            querryN();
        if (s[0] == 'Q')
            querryQ();
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
