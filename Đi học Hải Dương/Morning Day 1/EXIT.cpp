#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define mid ((l + r) >> 1)

using namespace std;
int h, q;
long long begi, last;

struct interval
{
    long long l, r, num;
    interval* lc;
    interval* rc;

    interval(long long l = 0, long long r = 0): l(l), r(r)
    {
        num = r - l + 1;
        lc = rc = NULL;
    }

    void makeSure()
    {
        if (lc != NULL)
            return;
        lc = new interval(l, mid);
        rc = new interval(mid + 1, r);
    }

    void update(long long x, long long y)
    {
        if (l > y || r < x || num == 0)
            return;
        if (x <= l && r <= y)
        {
            num = 0;
            return;
        }
        makeSure();
        lc -> update(x, y);
        rc -> update(x, y);
        num = lc -> num + rc -> num;
    }

    long long get()
    {
        if (l == r)
            return l;
        makeSure();
        if (lc -> num)
            return lc -> get();
        return rc -> get();
    }
} t;

void setup()
{
    cin >> h >> q;
    begi = 1ll << (h - 1);
    last = (1ll << h) - 1;
    t = interval(begi, last);
    int curH, ans;
    long long l, r;
    FOR(i, 1, q)
    {
        cin >> curH >> l >> r >> ans;
        FOR(j, curH + 1, h)
            l = (l << 1), r = (r << 1) + 1;
        if (ans)
        {
            t.update(begi, l - 1);
            t.update(r + 1, last);
        }
        else
            t.update(l, r);
    }
    if (t.num == 0)
        cout << "NO";
    if (t.num > 1)
        cout << "MULTI";
    if (t.num == 1)
        cout << t.get();
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("EXIT.INP", "r", stdin);
    freopen("EXIT.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
