#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define maxC 1000000007000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)

using namespace std;
int n, m, logn, h[mn], p[mn][19], sz[mn], spe[mn], beg[mn];
int belong[mn], pos[mn], num = 0, rig = 0;
long long ans[mn];
pair< long long, pair<int, int> > query[mn];
vector<int> g[mn];

struct interval
{
    int l, r, fId;
    long long highBv, fStart;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        fId = fStart = -1;
        highBv = (l == 1? maxC : -1);
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
        if (fId == -1)
            return;
        lc -> highBv = fStart + ((lc -> r - fId) << 1);
        rc -> highBv = fStart + ((rc -> r - fId) << 1);
        lc -> fStart = rc -> fStart = fStart;
        lc -> fId = rc -> fId = fId;
        fId = -1;
    }

    void update(int x, int y, long long start)
    {
        if (l > y || r < x)
            return;
        if (x <= l && r <= y)
        {
            highBv = start + ((r - x) << 1);
            fId = x, fStart = start;
            return;
        }
        push();
        lc -> update(x, y, start);
        rc -> update(x, y, start);
        highBv = max(lc -> highBv, rc -> highBv);
    }

    long long getHigh(int x, int y)
    {
        if (l > y || r < x)
            return -1;
        if (x <= l && r <= y)
            return highBv;
        push();
        return max(lc -> getHigh(x, y), rc -> getHigh(x, y));
    }
} t;

void rmq()
{
    FOR(j, 1, logn)
    FOR(i, 1, n)
        p[i][j] = p[p[i][j - 1]][j - 1];
}

void dfs(int u)
{
    sz[u] = 1, spe[u] = n + 1;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        h[v] = h[u] + 1;
        dfs(v);
        sz[u] += sz[v];
        if (sz[v] > sz[spe[u]])
            spe[u] = v;
    }
}

void hld(int u)
{
    if (beg[num] == -1)
        beg[num] = u;
    belong[u] = num;
    pos[u] = ++ rig;
    if (spe[u] != n + 1)
        hld(spe[u]);
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == spe[u])
            continue;
        beg[++ num] = -1;
        hld(v);
    }
}

int getStop(int v, long long val)
{
    int re = 0;
    while(v)
    {
        int u = beg[belong[v]];
        if (t.getHigh(pos[u], pos[v]) <= val)
        {
            v = p[u][0];
            continue;
        }
        if (t.getHigh(pos[v], pos[v]) > val)
            return v;
        int dif = h[v] - h[u];
        FORD(i, logn, 0)
        if ((1 << i) <= dif)
        {
            if (t.getHigh(pos[p[v][i]], pos[v]) <= val)
                v = p[v][i];
        }
        re = p[v][0];
        break;
    }
    return re;
}

void update(int a, int b, long long bVal)
{
    while(belong[a] != belong[b])
    {
        int u = beg[belong[a]];
        int posU = h[u] - h[b];
        t.update(pos[u], pos[a], bVal + (posU << 1));
        a = p[u][0];
    }
    t.update(pos[b], pos[a], bVal);
}

void setup()
{
    cin >> n >> m;
    logn = log2(n);
    FOR(i, 1, n)
    {
        cin >> p[i][0];
        g[p[i][0]].pb(i);
    }
    FOR(i, 1, m)
        cin >> query[i].S.F >> query[i].F, query[i].S.S = i;
}

int up(int u, int height)
{
    int dif = h[u] - height;
    FOR(i, 0, logn)
    if ((dif >> i) & 1)
        u = p[u][i];
    return u;
}

void deal(int id)
{
    int u = query[id].S.F;
    long long val = query[id].F;
    long long start = val - h[u];
    int v = getStop(u, val);
    int dis = h[u] - h[v];
    ans[query[id].S.S] = start + dis * 2;
    if (u == v)
        return;
    int z = up(u, h[v] + 1);
    update(u, z, h[z] + start + dis + 1);
}

void xuly()
{
    rmq();
    dfs(0);
    beg[num] = -1;
    hld(0);
    t = interval(1, rig);
    FOR(i, 1, m)
        query[i].F += h[query[i].S.F];
    sort(query + 1, query + m + 1);
    FOR(i, 1, m)
        deal(i);
    FOR(i, 1, m)
        cout << ans[i] << ' ';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("FILE.INP", "r", stdin);
    freopen("FILE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
