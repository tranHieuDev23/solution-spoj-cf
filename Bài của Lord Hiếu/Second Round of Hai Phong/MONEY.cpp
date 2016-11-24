#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 40004
#define maxC 100000007
#define g ((l + r) >> 1)
#define lc (id << 1)
#define rc (lc + 1)

using namespace std;
int n, d;
long long m[mn], ans = 0;

struct node
{
    int sz;
    long long both, lef, rig, mid;

    node(long long val = 0): both(val)
    {
        sz = 1;
        lef = rig = mid = 0;
    }

    node(node& a, node& b)
    {
        sz = a.sz + b.sz;
        if (sz == 2)
            both = 0;
        else
            both = max(a.lef + b.rig, max(a.both + b.rig, a.lef + b.both));
        lef = max(a.both + b.mid, max(a.lef + b.lef, a.lef + b.mid));
        rig = max(a.mid + b.both, max(a.rig + b.rig, a.mid + b.rig));
        mid = max(a.mid + b.mid, max(a.mid + b.lef, a.rig + b.mid));
    }
};

struct interval
{
    node tree[mn << 2];

    void build(int l, int r, int id)
    {
        if (l == r)
        {
            tree[id] = node(m[l]);
            return;
        }
        build(l, g, lc);
        build(g + 1, r, rc);
        tree[id] = node(tree[lc], tree[rc]);
    }

    void update(int l, int r, int id, int x, int v)
    {
        if (l > x || r < x)
            return;
        if (l == r)
        {
            m[l] = v;
            tree[id] = node(m[l]);
            return;
        }
        update(l, g, lc, x, v);
        update(g + 1, r, rc, x, v);
        tree[id] = node(tree[lc], tree[rc]);
    }
} t;

void setup()
{
    cin >> n >> d;
    FOR(i, 1, n)
        cin >> m[i];
    t.build(1, n, 1);
    int x, v;
    FOR(i, 1, d)
    {
        cin >> x >> v;
        t.update(1, n, 1, x, v);
        ans += max(max(t.tree[1].both, t.tree[1].lef), max(t.tree[1].rig, t.tree[1].mid));
    }
    cout << ans;
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MONEY.INP", "r", stdin);
    freopen("MONEY.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
