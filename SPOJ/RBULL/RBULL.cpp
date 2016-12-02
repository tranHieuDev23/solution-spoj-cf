#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define mn2 2003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int m, n, dp[4][mn][mn], sum[mn2][mn2];
char c[mn][mn];
pair< pair<int, int> , pair<int, int> > ans;

void setup()
{
    cin >> m >> n;
    FOR(x, 1, m)
    FOR(y, 1, n)
    {
        cin >> c[x][y];
        int a = x + y;
        int b = x - y + n;
        sum[a][b] = (c[x][y] == '*');
    }
    FOR(x, 2, m + n)
    FOR(y, 1 - n + n, m - 1 + n)
        sum[x][y] += sum[x - 1][y] + sum[x][y - 1] - sum[x - 1][y - 1];
}

void calcDp0()
{
    FOR(x, 1, m)
    FOR(y, 1, n)
    {
        dp[0][x][y] = 1;
        if (c[x][y] == '*')
            if (c[x - 1][y] == '*' || c[x][y - 1] == '*')
                continue;
        dp[0][x][y] += min(dp[0][x - 1][y], dp[0][x][y - 1]);
    }
}

void calcDp1()
{
    FOR(x, 1, m)
    FORD(y, n, 1)
    {
        dp[1][x][y] = 1;
        if (c[x][y] == '*')
            if (c[x - 1][y] == '*' || c[x][y + 1] == '*')
                continue;
        dp[1][x][y] += min(dp[1][x - 1][y], dp[1][x][y + 1]);
    }
}

void calcDp2()
{
    FORD(x, m, 1)
    FOR(y, 1, n)
    {
        dp[2][x][y] = 1;
        if (c[x][y] == '*')
            if (c[x + 1][y] == '*' || c[x][y - 1] == '*')
                continue;
        dp[2][x][y] += min(dp[2][x + 1][y], dp[2][x][y - 1]);
    }
}
void calcDp3()
{
    FORD(x, m, 1)
    FORD(y, n, 1)
    {
        dp[3][x][y] = 1;
        if (c[x][y] == '*')
            if (c[x + 1][y] == '*' || c[x][y + 1] == '*')
                continue;
        dp[3][x][y] += min(dp[3][x + 1][y], dp[3][x][y + 1]);
    }
}

int numPole(int x, int y, int r)
{
    int highA = (x + r - 1) + y;
    int lowA = (x - r + 1) + y;
    int highB = (x + r - 1) - y + n;
    int lowB = (x - r + 1) - y + n;
    return sum[highA][highB] - sum[highA][lowB - 1] - sum[lowA - 1][highB] + sum[lowA - 1][lowB - 1];
}

void xuly()
{
    calcDp0();
    calcDp1();
    calcDp2();
    calcDp3();
    FOR(x, 1, m)
    FOR(y, 1, n)
    {
        int r = maxC;
        FOR(i, 0, 3)
            r = min(r, dp[i][x][y]);
        if (r)
        {
            pair< pair<int, int> , pair<int, int> > val = mp(mp(numPole(x, y, r), r), mp(x, y));
            ans = max(ans, val);
        }
    }
    cout << ans.F.F << ' ' << ans.S.F << ' ' << ans.S.S << ' ' << ans.F.S - 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("RBULL.INP", "r", stdin);
    freopen("RBULL.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
