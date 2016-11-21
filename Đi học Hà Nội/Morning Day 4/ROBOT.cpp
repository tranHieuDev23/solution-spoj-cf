#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 10004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int m, n, l, k, ans;
int addX[] = {-1, 0, 1, 0};
int addY[] = {0, 1, 0, -1};
int changeX[20], changeY[20];
bool mark[mn][mn];

bool valid(int x, int y)
{
    if (x < 1)
        return false;
    if (x > m)
        return false;
    if (y < 1)
        return false;
    if (y > n)
        return false;
    return !mark[x][y];
}

int dir(char c)
{
    if (c == 'U')
        return 0;
    if (c == 'R')
        return 1;
    if (c == 'D')
        return 2;
    return 3;
}

void setup()
{
    cin >> m >> n >> l >> k;
    char c;
    FOR(i, 1, l)
    {
        cin >> c;
        int d = dir(c);
        changeX[i] = changeX[i - 1] + addX[d];
        changeY[i] = changeY[i - 1] + addY[d];
    }
    ans = m * n;
}

void check(int x, int y)
{
    FOR(i, 0, l)
    {
        int _x = x - changeX[i];
        int _y = y - changeY[i];
        if (valid(_x, _y))
            mark[_x][_y] = true, ans --;
    }
}

void xuly()
{
    int x, y;
    FOR(i, 1, k)
    {
        cin >> x >> y;
        check(x, y);
    }
    FOR(i, 1, m)
        check(i, 0), check(i, n + 1);
    FOR(i, 1, n)
        check(0, i), check(m + 1, i);
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
