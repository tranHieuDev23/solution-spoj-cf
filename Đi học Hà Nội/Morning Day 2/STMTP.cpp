#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define mn2 50004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define curCoor d[coor.F][coor.S]

using namespace std;
int m, t, p, q, xl[mn2], yl[mn2];
int xh[mn2], yh[mn2], c[mn2], ans[mn][mn];
int d[mn][mn];

int root(int x, int y)
{
    if (d[x][y])
        return (d[x][y] = root(x, d[x][y]));
    return y;
}

void setup()
{
    cin >> m >> t >> p >> q;
    FOR(i, 1, q)
        cin >> xl[i] >> yl[i] >> xh[i] >> yh[i] >> c[i];
}

void deal(int id)
{
    FOR(x, xl[id], xh[id])
    {
        int y = yl[id];
        int rootUp = root(x, yh[id] + 1);
        while(true)
        {
            y = root(x, y);
            if (y > yh[id])
                break;
            ans[x][y] = c[id];
            d[x][y] = rootUp;
            y ++;
        }
    }
}

void xuly()
{
    FORD(i, q, 1)
        deal(i);
    FOR(i, 1, m)
    {
        FOR(j, 1, t)
            cout << ans[i][j] << ' ';
        cout << '\n';
    }
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
