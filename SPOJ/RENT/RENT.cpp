#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2000006
#define mn2 10004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, dp[mn], maxDp[mn];
pair< pair<int, int> , int > order[mn2];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> order[i].F.S >> order[i].F.F >> order[i].S;
        order[i].F.F += order[i].F.S;
    }
    sort(order + 1, order + n + 1);
    memset(dp, 0, sizeof(dp));
    maxDp[0] = 0;
}

void xuly()
{
    int r = 0, ans = 0;
    FOR(i, 1, n)
    {
        while(r < order[i].F.S)
        {
            r ++;
            maxDp[r] = max(maxDp[r - 1], dp[r]);
        }
        int bestDeal = maxDp[order[i].F.S] + order[i].S;
        dp[order[i].F.F] = max(dp[order[i].F.F], bestDeal);
        ans = max(ans, bestDeal);
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
