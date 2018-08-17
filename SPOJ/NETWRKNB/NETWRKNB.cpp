#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)

using namespace std;
struct node
{
    int l, r, num;
    node* lc;
    node* rc;

    node(int l = 0, int r = 0, int num = 0): l(l), r(r), num(num)
    {
        lc = rc = NULL;
    }

    node* update(int x)
    {
        node* re = new node(l, r, num + 1);
        if (l == r)
            return re;
        if (x <= mid)
        {
            re -> lc = lc -> update(x);
            re -> rc = rc;
        }
        else
        {
            re -> lc = lc;
            re -> rc = rc -> update(x);
        }
        return re;
    }

    int get(int x, int y)
    {
        if (l > y || r < x)
            return 0;
        if (x <= l && r <= y)
            return num;
        return lc -> get(x, y) + rc -> get(x, y);
    }
};

node* build(int l, int r)
{
    node* re = new node(l, r);
    if (l == r)
        return re;
    re -> lc = build(l, mid);
    re -> rc = build(mid + 1, r);
    return re;
}

int n, m, logn, u[mn], v[mn], w[mn], sz[mn], spe[mn], p[mn][18], h[mn];
int beg[mn], belong[mn], pos[mn], fin[mn], num = 0, rig = 0;
vector< pair<int, int> > e;
vector<node*> root;
vector<int> g[mn];

void dfs(int u)
{
    sz[u] = 1, spe[u] = 0;
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
        sz[u] += sz[v];
        if (sz[v] > sz[spe[u]])
            spe[u] = v;
    }
}

void hld(int u)
{
    if (beg[num] == 0)
        beg[num] = u;
    belong[u] = num;
    pos[u] = ++ rig;
    if (spe[u])
    {
        hld(spe[u]);
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (v == p[u][0] || v == spe[u])
                continue;
            num ++;
            hld(v);
        }
    }
    fin[u] = rig;
}

void prepare()
{
    dfs(1);
    hld(1);
    root.pb(build(2, rig));
    sort(e.begin(), e.end());
    FOR(i, 0, n - 2)
    {
        int id = e[i].S;
        if (h[u[id]] < h[v[id]])
            u[id] = v[id];
        root.pb(root[i] -> update(pos[u[id]]));
    }
}

int properVer(int c)
{
    int l = -1, r = n - 1;
    while(r - l > 1)
    {
        if(e[mid].F <= c)
            l = mid;
        else
            r = mid;
    }
    return r;
}

int up(int u, int height)
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
    b = up(b, h[a]);
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

int get(int a, int b, int ver)
{
    int re = 0;
    while(belong[a] != belong[b])
    {
        re += root[ver] -> get(pos[beg[belong[a]]], pos[a]);
        a = p[beg[belong[a]]][0];
    }
    re += root[ver] -> get(pos[b], pos[a]);
    return re;
}

void query1()
{
    int a, b, c;
    cin >> a >> b >> c;
    int ver = properVer(c);
    int l = lca(a, b);
    int ans = 0;
    if (a != l)
        ans += get(a, up(a, h[l] + 1), ver);
    if (b != l)
        ans += get(b, up(b, h[l] + 1), ver);
    cout << ans << '\n';
}

void query2()
{
    int k, c;
    cin >> k >> c;
    int ver = properVer(c);
    int numLow = root[ver] -> get(pos[u[k]] + 1, fin[u[k]]);
    if (v[k] == u[k])
        cout << numLow << '\n';
    else
        cout << (root[ver] -> num - numLow - (w[k] <= c)) << '\n';
}

void setup()
{
    cin >> n >> m;
    logn = log2(n);
    FOR(i, 1, n - 1)
    {
        cin >> u[i] >> v[i] >> w[i];
        g[u[i]].pb(v[i]);
        g[v[i]].pb(u[i]);
        e.pb(mp(w[i], i));
    }
}

void xuly()
{
    prepare();
    char c;
    FOR(i, 1, m)
    {
        cin >> c;
        if (c == 'P')
            query1();
        else
            query2();
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
