#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define dis(a, b) (abs(x[a] - x[b]) + abs(y[a] - y[b]))

using namespace std;

void getInt(int& x)
{
    char c = ' ';
    while(c == ' ' || c == '\n')
        c = getchar();
    x = c - '0';
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            return;
        x = x * 10 + c - '0';
    }
}

void printInt(int x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    bool okZero = false;
    for(int i = 1000000000; i; i /= 10)
    {
        int digit = x / i;
        x %= i;
        if (digit)
            okZero = true, putchar('0' + digit);
        else if (okZero)
            putchar('0');
    }
}

int n, x[mn], y[mn], id[mn2][mn2], d[mn];
int nextOnLine[mn2][mn2], preOnLine[mn2][mn2];
vector< pair< pair<int, int> , int> > e;
int last[mn2 << 1];

int getRoot(int x)
{
    if (d[x])
        return d[x] = getRoot(d[x]);
    return x;
}

void setup()
{
    getInt(n);
    FOR(i, 1, n)
    {
        getInt(x[i]), getInt(y[i]);
        if (id[x[i]][y[i]])
        {
            i --, n --;
            continue;
        }
        id[x[i]][y[i]] = i;
    }
    memset(last, -1, sizeof(last));
}

void prepapre()
{
    FOR(x, 0, 1000)
    {
        FOR(y, 0, 1000)
        if (id[x][y - 1])
            preOnLine[x][y] = id[x][y - 1];
        else
            preOnLine[x][y] = preOnLine[x][y - 1];
        FORD(y, 1000, 0)
        if (id[x][y + 1])
            nextOnLine[x][y] = id[x][y + 1];
        else
            nextOnLine[x][y] = nextOnLine[x][y + 1];
    }
}

void addEdge(int x, int y, int w)
{
    e.pb(mp(mp(x, y), last[w]));
    last[w] = int(e.size()) - 1;
}

void calcEdge()
{
    FOR(u, 1, n)
    FOR(_x, 0, 1000)
    {
        int id1;
        if (_x != x[u] && id[_x][y[u]])
            id1 = id[_x][y[u]];
        else
            id1 = nextOnLine[_x][y[u]];
        int id2 = preOnLine[_x][y[u]];

        if (id1)
            addEdge(u, id1, dis(u, id1));
        if (id2)
            addEdge(u, id2, dis(u, id2));
    }
}

int calcAns()
{
    int ans = 0, tplt = n;
    FOR(w, 0, (mn2 << 1) - 1)
    for(int i = last[w]; i != -1; i = e[i].S)
    {
        int r1 = getRoot(e[i].F.F);
        int r2 = getRoot(e[i].F.S);
        if (r1 == r2)
            continue;
        d[r1] = r2;
        ans += w;
        if (-- tplt == 1)
            break;
    }
    return ans;
}

void xuly()
{
    prepapre();
    calcEdge();
    printInt(calcAns());
}

int main()
{
    freopen("MST.INP", "r", stdin);
    freopen("MST.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
