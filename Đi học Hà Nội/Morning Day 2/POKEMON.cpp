#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 10000000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m;
long long d1[mn], d2[mn];
vector< pair<int, int> > g[mn];

void setup()
{
    cin >> n >> m;
    int u, v, w;
    FOR(i, 1, m)
    {
        cin >> u >> v >> w;
        g[u].pb(mp(v, w));
    }
}

void fordBellman()
{
    d1[1] = 0;
    FOR(i, 2, n)
        d1[i] = -maxC;
    FOR(k, 2, n)
    FOR(u, 1, n)
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        int e = g[u][i].S;
        if (d1[u] != -maxC)
            d1[v] = max(d1[v], d1[u] + e);
    }

    FOR(i, 1, n)
        d2[i] = d1[i];
    FOR(k, 1, n * 5)
    FOR(u, 1, n)
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        int e = g[u][i].S;
        if (d2[u] != -maxC)
            d2[v] = max(d2[v], d2[u] + e);
    }
}

void xuly()
{
    fordBellman();
    FOR(u, 2, n)
    if (d1[u] == -maxC)
        cout << "IMPOSSIBLE\n";
    else if (d1[u] != d2[u])
        cout << "INFINITY\n";
    else
        cout << d1[u] << '\n';
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
