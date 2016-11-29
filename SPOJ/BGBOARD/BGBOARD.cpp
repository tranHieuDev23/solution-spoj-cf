#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 405
#define mn2 1000001
#define maxC 100000000700000ll

using namespace std;
int m, n, dem = 0, val[mn2], mark[mn * mn], mark2[mn * mn], ans = 0;
int t[mn][mn], pos[mn][mn * mn], f[mn][mn][mn];

void setup()
{
    cin >> m >> n;
    FOR(i, 1, m)
    FOR(j, 1, n)
    {
        cin >> t[i][j];
        if (!val[t[i][j]])
            val[t[i][j]] = ++ dem;
        t[i][j] = val[t[i][j]];
    }
}

void deal(int u, int d)
{
    dem ++;
    FOR(r, 1, n)
    {
        mark[t[u][r]] = dem;
        mark2[t[d][r]] = dem;
        pos[u][t[u][r]] = r;
        pos[d][t[d][r]] = r;
        int cases = max(f[u][d][r - 1], max(f[u + 1][d][r], f[u][d - 1][r]));
        if (mark2[t[u][r]] != dem)
        {
            mark2[t[u][r]] = dem;
            pos[d][t[u][r]] = 0;
        }
        if (mark[t[d][r]] != dem)
        {
            mark[t[d][r]] = dem;
            pos[u][t[d][r]] = 0;
        }
        int posU = pos[u][t[d][r]];
        int posD = pos[d][t[u][r]];
        int top = max(max(cases, 1), max(posU, posD) + 1);
        ans = max(ans, (r - top + 1) * (d - u + 1));
        f[u][d][r] = top;
    }
}

void xuly ()
{
    dem = 0;
    int l;
    FORD(u, m, 1)
    {
        dem ++;
        l = 1;
        FOR(r, 1, n)
        {
            if (mark[t[u][r]] != dem)
            {
                mark[t[u][r]] = dem;
                pos[u][t[u][r]] = r;
            }
            else
            {
                l = max(l, pos[u][t[u][r]] + 1);
                pos[u][t[u][r]] = r;
            }
            f[u][u][r] = l;
            ans = max(ans, r - l + 1);
        }
        FOR(d, u + 1, m)
            deal(u, d);
    }
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
