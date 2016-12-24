#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define mn2 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, dsu[mn2], siz[mn2], dp[mn2][mn2];
int mark[mn2], co = 0, connect[mn2];
pair< int , pair<int, int> > e[mn];

int getRoot(int x)
{
    if (dsu[x])
        return dsu[x] = getRoot(dsu[x]);
    return x;
}

void setup()
{
    cin >> n >> m;
    FOR(i, 1, m)
        cin >> e[i].S.F >> e[i].S.S >> e[i].F;
    sort(e + 1, e + m + 1);
}

bool check(int x)
{
    FOR(i, 1, n)
        dsu[i] = 0, siz[i] = 1;
    FOR(i, x + 1, m)
    if (e[i].F > e[x].F)
    {
        int r1 = getRoot(e[i].S.F);
        int r2 = getRoot(e[i].S.S);
        if (r1 != r2)
        {
            dsu[r1] = r2;
            siz[r2] += siz[r1];
        }
    }

    int sz = 0; co ++;
    FOR(u, 1, n)
    {
        int r = getRoot(u);
        if (mark[r] == co)
            continue;
        mark[r] = co;
        connect[++ sz] = r;
    }

    dp[0][0] = co;
    FOR(i, 1, sz)
    FOR(j, 0, n)
    {
        int u = connect[i];
        if (dp[i - 1][j] == co)
            dp[i][j] = co;
        else if (j >= siz[u])
            if (dp[i - 1][j - siz[u]] == co)
                dp[i][j] = co;
    }

    return dp[sz][n >> 1] == co;
}

void xuly()
{
    int l = -1, r = m;
    while(r - l > 1)
    {
        int g = ((l + r) >> 1);
        if (check(g))
            r = g;
        else
            l = g;
    }
    cout << e[r].F;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("TEAM.INP", "r", stdin);
    freopen("TEAM.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
