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
int n, m, a[mn];

void add(long long& a, long long b)
{
    a = (a + b) % maxC;
}

void mul(long long& a, long long b)
{
    a = (a * b) % maxC;
}

struct interval
{
    int l, r;
    long long ad, ml;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        ml = 1;
        if (l == r)
        {
            ad = a[l];
            lc = rc = NULL;
            return;
        }
        ad = 0;
        lc = new interval(l, mid);
        rc = new interval(mid + 1, r);
    }

    void push()
    {
        if (l == r)
            return;
        mul(lc -> ml, ml);
        mul(lc -> ad, ml);
        add(lc -> ad, ad);
        mul(rc -> ml, ml);
        mul(rc -> ad, ml);
        add(rc -> ad, ad);
        ad = 0, ml = 1;
    }

    void updateAdd(int x, int y, long long v)
    {
        if (l > y || r < x)
            return;
        push();
        if (x <= l && r <= y)
        {
            add(ad, v);
            return;
        }
        lc -> updateAdd(x, y, v);
        rc -> updateAdd(x, y, v);
    }

    void updateMul(int x, int y, long long v)
    {
        if (l > y || r < x)
            return;
        push();
        if (x <= l && r <= y)
        {
            mul(ad, v);
            mul(ml, v);
            return;
        }
        lc -> updateMul(x, y, v);
        rc -> updateMul(x, y, v);
    }

    long long get(int x)
    {
        if (l == r)
            return ad;
        push();
        if (x <= mid)
            return lc -> get(x);
        return rc -> get(x);
    }
} t;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    cin >> m;
    t = interval(1, n);
}

void xuly()
{
    char o;
    int x, y, v;
    FOR(i, 1, m)
    {
        cin >> o;
        if (o == '?')
        {
            cin >> x;
            cout << t.get(x) << '\n';
        }
        else
        {
            cin >> x >> y >> v;
            if (o == '+')
                t.updateAdd(x, y, v);
            else
                t.updateMul(x, y, v);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("ARITHMETIC.INP", "r", stdin);
    freopen("ARITHMETIC.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
