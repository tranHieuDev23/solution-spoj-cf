#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define mn2 30
#define mn3 90
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int co, t, a, n;
int ti[mn], ai[mn], wi[mn];
int dp[mn][mn2][mn3];
int mark[mn][mn2][mn3];

void setup()
{
    cin >> t >> a >> n;
    FOR(i, 1, n)
        cin >> ti[i] >> ai[i] >> wi[i];
}

int ans(int u, int t, int a)
{
    if (t <= 0 && a <= 0)
        return 0;
    if (u == 0)
        return maxC;
    t = max(t, 0);
    a = max(a, 0);
    if (mark[u][t][a] == co)
        return dp[u][t][a];
    mark[u][t][a] = co;
    dp[u][t][a] = min(ans(u - 1, t, a), ans(u - 1, t - ti[u], a - ai[u]) + wi[u]);
    return dp[u][t][a];
}

void xuly()
{
    cout << ans(n, t, a) << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int c; cin >> c;
    for(co = 1; co <= c; co ++)
    {
        setup ();
        xuly ();
    }
    return 0;
}
