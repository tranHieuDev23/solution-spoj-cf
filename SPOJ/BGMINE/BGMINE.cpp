#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 100000000700000ll
#define base 100007
#define mp make_pair
#define F first
#define S second

using namespace std;
int n, maxPos[mn];
long long x[mn], g[mn], r[mn], sum = 0, ans = 0, t[mn];
pair< long long, int > p[mn];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> x[i] >> g[i] >> r[i];
        sum += r[i];
        g[i] += g[i - 1];
        t[i] = sum - x[i];
        p[i] = mp(t[i], i);
    }
}

void xuly ()
{
    sort(p + 1, p + n + 1);
    FORD(i, n, 1)
        maxPos[i] = max(maxPos[i + 1], p[i].S);
    FOR(i, 1, n)
    {
        int id = lower_bound(p + 1, p + n + 1, mp(t[i] - r[i], 0)) - p;
        if (id != n + 1 && maxPos[id] >= i)
            ans = max(ans, g[maxPos[id]] - g[i - 1]);
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
