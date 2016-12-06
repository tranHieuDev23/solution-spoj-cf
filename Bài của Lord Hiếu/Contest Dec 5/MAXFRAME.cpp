#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 402
#define maxC 20000000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, a[mn][mn];
long long sumLine[mn][mn], ans = -maxC;

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
    FOR(j, 1, m)
    {
        cin >> a[i][j];
        sumLine[i][j] = sumLine[i][j - 1] + a[i][j];
    }
}

void deal(int l, int r)
{
    long long best = sumLine[1][r] - sumLine[1][l - 1];
    FOR(i, 2, n)
    {
        long long val = best + sumLine[i][r] - sumLine[i][l - 1];
        ans = max(ans, val);
        best = max(best + a[i][l] + a[i][r], sumLine[i][r] - sumLine[i][l - 1]);
    }
}

void xuly()
{
    FOR(i, 1, m - 1)
    FOR(j, i + 1, m)
        deal(i, j);
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MAXFRAME.INP", "r", stdin);
    freopen("MAXFRAME.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
