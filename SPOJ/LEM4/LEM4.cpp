#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define mid ((l + r) >> 1)

using namespace std;
struct node
{
    int sz, best, lef, rig;

    node(int sz = 0, int co = 1): sz(sz)
    {
        best = lef = rig = sz * co;
    }

    node(node a, node b)
    {
        sz = a.sz + b.sz;
        if (a.lef == a.sz)
            lef = a.lef + b.lef;
        else
            lef = a.lef;
        if (b.rig == b.sz)
            rig = a.rig + b.rig;
        else
            rig = b.rig;
        best = max(max(a.best, b.best), a.rig + b.lef);
    }
};

struct interval
{
    int l, r, f;
    node val;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        f = -1;
        val = node(r - l + 1);
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
        if (f == -1)
            return;
        lc -> val = node(lc -> val.sz, f);
        rc -> val = node(rc -> val.sz, f);
        lc -> f = rc -> f = f;
        f = -1;
    }

    void update(int x, int y, int v)
    {
        if (l > y || r < x)
            return;
        if (x <= l && r <= y)
        {
            val = node(val.sz, v);
            f = v;
            return;
        }
        push();
        lc -> update(x, y, v);
        rc -> update(x, y, v);
        val = node(lc -> val, rc -> val);
    }
} t;

int n, m;

void setup()
{
    cin >> n >> m;
    t = interval(1, n);
    int type, l, r;
    FOR(i, 1, m)
    {
        cin >> type;
        if (type < 3)
        {
            cin >> l >> r;
            t.update(l, r, (type == 1));
        }
        else
            cout << t.val.best << '\n';
    }
}

void xuly()
{

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
