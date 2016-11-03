#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 12345678
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
long long n, dp[3][3][2], one[3][3];
int cur = 1, pre = 0;

void add(long long& a, long long const b)
{
    a = (a + b) % maxC;
    a = (a + maxC) % maxC;
}

void calc(long long x)
{
    if (x == 1)
    {
        dp[0][0][cur] = dp[1][1][cur] = dp[2][2][cur] = 1;
        return;
    }
    calc(x >> 1);
    swap(cur, pre);
    FOR(i, 0, 2)
    FOR(j, 0, 2)
    {
        dp[i][j][cur] = 0;
        FOR(k, 0, 2)
        FOR(q, 0, 2)
        if (!k || !q || k != q)
            add(dp[i][j][cur], (dp[i][k][pre] * dp[q][j][pre]) % maxC);
    }
    if (x & 1)
    {
        swap(cur, pre);
        FOR(i, 0, 2)
        FOR(j, 0, 2)
        {
            dp[i][j][cur] = 0;
            FOR(k, 0, 2)
            FOR(q, 0, 2)
            if (!k || !q || k != q)
                add(dp[i][j][cur], (dp[i][k][pre] * one[q][j]) % maxC);
        }
    }
}

void setup()
{
    cin >> n;
    one[0][0] = one[1][1] = one[2][2] = 1;
    calc(n);
    long long ans = -1;
    FOR(i, 0, 2)
    FOR(j, 0, 2)
        add(ans, dp[i][j][cur]);
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
    freopen("TABLE.INP", "r", stdin);
    freopen("TABLE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
