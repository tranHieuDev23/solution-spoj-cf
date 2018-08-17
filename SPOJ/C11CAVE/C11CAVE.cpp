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
int n, h;

struct interval
{
    int l, r, f;
    pair<int, int> best;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        best = mp(0, r - l + 1);
        f = 0;
        if (l == r)
        {
            lc = rc = NULL;
            return;
        }
        lc = new interval(l, mid);
        rc = new interval(mid + 1, r);
    }

    void push()
    {
        lc -> best.F += f;
        rc -> best.F += f;
        lc -> f += f;
        rc -> f += f;
        f = 0;
    }

    void update(int x, int y)
    {
        if (l > y || r < x)
            return;
        if (x <= l && r <= y)
        {
            best.F ++;
            f ++;
            return;
        }
        push();
        lc -> update(x, y);
        rc -> update(x, y);
        if (lc -> best.F == rc -> best.F)
            best = mp(lc -> best.F, lc -> best.S + rc -> best.S);
        else
            best = min(lc -> best, rc -> best);
    }
} t;

void setup()
{
    cin >> n >> h;
    t = interval(1, h);
    int x;
    FOR(i, 1, n)
    {
        cin >> x;
        if (i & 1)
            t.update(1, x);
        else
            t.update(h - x + 1, h);
    }
    cout << t.best.F << ' ' << t.best.S;
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
