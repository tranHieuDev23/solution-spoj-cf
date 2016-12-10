#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define mn2 21
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, k, low[mn2], high[mn2];
int dp[2][mn], cur = 1, pre = 0;

void setup()
{
    cin >> n >> m >> k;
    FOR(i, 1, n)
        low[i] = 0, high[i] = m;
    int t, x, a;
    FOR(i, 1, k)
    {
        cin >> t >> x >> a;
        if (t == 1)
            low[x] = max(low[x], a);
        else
            high[x] = min(high[x], a);
        if (low[x] > high[x])
        {
            cout << 0;
            exit(0);
        }
    }
}

void add(int& a, int const b)
{
    a += b;
    if (a >= maxC) a -= maxC;
    if (a < 0) a += maxC;
}

void xuly()
{
    int sum, l, r;
    dp[cur][0] = 1;
    FOR(i, 1, n)
    {
        swap(cur, pre);
        sum = 0, l = 0, r = -1;
        FOR(j, 0, m)
        {
            while(r < j - low[i])
                add(sum, dp[pre][++ r]);
            while(l < j - high[i])
                add(sum, - dp[pre][l ++]);
            dp[cur][j] = sum;
        }
    }
    cout << dp[cur][m];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("EQUATION.INP", "r", stdin);
    freopen("EQUATION.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
