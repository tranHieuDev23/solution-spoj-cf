#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define pb push_back
#define mid ((l + r) >> 1)
#define lc (id << 1)
#define rc (lc + 1)

using namespace std;
int n, q, p[mn][18], pos[mn], fin[mn], rig = 0;
bool black[mn];
vector<int> g[mn];

struct intervalTree
{
    int tree[mn << 2];

    void push(int id)
    {
        tree[lc] += tree[id];
        tree[rc] += tree[id];
        tree[id] = 0;
    }

    void update(int l, int r, int id, int x, int y, int v)
    {
        if (l > y || r < x)
            return;
        if (x <= l && r <= y)
        {
            tree[id] += v;
            return;
        }
        push(id);
        update(l, mid, lc, x, y, v);
        update(mid + 1, r, rc, x, y, v);
    }

    int get(int l, int r, int id, int x)
    {
        if (l > x || r < x)
            return 0;
        if (l == r)
            return tree[id];
        push(id);
        int a = get(l, mid, lc, x);
        int b = get(mid + 1, r, rc, x);
        return a + b;
    }
} t;

void setup()
{
    cin >> n >> q;
    int u, v;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(int u)
{
    pos[u] = ++ rig;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p[u][0])
            continue;
        p[v][0] = u;
        FOR(i, 1, 17)
            p[v][i] = p[p[v][i - 1]][i - 1];
        dfs(v);
    }
    fin[u] = rig;
}

void querry1(int u)
{
    black[u] = !black[u];
    if (black[u])
        t.update(1, n, 1, pos[u], fin[u], 1);
    else
        t.update(1, n, 1, pos[u], fin[u], -1);
}

void querry2(int u)
{
    if (!t.get(1, n, 1, pos[u]))
    {
        cout << "-1\n";
        return;
    }
    FORD(i, 17, 0)
    {
        int pa = p[u][i];
        if (t.get(1, n, 1, pos[pa]))
            u = pa;
    }
    cout << u << '\n';
}

void xuly()
{
    dfs(1);
    int t, u;
    FOR(i, 1, q)
    {
        cin >> t >> u;
        if (t == 0)
            querry1(u);
        else
            querry2(u);
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
