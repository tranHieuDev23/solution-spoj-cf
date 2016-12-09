#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 202
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
string s, w;
int n, m, a, b, k, co = 0;
int dp[mn][mn2], mark[mn][mn2];

int calcDp(int x, int y)
{
    int delta = x - y;
    if (abs(delta) > k)
        return maxC;
    int z = delta + 100;
    if (mark[x][z] == co)
        return dp[x][z];
    mark[x][z] = co;
    if (x == 0)
        return dp[x][z] = y * a;
    if (y == 0)
        return dp[x][z] = x * a;
    if (s[x - 1] == w[y - 1])
        return dp[x][z] = calcDp(x - 1, y - 1);
    dp[x][z] = maxC;
    dp[x][z] = min(dp[x][z], calcDp(x - 1, y) + a);
    dp[x][z] = min(dp[x][z], calcDp(x, y - 1) + a);
    dp[x][z] = min(dp[x][z], calcDp(x - 1, y - 1) + b);
    return dp[x][z];
}

void setup()
{
    cin >> s >> w >> a >> b >> k;
    co ++;
    int ans = calcDp(s.size(), w.size());
    cout << (ans > k? -1 : ans) << '\n';
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SEATSR.INP", "r", stdin);
    freopen("SEATSR.OUT", "w", stdout);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
