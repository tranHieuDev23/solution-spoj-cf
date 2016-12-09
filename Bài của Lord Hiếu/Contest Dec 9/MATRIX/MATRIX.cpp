#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int m, n, dp[mn][mn];
long long ans = 0;

void setup()
{
    cin >> m >> n;
    char c;
    FOR(i, 1, m)
    FOR(j, 1, n)
    {
        cin >> c;
        if (c == '1')
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + 1;
        ans += dp[i][j];
    }
    cout << ans;
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MATRIX.INP", "r", stdin);
    freopen("MATRIX.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
