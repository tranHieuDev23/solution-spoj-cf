#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 300005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, ans[5];
long long p[mn], bestP = 0;
vector<int> g[mn];
pair<int, int> e[mn];

bool comp(int& a, int& b)
{
    return p[a] > p[b];
}

void setup()
{
    cin >> n >> m;

    ans[1] = ans[2] = ans[3] = ans[4] = n + 1;
    FOR(i, 1, n)
    {
        cin >> p[i];
        if (p[i] > bestP)
            bestP = p[i], ans[1] = i;
    }

    FOR(i, 1, m)
    {
        cin >> e[i].F >> e[i].S;
        g[e[i].F].pb(e[i].S);
        g[e[i].S].pb(e[i].F);
    }

    FOR(i, 1, n)
    {
        sort(g[i].begin(), g[i].end(), comp);
        g[i].pb(n + 1), g[i].pb(n + 2);
    }
}

void check(int u, int v)
{
    int u1 = (g[u][0] == v? 1 : 0);
    int u2 = (g[u][u1 + 1] == v? u1 + 2 : u1 + 1);
    int v1 = (g[v][0] == u? 1 : 0);
    int v2 = (g[v][v1 + 1] == u? v1 + 2 : v1 + 1);

    long long best; int id1, id2;
    if (g[u][u1] != g[v][v1])
    {
        id1 = g[u][u1], id2 = g[v][v1];
        best = p[u] + p[v] + p[id1] + p[id2];
    }
    else
    {
        long long best1 = p[u] + p[v] + p[g[u][u2]] + p[g[v][v1]];
        long long best2 = p[u] + p[v] + p[g[u][u1]] + p[g[v][v2]];
        if (best1 > best2)
            best = best1, id1 = g[u][u2], id2 = g[v][v1];
        else
            best = best2, id1 = g[u][u1], id2 = g[v][v2];
    }

    if (best > bestP)
    {
        bestP = best;
        ans[1] = u, ans[2] = v, ans[3] = id1, ans[4] = id2;
    }
}

void xuly()
{
    FOR(i, 1, m)
        check(e[i].F, e[i].S);
    sort(ans + 1, ans + 5);
    int r = 0;
    FOR(i, 1, 4)
    if (ans[i] <= n)
        r ++;
    else
        break;
    cout << r << '\n';
    FOR(i, 1, r)
        cout << ans[i] << ' ';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("TOURIST.INP", "r", stdin);
    freopen("TOURIST.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
