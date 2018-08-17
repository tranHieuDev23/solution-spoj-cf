#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 101
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn], dp[mn][mn2], ans = 0;
pair<int, int> p[mn];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> a[i];
        p[i] = mp(a[i], i);
    }
    sort(p + 1, p + n + 1);
}

void dealWith(int u, int d)
{
    pair<int, int> z = mp(a[u] - d, u - 1);
    int v = upper_bound(p + 1, p + n + 1, z) - p - 1;
    if (p[v].F != a[u] - d)
        dp[u][d] = 1;
    else
        dp[u][d] = dp[p[v].S][d] + 1;
    ans = max(ans, dp[u][d]);
}

void xuly()
{
    FOR(i, 1, n)
    FOR(j, 1, mn2 - 1)
        dealWith(i, j);
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
