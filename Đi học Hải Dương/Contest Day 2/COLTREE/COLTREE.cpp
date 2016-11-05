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
int n, m, root, cur[mn], pos[mn], fin[mn], rig, co[mn], ans[mn];
int num[mn], st[mn], r = 0, las[mn], nex[mn], con[mn];
map<int, int> Map;
vector<int> g[mn];

struct query
{
    int l, r, id;

    query(int l = 0, int r = 0, int id = 0): l(l), r(r), id(id) {};

} q[mn];

bool com(query& a, query& b)
{
    if (a.l != b.l)
        return a.l < b.l;
    return a.r < b.r;
}

struct bitTree
{
    int tree[mn];

    void update(int x, int v)
    {
        for(; x <= n; x += (x & (-x)))
            tree[x] += v;
    }

    int get(int x)
    {
        int re = 0;
        for(; x; x -= (x & (-x)))
            re += tree[x];
        return re;
    }
} t;

void dfs()
{
    pos[root] = rig = 1;
    con[rig] = root;
    st[++ r] = root;
    while(r)
    {
        int u = st[r];
        while(cur[u] < int(g[u].size()) && pos[g[u][cur[u]]])
            cur[u] ++;
        if (cur[u] == int(g[u].size()))
        {
            fin[u] = rig;
            r --;
            continue;
        }
        int v = g[u][cur[u]];
        pos[v] = ++ rig;
        con[rig] = v;
        st[++ r] = v;
    }
}

void setup()
{
    scanf("%d%d%d", &n, &m, &root);
    int u, v;
    FOR(i, 2, n)
    {
        scanf("%d%d", &u, &v);
        g[u].pb(v);
        g[v].pb(u);
    }
    FOR(i, 1, n)
    {
        scanf("%d", &co[i]);
        if (!Map[co[i]])
            Map[co[i]] = ++ rig;
        co[i] = Map[co[i]];
    }
}

void xuly()
{
    dfs();
    int u;
    FOR(i, 1, m)
    {
        scanf("%d", &u);
        q[i] = query(pos[u], fin[u], i);
    }
    sort(q + 1, q + m + 1, com);
    FOR(i, 1, n)
    {
        int u = con[i];
        if (las[co[u]])
            nex[las[co[u]]] = i;
        else
            t.update(i, 1);
        las[co[u]] = i;
        nex[i] = n + 1;
    }
    int lef = 1;
    FOR(i, 1, m)
    {
        while(lef < q[i].l)
        {
            t.update(lef, -1);
            t.update(nex[lef], 1);
            lef ++;
        }
        ans[q[i].id] = t.get(q[i].r);
    }
    FOR(i, 1, m)
        printf("%d\n", ans[i]);
}

int main()
{
    freopen("COLTREE.INP", "r", stdin);
    freopen("COLTREE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
