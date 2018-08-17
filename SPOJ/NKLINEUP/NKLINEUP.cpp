#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 50004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)

using namespace std;
int n, q, h[mn];

struct interval
{
    int l, r, hig, low;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        if (l == r)
        {
            hig = low = h[l];
            lc = rc = NULL;
            return;
        }
        lc = new interval(l, mid);
        rc = new interval(mid + 1, r);
        hig = max(lc -> hig, rc -> hig);
        low = min(lc -> low, rc -> low);
    }

    int getHigh(int x, int y)
    {
        if (l > y || r < x)
            return - maxC;
        if (x <= l && r <= y)
            return hig;
        return max(lc -> getHigh(x, y), rc -> getHigh(x, y));
    }

    int getLow(int x, int y)
    {
        if (l > y || r < x)
            return maxC;
        if (x <= l && r <= y)
            return low;
        return min(lc -> getLow(x, y), rc -> getLow(x, y));
    }
} t;

void setup()
{
    cin >> n >> q;
    FOR(i, 1, n)
        cin >> h[i];
    t = interval(1, n);
    int x, y;
    FOR(i, 1, q)
    {
        cin >> x >> y;
        cout << t.getHigh(x, y) - t.getLow(x, y) << '\n';
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
