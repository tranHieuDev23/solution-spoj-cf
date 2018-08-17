#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 102
#define maxC 1000000007000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define sum(l, r) ((sumC[r] - sumC[l - 1]) % 100)

using namespace std;
int n, c[mn], sumC[mn];
long long dp[mn][mn];

void setup()
{
    FOR(i, 1, n)
    {
        cin >> c[i];
        sumC[i] = sumC[i - 1] + c[i];
    }
}

void xuly()
{
    FORD(i, n, 1)
    {
        dp[i][i] = 0;
        FOR(j, i + 1, n)
        {
            dp[i][j] = maxC;
            FOR(k, i, j - 1)
            {
                long long val = dp[i][k] + dp[k + 1][j] + sum(i, k) * sum(k + 1, j);
                dp[i][j] = min(dp[i][j], val);
            }
        }
    }
    cout << dp[1][n] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    while(cin >> n)
    {
        setup ();
        xuly ();
    }
    return 0;
}
