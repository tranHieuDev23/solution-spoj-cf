#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 20
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define isOne(x, i) (((x) >> (i)) & 1)

using namespace std;
int a[] =
{
    1, 2, 3,
    1, 2, 3, 4,
    5, 6, 7,
    5, 6, 7, 8,
    9, 10, 11
};
int b[] =
{
    2, 3, 4,
    5, 6, 7, 8,
    6, 7, 8,
    9, 10, 11, 12,
    10, 11, 12
};
int val[mn], chance[mn], deg[mn];
vector< pair<int, int> > g[mn];
int oddDeg;
long long ans = 0, sumVal;
bool mark[mn];

void setup()
{
    FOR(i, 0, 16)
    {
        cin >> val[i];
        int temp = val[i];
        while(temp)
            chance[i] ++, temp >>= 1;
    }
}

void dfs(int u)
{
    mark[u] = true;
    oddDeg += (deg[u] & 1);
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i].F;
        sumVal += g[u][i].S;
        if (mark[v])
            continue;
        dfs(v);
    }
}

long long check(int state)
{
    FOR(u, 1, 12)
    {
        g[u].clear();
        deg[u] = mark[u] = 0;
    }

    FOR(i, 0, 16)
    {
        int leftOne = isOne(state, i);
        if (val[i] == 0)
        {
            if (leftOne)
                return -1;
            continue;
        }
        if (val[i] == 1 && leftOne)
            continue;

        int w = val[i] - leftOne;
        int addDeg = chance[i] - leftOne;
        int u = a[i], v = b[i];
        deg[u] += addDeg, deg[v] += addDeg;
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }

    long long ret = 0;
    FOR(u, 1, 12)
    if (!mark[u])
    {
        oddDeg = sumVal = 0;
        dfs(u);
        if (oddDeg == 0 || oddDeg == 2)
            ret = max(ret, sumVal >> 1);
    }
    return ret;
}

void xuly()
{
    FOR(i, 0, (1 << 17) - 1)
        ans = max(ans, check(i));
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("GAME34.INP", "r", stdin);
    freopen("GAME34.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
