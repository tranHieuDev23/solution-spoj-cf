#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define maxC 1000000007
#define base1 3
#define base2 5
#define mid ((l + r) >> 1)

using namespace std;
string s;
unsigned long long po1[mn], po2[mn];
int n;

struct node
{
    int sz;
    unsigned long long hashVal1, hashVal2;

    node(int sz = 0, int v = 0): sz(sz)
    {
        hashVal1 = hashVal2 = v;
    }

    node(node const& a, node const& b)
    {
        sz = a.sz + b.sz;
        hashVal1 = a.hashVal1 * po1[b.sz] + b.hashVal1;
        hashVal2 = a.hashVal2 * po2[b.sz] + b.hashVal2;
    }

    bool operator == (node const& x)
    {
        if (sz != x.sz)
            return false;
        if (hashVal1 != x.hashVal1)
            return false;
        if (hashVal2 != x.hashVal2)
            return false;
        return true;
    }
};

struct interval
{
    int l, r;
    node val;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        if (l == r)
        {
            val = node(1, s[l - 1] - '0');
            lc = rc = NULL;
            return;
        }
        lc = new interval(l, mid);
        rc = new interval(mid + 1, r);
        val = node(lc -> val, rc -> val);
    }

    void update(int x)
    {
        if (l == r)
        {
            val = node();
            return;
        }
        if (x <= mid)
            lc -> update(x);
        else
            rc -> update(x);
        val = node(lc -> val, rc -> val);
    }

    int findPos(int x)
    {
        if (l == r)
            return l;
        if (lc -> val.sz >= x)
            return lc -> findPos(x);
        return rc -> findPos(x - lc -> val.sz);
    }

    node getHash(int x, int y)
    {
        if (l > y || r < x)
            return node();
        if (x <= l && r <= y)
            return val;
        node a = lc -> getHash(x, y);
        node b = rc -> getHash(x, y);
        return node(a, b);
    }
} t;

void setup()
{
    cin >> s >> n;
    po1[0] = po2[0] = 1;
    FOR(i, 1, int(s.size()))
        po1[i] = po1[i - 1] * base1, po2[i] = po2[i - 1] * base2;
    t = interval(1, s.size());
}

void xuly()
{
    char type;
    int u, v, m;
    while(n --)
    {
        cin >> type;
        if (type == '-')
        {
            cin >> u;
            u = t.findPos(u);
            t.update(u);
        }
        else
        {
            cin >> u >> v >> m;
            int X1 = t.findPos(u), Y1 = t.findPos(u + m - 1);
            int X2 = t.findPos(v), Y2 = t.findPos(v + m - 1);
            node a = t.getHash(X1, Y1);
            node b = t.getHash(X2, Y2);
            cout << (a == b? "YES\n" : "NO\n");
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("COMP_STR.INP", "r", stdin);
    freopen("COMP_STR.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
