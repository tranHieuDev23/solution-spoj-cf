#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 500005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)
#define multi(a, b) ((1ll * (a) * (b)) % maxC)

using namespace std;
int n, m, x[mn], y[mn];

struct interval
{
    int l, r, nonOne, mulX;
    pair<int, int> bestY;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        if (l == r)
        {
            bestY = mp(y[l], l);
            nonOne = (x[l] != 1 || l == 1);
            mulX = x[l];
            lc = rc = NULL;
            return;
        }
        lc = new interval(l, mid);
        rc = new interval(mid + 1, r);
        bestY = max(lc -> bestY, rc -> bestY);
        nonOne = lc -> nonOne + rc -> nonOne;
        mulX = multi(lc -> mulX, rc -> mulX);
    }

    void updateY(int x, int val)
    {
        if (l > x || r < x)
            return;
        if (l == r)
        {
            y[l] = bestY.F = val;
            return;
        }
        lc -> updateY(x, val);
        rc -> updateY(x, val);
        bestY = max(lc -> bestY, rc -> bestY);
    }

    void updateX(int pos, int val)
    {
        if (l > pos || r < pos)
            return;
        if (l == r)
        {
            x[l] = mulX = val;
            nonOne = (val != 1 || l == 1);
            return;
        }
        lc -> updateX(pos, val);
        rc -> updateX(pos, val);
        nonOne = lc -> nonOne + rc -> nonOne;
        mulX = multi(lc -> mulX, rc -> mulX);
    }

    pair<int, int> getBestY(int x, int y)
    {
        if (l > y || r < x)
            return mp(-maxC, -maxC);
        if (x <= l && r <= y)
            return bestY;
        return max(lc -> getBestY(x, y), rc -> getBestY(x, y));
    }

    int getMulX(int x, int y)
    {
        if (l > y || r < x)
            return 1;
        if (x <= l && r <= y)
            return mulX;
        return multi(lc -> getMulX(x, y), rc -> getMulX(x, y));
    }

    int findNonOne(int num)
    {
        if (l == r)
            return l;
        if (rc -> nonOne >= num)
            return rc -> findNonOne(num);
        return lc -> findNonOne(num - rc -> nonOne);
    }
} t;

void findBest()
{
    int pos = 1;
    int top = t.findNonOne(1);
    pair<int, int> p = t.getBestY(top, n);
    long long cur = p.F;
    int sellPoint = p.S;
    while(top != 1)
    {
        cur *= x[top];
        if (cur >= maxC)
            break;
        int nex = t.findNonOne(++ pos);
        p = t.getBestY(nex, top - 1);
        if (p.F > cur)
        {
            cur = p.F;
            sellPoint = p.S;
        }
        top = nex;
    }
    cout << multi(t.getMulX(1, sellPoint), y[sellPoint]) << '\n';
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> x[i];
    FOR(i, 1, n)
        cin >> y[i];
    cin >> m;
    t = interval(1, n);
}

void xuly()
{
    int type, pos, val;
    findBest();
    FOR(i, 1, m)
    {
        cin >> type >> pos >> val;
        pos ++;
        if (type == 1)
            t.updateX(pos, val);
        else
            t.updateY(pos, val);
        findBest();
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
