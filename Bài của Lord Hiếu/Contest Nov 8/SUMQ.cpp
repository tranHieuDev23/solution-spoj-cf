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
struct interval
{
    int l, r, sum;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        if (l == r)
        {
            sum = a[l];
            lc = rc = NULL;
            return;
        }
        lc = new interval(l, mid);
        rc = new interval(mid + 1, r);
        sum = lc -> sum + rc -> sum;
    }

    void update(int x, int v)
    {
        if (l == r)
        {
            sum -= v;
            return;
        }
        if (x <= mid)
            lc -> update(x, v);
        else
            rc -> update(x, v);
        sum = lc -> sum + rc -> sum;
    }

    int getSum(int x, int y)
    {
        if (l > y || r < x)
            return 0;
        if (x <= l && r <= y)
            return sum;
        int a = lc -> getSum(x, y);
        int b = rc -> getSum(x, y);
        return a + b;
    }
} t;

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
        cin >> a[i];
    t = interval(1, n);
}

void xuly()
{
    int type, u, v;
    FOR(i, 1, m)
    {
        cin >> type >> u >> v;
        if (type == 0)
            t.update(u, v);
        else
            cout << t.getSum(u, v) << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SUMQ.INP", "r", stdin);
    freopen("SUMQ.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
