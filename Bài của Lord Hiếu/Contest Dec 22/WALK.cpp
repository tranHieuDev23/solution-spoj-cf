#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 10004
#define mn2 38
#define maxC 10000000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;

int nextInt()
{
    char c = ' ';
    while(c == ' ' || c == '\n')
        c = getchar();
    int x = c - '0';
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            break;
        x = x * 10 + c - '0';
    }
    return x;
}

void printString(string const s)
{
    FOR(i, 0, int(s.size()) - 1)
        putchar(s[i]);
}

void printLongLong(long long x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    bool okZero = false;
    for(long long i = 1000000000000000000ll; i; i /= 10)
    {
        int digit = x / i;
        x %= i;
        if (digit)
            okZero = true, putchar('0' + digit);
        else if (okZero)
            putchar('0');
    }
}

int n, m, a, b;
long long d[mn][mn2];
priority_queue< pair< long long, pair<int, int> > > p;
vector< pair<int, int> > g[mn];

void setup()
{
    n = nextInt(), m = nextInt(), a = nextInt(), b = nextInt();
    FOR(i, 1, n)
    {
        g[i].clear();
        FOR(j, 0, mn2 - 1)
            d[i][j] = maxC;
    }
    int u, v, w;
    FOR(i, 1, m)
    {
        u = nextInt(), v = nextInt(), w = nextInt();
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }
}

void dijiktra()
{
    d[a][0] = 0;
    p.push(mp(0, mp(a, 0)));
    while(!p.empty())
    {
        int u = p.top().S.F;
        int r = p.top().S.S;
        long long w = - p.top().F;
        p.pop();
        if (w != d[u][r])
            continue;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int e = g[u][i].S;
            int newR = min(r + 1, mn2 - 1);
            if (d[v][newR] <= w + e)
                continue;
            d[v][newR] = w + e;
            p.push(mp(- d[v][newR], mp(v, newR)));
        }
    }
}

void xuly()
{
    dijiktra();
    long long ans = maxC;
    FOR(i, 0, mn2 - 1)
    {
        long long twoPower = 1ll << i;
        long long val = d[b][i] << (twoPower <= d[b][i]);
        ans = min(ans, val);
    }
    if (ans == maxC)
        putchar('-'), putchar('1');
    else
        printLongLong(ans);
    putchar('\n');
}

int main()
{
    freopen("WALK.INP", "r", stdin);
    freopen("WALK.OUT", "w", stdout);
    int t = nextInt();
    FOR(i, 1, t)
    {
        printString("Case #"), printLongLong(i), putchar(':'), putchar(' ');
        setup ();
        xuly ();
    }
    return 0;
}
