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
int n, a[mn], r = 0;
pair<int, int> p[mn];

struct interval
{
    int l, r, best;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        best = 0;
        if (l == r)
            lc = rc = NULL;
        else
        {
            lc = new interval(l, mid);
            rc = new interval(mid + 1, r);
        }
    }

    void update(int x, int v)
    {
        if (l > x || r < x)
            return;
        if (l == r)
        {
            best = v;
            return;
        }
        lc -> update(x, v);
        rc -> update(x, v);
        best = max(lc -> best, rc -> best);
    }

    int getBest(int x, int y)
    {
        if (l > y || r < x)
            return 0;
        if (x <= l && r <= y)
            return best;
        return max(lc -> getBest(x, y), rc -> getBest(x, y));
    }
} t1, t2;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> p[i].F, p[i].S = i;
    sort(p + 1, p + n + 1);
    FOR(i, 1, n)
    {
        r += (p[i].F != p[i - 1].F);
        a[p[i].S] = r;
    }
}

void xuly()
{
    int ans = 0;
    t1 = interval(1, r);
    t2 = interval(1, r);
    FORD(i, n, 1)
    {
        int lis = t1.getBest(a[i] + 1, r) + 1;
        int lds = t2.getBest(1, a[i] - 1) + 1;
        ans = max(ans, lis + lds - 1);
        t1.update(a[i], lis);
        t2.update(a[i], lds);
    }
    cout << ans;
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
