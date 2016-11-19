#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 5003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
void scanInt(int& x)
{
    x = 0;
    while(true)
    {
        char c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            return;
        x = (x * 10) + (c - '0');
    }
}

void printInt(int x)
{
    bool okZero = false;
    for(int i = 1000000000; i; i /= 10)
    {
        int digit = x / i;
        if (digit)
            okZero = true, putchar('0' + digit);
        else
            if (okZero)
                putchar('0');
        x %= i;
    }
}

int n, k, c[mn], d[mn], dis[mn][mn];
vector<int> g[mn];
priority_queue< pair< pair<int, int> , int > > p;

void setup()
{
    scanInt(n), scanInt(k);
    FOR(i, 1, n)
        scanInt(c[i]), scanInt(d[i]);
    int u, v;
    FOR(i, 1, k)
    {
        scanInt(u), scanInt(v);
        g[u].pb(v);
        g[v].pb(u);
    }
}

void check(int v, int rem, int w)
{
    if(dis[v][rem] <= w)
        return;
    dis[v][rem] = w;
    p.push(mp(mp(-w, rem), v));
}

void xuly()
{
    memset(dis, 59, sizeof(dis));
    dis[1][0] = 0;
    p.push(mp(mp(0, 0), 1));
    while(!p.empty())
    {
        int u = p.top().S;
        int rem = p.top().F.S;
        int w = - p.top().F.F;
        p.pop();
        if (w != dis[u][rem])
            continue;
        if (u == n)
        {
            printInt(w);
            return;
        }
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            if (rem)
                check(v, rem - 1, w);
            if (d[u])
                check(v, d[u] - 1, w + c[u]);
        }
    }
}

int main()
{
    freopen("ICBUS.INP", "r", stdin);
    freopen("ICBUS.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
