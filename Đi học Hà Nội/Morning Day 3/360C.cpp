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
int n, k, dp[mn][mn], sumDp[mn][mn];
char s[mn];

int add(int const a, int const b)
{
    int re = (a + b);
    if (re >= maxC)
        re -= maxC;
    return re;
}

int mul(int const a, int const b)
{
    return (1ll * a * b) % maxC;
}

void setup()
{
    cin >> n >> k;
    FOR(i, 1, n)
        cin >> s[i];
}

void xuly()
{
    dp[0][0] = sumDp[0][0] = 1;
    FOR(i, 1, n)
    FOR(j, 0, k)
    {
        dp[i][j] = mul(sumDp[i - 1][j], s[i] - 'a');
        int id = i, num = j, sub = n - i + 1;
        while(-- id >= 0 && (num -= sub) >= 0)
            dp[i][j] = add(dp[i][j], mul(dp[id][num], 'z' - s[i]));
        sumDp[i][j] = add(sumDp[i - 1][j], dp[i][j]);
    }
    int ans = sumDp[n][k];
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
