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
int n, m, rig, base = 0, d[mn], way[mn];
vector< pair<int, int> > g[mn];
priority_queue< pair<int, int> > p;

struct trie
{
    int id;
    trie* child[26];

    trie()
    {
        id = 0;
        FOR(i, 0, 25)
            child[i] = NULL;
    }
} t;

int scanInt(int& x)
{
    x = 0;
    char c;
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            return x;
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

int getId()
{
    trie* p = &t;
    char c;
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            break;
        int z = c - 'a';
        if (p -> child[z] == NULL)
            p -> child[z] = new trie();
        p = p -> child[z];
    }
    if (p -> id > base)
        return (p -> id) - base;
    p -> id = base + (++ rig);
    return rig;
}

void setup()
{
    scanInt(m);
    base += mn, rig = 0;
    FOR(i, 1, n)
        g[i].clear();
    getId(); getId();
    int u, v, w;
    FOR(i, 1, m)
    {
        u = getId();
        v = getId();
        scanInt(w);
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }
}

void IJK()
{
    memset(d, 60, sizeof(int) * (n + 1));
    d[2] = 0;
    p.push(mp(0, 2));
    while(!p.empty())
    {
        int u = p.top().S;
        int w = - p.top().F;
        p.pop();
        if (w != d[u])
            continue;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int e = g[u][i].S;
            if (w + e >= d[v])
                continue;
            d[v] = w + e;
            p.push(mp(- d[v], v));
        }
    }
}

void calcWay()
{
    memset(way, 0, sizeof(int) * (n + 1));
    way[1] = 1;
    FOR(i, 1, n)
        p.push(mp(d[i], i));
    while(!p.empty())
    {
        int u = p.top().S;
        p.pop();
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            if (d[v] >= d[u])
                continue;
            way[v] += way[u];
        }
    }
}

void xuly()
{
    IJK();
    calcWay();
    printInt(way[2]);
    putchar('\n');
}

int main()
{
    freopen("WALK.INP", "r", stdin);
    freopen("WALK.OUT", "w", stdout);
    while(scanInt(n))
    {
        setup ();
        xuly ();
    }
    return 0;
}
