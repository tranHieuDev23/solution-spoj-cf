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
struct interval
{
    int l, r, num;
    long long sumT;
    interval* lc;
    interval* rc;

    interval(int l = 0, int r = 0): l(l), r(r)
    {
        num = sumT = 0;
        if (l == r)
            lc = rc = NULL;
        else
        {
            lc = new interval(l, mid);
            rc = new interval(mid + 1, r);
        }
    }

    void update(int x, int t)
    {
        sumT += t;
        num ++;
        if (l == r)
            return;
        if (x <= mid)
            lc -> update(x, t);
        else
            rc -> update(x, t);
    }

    int findMaxNum(long long x)
    {
        if (l == r)
            return (sumT <= x? num : 0);
        if (lc -> sumT > x)
            return lc -> findMaxNum(x);
        return lc -> num + rc -> findMaxNum(x - lc -> sumT);
    }
} tr;
int n, Time, x[mn], t[mn];
int ans = 0, pos[mn];
pair<int, int> cake[mn];

void setup()
{
    cin >> n >> Time;
    FOR(i, 1, n)
    {
        cin >> x[i] >> t[i];
        cake[i] = mp(t[i], i);
    }
    sort(cake + 1, cake + n + 1);
    FOR(i, 1, n)
        pos[cake[i].S] = i;
    tr = interval(1, n);
}

void xuly()
{
    FOR(i, 1, n)
    {
        if (x[i] > Time)
            break;
        tr.update(pos[i], t[i]);
        ans = max(ans, tr.findMaxNum(Time - x[i]));
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("CAKE.INP", "r", stdin);
    freopen("CAKE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
