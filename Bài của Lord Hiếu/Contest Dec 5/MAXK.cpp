#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 100000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, k, cur = 1, pre = 0, bef[mn];
long long a[mn], dp[mn][2], st[mn], bestDp[mn];

void setup()
{
    cin >> n >> k;
    FOR(i, 1, n)
        cin >> a[i];
}

void prepare()
{
    dp[0][cur] = maxC;
    dp[1][cur] = a[1];
    FOR(i, 2, n)
        dp[i][cur] = max(dp[i - 1][cur], a[i]);
}

void dping(int k)
{
    swap(cur, pre);
    bestDp[0] = maxC;
    int r = 0;
    FOR(i, 1, n)
    {
        bestDp[i] = dp[st[r]][pre];
        while(r && a[st[r]] <= a[i])
            bestDp[i] = min(bestDp[i], bestDp[st[r --]]);
        bef[i] = st[r];
        st[++ r] = i;
    }
    FOR(i, 0, k - 1)
        dp[i][cur] = maxC;
    FOR(i, k, n)
        dp[i][cur] = min(bestDp[i] + a[i], dp[bef[i]][cur]);
}

void xuly()
{
    prepare();
    FOR(i, 2, k)
        dping(i);
    cout << dp[n][cur];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MAXK.INP", "r", stdin);
    freopen("MAXK.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
