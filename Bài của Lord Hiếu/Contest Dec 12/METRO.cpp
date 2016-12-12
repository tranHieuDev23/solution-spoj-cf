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
int n, m, k, a[mn], b[mn];
int x[mn], y[mn], pos[mn];
vector<int> up[mn], down[mn];
pair<int, int> difAB[mn];

struct interval
{
    int l, r, num;
    long long sum;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        num = sum = 0;
        if (l == r)
            lc = rc = NULL;
        else
        {
            lc = new interval(l, mid);
            rc = new interval(mid + 1, r);
        }
    }

    void add(int x, int v)
    {
        if (l > x || r < x)
            return;
        sum += v, num ++;
        if (l == r)
            return;
        if (x <= mid)
            lc -> add(x, v);
        else
            rc -> add(x, v);
    }

    void del(int x, int v)
    {
        if (l > x || r < x)
            return;
        sum -= v, num --;
        if (l == r)
            return;
        if (x <= mid)
            lc -> del(x, v);
        else
            rc -> del(x, v);
    }

    long long getBest(int x)
    {
        if (num <= x)
            return sum;
        if (lc -> num >= x)
            return lc -> getBest(x);
        return lc -> sum + rc -> getBest(x - lc -> num);
    }
} t;

void setup()
{
    cin >> n >> m >> k;
    FOR(i, 1, n)
    {
        cin >> a[i] >> b[i] >> x[i] >> y[i];
        up[x[i]].pb(i);
        down[y[i]].pb(i);
        difAB[i] = mp(a[i] - b[i], i);
    }
    sort(difAB + 1, difAB + n + 1, greater< pair<int, int> >());
    FOR(i, 1, n)
    {
        if (difAB[i].F <= 0)
            break;
        pos[difAB[i].S] = i;
    }
    t = interval(1, n);
}

void xuly()
{
    long long ans = 0, sumB = 0;
    FOR(u, 1, k)
    {
        FOR(i, 0, int(down[u].size()) - 1)
        {
            int x = down[u][i];
            sumB -= b[x];
            t.del(pos[x], a[x] - b[x]);
        }
        FOR(i, 0, int(up[u].size()) - 1)
        {
            int x = up[u][i];
            sumB += b[x];
            t.add(pos[x], a[x] - b[x]);
        }
        ans += sumB + t.getBest(m);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("METRO.INP", "r", stdin);
    freopen("METRO.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
