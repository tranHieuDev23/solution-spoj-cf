#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
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
        if(digit)
            okZero = true, putchar('0' + digit);
        else
            if (okZero)
                putchar('0');
    }
}

int n, m, k, last[mn], to[mn], pre[mn], sz[mn];
int lastK[mn], preK[mn], fromK[mn], r = 0;

void setup()
{
    scanInt(n), scanInt(m), scanInt(k);
    int u;
    FOR(i, 1, m)
    {
        scanInt(u), scanInt(to[i]);
        pre[i] = last[u];
        last[u] = i;
        sz[u] ++;
    }
}

void printEdge(int u, int id)
{
    if(!id)
        return;
    printEdge(u, pre[id]);
    int &v = to[id];
    fromK[++ r] = u;
    preK[r] = lastK[v];
    lastK[v] = r;
    printInt(v), putchar(' ');
}

void firstRequest()
{
    printInt(n), putchar(' '), printInt(m), putchar('\n');
    int head = 1;
    FOR(u, 1, n)
    {
        printInt(head); putchar(' ');
        head += sz[u];
    }
    putchar('\n');
    FOR(u, 1, n)
        printEdge(u, last[u]);
    putchar('\n');
}

void printFrom(int v, int id)
{
    if(!id)
        return;
    printFrom(v, preK[id]);
    printInt(fromK[id]), putchar(' ');
}

void secondRequest()
{
    int v; scanInt(v);
    printFrom(v, lastK[v]);
    putchar('\n');
}

void xuly()
{
    firstRequest();
    while(k --)
        secondRequest();
}

int main()
{
    freopen("GREP.INP", "r", stdin);
    freopen("GREP.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
