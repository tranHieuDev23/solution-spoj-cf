#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2005
#define maxC 1000000007
#define base 100007
#define mp make_pair
#define F first
#define S second

using namespace std;
int n, m, pari[mn], _x = -1, _y;
long long temp[mn][mn], a[mn][mn], sum = 0;

void setup()
{
    memset(pari, -1, sizeof(pari));
    cin >> n >> m;
    FOR(i, 1, n)
    FOR(j, 1, m)
    {
        cin >> temp[i][j];
        if (temp[i][j])
        {
            sum += temp[i][j];
            _x = i;
            _y = j;
        }
    }
}

void cop()
{
    FOR(i, 1, n)
    FOR(j, 1, m)
        a[i][j] = temp[i][j];
}

bool over(int x, int y)
{
    return (a[x][y + 1] && a[x][y] >= a[x][y + 1]) || (a[x + 1][y] && a[x][y] >= a[x + 1][y]);
}

void speacialCase()
{
    if (n == 1)
    {
        cop();
        FOR(i, 1, m)
        {
            if (a[1][i] == 0)
            {
                a[1][i] = a[1][i - 1] + 1;
                sum += a[1][i];
            }
            if (over(1, i))
            {
                cout << -1;
                exit(0);
            }
        }
        cout << sum;
        exit(0);
    }
    if (m == 1)
    {
        cop();
        FOR(i, 1, n)
        {
            if (a[i][1] == 0)
            {
                a[i][1] = a[i - 1][1] + 1;
                sum += a[i][1];
            }
            if (over(i, 1))
            {
                cout << -1;
                exit(0);
            }
        }
        cout << sum;
        exit(0);
    }
}

long long checkH()
{
    cop();
    long long re = sum;
    pari[_x] = (a[_x][_y] & 1);
    FOR(i, 1, n)
        pari[i] = ((abs(_x - i) & 1) ? 1 - pari[_x] : pari[_x]);
    FOR(i, 1, n)
    FOR(j, 1, m)
    {
        if (a[i][j] == 0)
        {
            a[i][j] = max(a[i - 1][j], a[i][j - 1]) + 1;
            if ((a[i][j] & 1) != pari[i])
                a[i][j] ++;
            re += a[i][j];
        }
        else
            if ((a[i][j] & 1) != pari[i])
                return -1;
        if (over(i, j))
            return -1;
    }
    return re;
}

long long checkV()
{
    cop();
    long long re = sum;
    pari[_y] = (a[_x][_y] & 1);
    FOR(i, 1, m)
        pari[i] = ((abs(_y - i) & 1) ? 1 - pari[_y] : pari[_y]);
    FOR(i, 1, n)
    FOR(j, 1, m)
    {
        if (a[i][j] == 0)
        {
            a[i][j] = max(a[i - 1][j], a[i][j - 1]) + 1;
            if ((a[i][j] & 1) != pari[j])
                a[i][j] ++;
            re += a[i][j];
        }
        else
            if ((a[i][j] & 1) != pari[j])
                return -1;
        if (over(i, j))
            return -1;
    }
    return re;
}

void xuly ()
{
    if (_x == -1)
        _x = _y = temp[1][1] = sum = 1;
    speacialCase();
    long long a = checkH();
    long long b = checkV();
    if (a == -1)
    {
        cout << b;
        return;
    }
    if (b == -1)
    {
        cout << a;
        return;
    }
    cout << min(a, b);
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
