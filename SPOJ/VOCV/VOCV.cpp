#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100500
#define maxC 10007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, minSpot[mn][2], way[mn][2];
vector<int> g[mn];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        g[i].clear();
        minSpot[i][0] = minSpot[i][1] = 0;
        way[i][0] = way[i][1] = 0;
    }
    int u, v;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

void dfs(int u, int p)
{
    int zero = 0, one = 0;
    int wayOne = 1, wayZero = 1;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p)
            continue;
        dfs(v, u);
        zero += minSpot[v][0];
        one += minSpot[v][1];
        wayZero = (wayZero * way[v][0]) % maxC;
        wayOne = (wayOne * way[v][1]) % maxC;
    }
    minSpot[u][0] = one + 1;
    minSpot[u][1] = min(one + 1, zero);
    way[u][0] = wayOne;
    if (minSpot[u][1] == one + 1)
        way[u][1] += wayOne;
    if (minSpot[u][1] == zero)
        way[u][1] += wayZero;
    way[u][1] %= maxC;
}

void xuly()
{
    dfs(1, 0);
    cout << minSpot[1][1] << ' ' << way[1][1] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
