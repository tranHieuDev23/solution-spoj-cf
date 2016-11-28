#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 200005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define opposite(x) (x > n? x - n : x + n)

using namespace std;
int n, n2, m, p, belong[mn2], siz[mn2];
int start[mn2], finish[mn2], nex[mn2];
vector< pair<int, int> > g[mn];
bool mark[mn], odd[mn], color[mn];

void setup()
{
    cin >> n >> m >> p;
    int u, v, w;
    FOR(i, 1, m)
    {
        cin >> u >> v >> w;
        g[u].pb(mp(v, i));
        g[v].pb(mp(u, i));
    }
}

void prepare()
{
    n2 = n << 1;
    FOR(i, 1, n2)
    {
        belong[i] = i;
        start[i] = finish[i] = i;
        siz[i] = 1;
        nex[i] = -1;
    }
}

bool combine(int a, int b)
{
    if (a == b)
        return true;
    if (siz[a] < siz[b])
        swap(a, b);
    for(int x = start[b]; x != -1; x = nex[x])
    {
        if (belong[opposite(x)] == a)
            return false;
        belong[x] = a;
    }
    nex[finish[a]] = start[b];
    finish[a] = finish[b];
    siz[a] += siz[b];
    return true;
}

bool checkPair()
{
    int u, v;
    FOR(i, 1, p)
    {
        cin >> u >> v;
        if (!combine(belong[u], belong[opposite(v)]))
            return false;
        if (!combine(belong[opposite(u)], belong[v]))
            return false;
    }
    return true;
}

void calcOdd(int x)
{
    x = belong[x];
    for(int i = start[x]; i != -1; i = nex[i])
    if (i > n)
        odd[i - n] = mark[i - n] = true;
    else
        mark[i] = true;
}

void dfs(int u, int p)
{
    if (!mark[u])
        calcOdd(u);
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (v == p)
            continue;
        dfs(v, u);
    }
}

void dfs(int u, int p, int num)
{

    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        if (v == p)
            continue;
        int id = g[u][i].S;
        if (odd[u] != odd[v])
            color[id] = true;
        dfs(v, u, num ^ color[id]);
    }
}

void xuly()
{
    prepare();
    if (!checkPair())
    {
        cout << "NO";
        return;
    }
    cout << "YES\n";
    dfs(1, 0);
    dfs(1, 0, 0);
    FOR(i, 1, m)
        cout << (color[i]? "ORANGE\n" : "PURPLE\n");
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SIMPLEGRAPH.INP", "r", stdin);
    freopen("SIMPLEGRAPH.OUT", "w", stdout);
    int t; cin >> t;
    setup ();
    xuly ();
    return 0;
}
