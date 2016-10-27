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
struct line
{
    long long a, b;

    line(long long a = 0, long long b = 0): a(a), b(b){}

    long long val(long long x) {return a * x + b;}
};

struct interval
{
    int l, r;
    line cur;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        cur = line();
        if (l == r)
            lc = rc = NULL;
        else
        {
            lc = new interval(l, mid);
            rc = new interval(mid + 1, r);
        }
    }

    void update(int x, int y, line val)
    {
        if (l > y || r < x)
            return;
        if (x <= l && r <= y)
        {
            long long lCur = cur.val(l);
            long long rCur = cur.val(r);
            long long lVal = val.val(l);
            long long rVal = val.val(r);
            if (lCur >= lVal && rCur >= rVal)
                return;
            if (lCur <= lVal && rCur <= rVal)
            {
                cur = val;
                return;
            }
            long long gCur = cur.val(mid);
            long long gVal = val.val(mid);
            if (lCur >= lVal && gCur >= gVal)
            {
                rc -> update(x, y, val);
                return;
            }
            if (lCur <= lVal && gCur <= gVal)
            {
                rc -> update(x, y, cur);
                cur = val;
                return;
            }
            if (gCur >= gVal && rCur >= rVal)
            {
                lc -> update(x, y, val);
                return;
            }
            if (gCur <= gVal && rCur <= rVal)
            {
                lc -> update(x, y, cur);
                cur = val;
                return;
            }
        }
        lc -> update(x, y, val);
        rc -> update(x, y, val);
    }

    long long getMax(int x)
    {
        if (l > x || r < x)
            return 0;
        long long re = cur.val(x);
        if (l == r)
            return re;
        re = max(re, lc -> getMax(x));
        re = max(re, rc -> getMax(x));
        return re;
    }
} t;
int n, m;

void setup()
{
    cin >> n >> m;
    t = interval(1, n);
    long long s, e, v, d;
    FOR(i, 1, m)
    {
        cin >> s >> e >> v >> d;
        t.update(s, e, line(d, v - s * d));
    }
    FOR(i, 1, n)
        cout << t.getMax(i) << '\n';
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
