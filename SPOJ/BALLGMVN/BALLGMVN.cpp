#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define mn2 2003
#define maxC 1000000007
#define pb push_back
#define X first.first
#define Y first.second
#define id second
#define mp make_pair

using namespace std;
typedef pair< pair<int, int> , int > TPoint;

int n, c[mn2];
TPoint blue[mn], red[mn], all[mn2], cur;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> all[i].X >> all[i].Y;
        all[i].id = i, c[i] = 1;
        blue[i] = all[i];
    }
    FOR(i, n + 1, n << 1)
    {
        cin >> all[i].X >> all[i].Y;
        all[i].id = i;
        red[i - n] = all[i];
    }
}

long long ccw(TPoint& a, TPoint& b, TPoint& c)
{
    int vecABx = b.X - a.X;
    int vecABy = b.Y - a.Y;
    int vecBCx = c.X - b.X;
    int vecBCy = c.Y - b.Y;
    return 1ll * vecABx * vecBCy - 1ll * vecABy * vecBCx;
}

bool comp(TPoint a, TPoint b)
{
    if (a.id == cur.id)
        return false;
    if (b.id == cur.id)
        return true;
    return ccw(a, cur, b) < 0;
}

void dealWith(TPoint& u)
{
    cur = u; sort(all + 1, all + (n << 1) + 1, comp);
    int r = 2;
    FOR(i, 1, (n << 1))
    {
        while(r < (n << 1) && ccw(all[i], u, all[r]) < 0)
            r ++;
        if (r == (n << 1))
            return;
        if (ccw(all[i], u, all[r]) == 0)
        {
            int x = all[i].id;
            int y = u.id;
            int z = all[r].id;
            if (x == y || y == z || z == x)
                continue;
            if (c[x] == c[y] && c[x] == c[z])
                continue;
            cout << x << ' ' << y <<  ' ' << z;
            exit(0);
        }
    }
}

void xuly()
{
    FOR(i, 1, n)
        dealWith(blue[i]);
    FOR(i, 1, n)
        dealWith(red[i]);
    cout << -1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("BALLGMVN.INP", "r", stdin);
    freopen("BALLGMVN.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
