#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
struct line
{
    long long a, b;

    line(long long a = 0, long long b = 0): a(a), b(b) {}

    bool operator < (line const& x)
    {
        if (a != x.a)
            return a > x.a;
        return b < x.b;
    }

    long long val(long long const x)
    {
        return a * x + b;
    }

    double intersect(line const& x)
    {
        return 1.0 * (x.b - b) / (a - x.a);
    }
} allLine[mn], st[mn];
int n, m, h[mn], top;
double rLim[mn];

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
        cin >> h[i];
    sort(h + 1, h + n + 1);
    int x, y;
    FOR(i, 1, m)
    {
        cin >> x >> y;
        allLine[i] = line(- (x << 1), 1ll * x * x + 1ll * y * y);
    }
}

void prepare()
{
    sort(allLine + 1, allLine + m + 1);
    st[top = 1] = allLine[1];
    rLim[0] = - maxC;
    rLim[1] = maxC;
    FOR(i, 2, m)
    if (allLine[i].a != allLine[i - 1].a)
    {
        double x = allLine[i].intersect(st[top]);
        while(x < rLim[top - 1])
            x = allLine[i].intersect(st[-- top]);
        st[++ top] = allLine[i];
        rLim[top - 1] = x;
        rLim[top] = maxC;
    }
}

void xuly()
{
    prepare();
    int id = 1;
    double ans = 0;
    FOR(i, 1, n)
    {
        while(h[i] > rLim[id])
            id ++;
        long long square = st[id].val(h[i]) + 1ll * h[i] * h[i];
        ans = max(ans, sqrt(square));
    }
    cout << fixed << setprecision(4) << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("HLBAY.INP", "r", stdin);
    freopen("HLBAY.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
