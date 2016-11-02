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
int n, m, r, sz[mn], spe[mn], p[mn];
int beg[mn], belong[mn], pos[mn], num = 0, rig = 0, cur = 0;
vector<int> g[mn];
pair<int, int> co[mn];

struct interval
{
    int l, r, mark, val;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        mark = val = 0;
        if (l == r)
            lc = rc = NULL;
        else
        {
            lc = new interval(l, mid);
            rc = new interval(mid + 1, r);
        }
    }

    void push()
    {
        lc -> val += val;
        rc -> val += val;
        val = 0;
    }

    void update(int x, int y)
    {
        if (l > y || r < x || mark == cur)
            return;
        if (x <= l && r <= y)
        {
            mark = cur;
            val ++;
            return;
        }
        push();
        lc -> update(x, y);
        rc -> update(x, y);
    }

    int get(int x)
    {
        if (l == r)
            return val;
        push();
        if (x <= mid)
            return lc -> get(x);
        return rc -> get(x);
    }
} t;

void dfs(int u)
{
    sz[u] = 1, spe[u] = 0;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p[u])
            continue;
        p[v] = u;
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
    if (spe[u])
    {
        hld(spe[u]);
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (v == spe[u] || v == p[u])
                continue;
            beg[++ num] = -1;
            hld(v);
        }
    }
}

void update(int a)
{
    while(belong[a] != belong[r])
    {
        t.update(pos[beg[belong[a]]], pos[a]);
        a = p[beg[belong[a]]];
    }
    t.update(pos[r], pos[a]);
}

void setup()
{
    cin >> n >> m >> r;
    int u, v;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    FOR(i, 1, n)
        cin >> co[i].F, co[i].S = i;
    beg[num] = -1;
}

void xuly()
{
    dfs(r);
    hld(r);
    t = interval(1, n);
    sort(co + 1, co + n + 1);
    FOR(i, 1, n)
    {
        cur += (co[i].F != co[i - 1].F);
        update(co[i].S);
    }
    int u;
    FOR(i, 1, m)
    {
        cin >> u;
        cout << t.get(pos[u]) << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("COLTREE.INP", "r", stdin);
    freopen("COLTREE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
