#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 151
#define mn2 301
#define mn3 300005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
typedef bitset<150> bit;

int n, m, q;
char c[mn][mn];
bit data[mn2], canMove[mn][mn][mn2], allOne;
pair<int, int> a[mn3], b[mn3];

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
    FOR(j, 1, m)
    {
        cin >> c[i][j];
        if (c[i][j] == '.')
            data[i + j].set(i - 1);
    }
    cin >> q;
}

void prepare()
{
    FOR(i, 0, n - 1)
        allOne.set(i);

    FOR(x, 1, n)
    FOR(y, 1, m)
    if (c[x][y] == '.')
    {
        canMove[x][y][x + y].set(x - 1);
        FOR(dia, x + y + 1, n + m)
        {
            bit temp = canMove[x][y][dia - 1] << 1;
            canMove[x][y][dia] = (canMove[x][y][dia - 1] | temp) & data[dia];
        }
        FORD(dia, x + y - 1, 2)
        {
            bit temp = canMove[x][y][dia + 1] >> 1;
            canMove[x][y][dia] = (canMove[x][y][dia + 1] | temp) & data[dia];
        }
    }
}

bool check(pair<int, int>& a, pair<int, int>& b, pair<int, int>& c)
{
    int diaA = a.F + a.S;
    int diaB = b.F + b.S;
    int diaC = c.F + c.S;

    if (diaA > diaC)
        return false;

    if (diaB < diaA || diaB > diaC)
        return canMove[a.F][a.S][diaC][c.F - 1];

    bit temp = canMove[a.F][a.S][diaB] & canMove[c.F][c.S][diaB];
    temp.set(b.F - 1, 0);
    return (temp & allOne).any();
}

int query()
{
    int ret = 0, szA, szB, szC;
    pair<int, int> c;
    cin >> szA;
    FOR(i, 1, szA)
        cin >> a[i].F >> a[i].S;
    cin >> szB;
    FOR(i, 1, szB)
        cin >> b[i].F >> b[i].S;
    cin >> szC;
    FOR(i, 1, szC)
    {
        cin >> c.F >> c.S;
        FOR(j, 1, szA)
        FOR(k, 1, szB)
            ret += check(a[j], b[k], c);
    }
    return ret;
}

void xuly()
{
    prepare();
    while(q --)
        cout << query() << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("TURTLE.INP", "r", stdin);
    freopen("TURTLE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
