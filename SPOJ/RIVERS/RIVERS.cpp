#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 102
#define maxC 1000000007000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define child(u) (int(g[u].size()))

using namespace std;
int n, k, tree[mn], dis[mn];
vector< pair<int, int> > g[mn];
long long dp[mn][mn][mn];
long long withU[mn][mn];
long long noU[mn][mn][mn];
int st[mn], r = 0;

void setup()
{
    cin >> n >> k;
    int p, d;
    FOR(i, 1, n)
    {
        cin >> tree[i] >> p >> d;
        g[p].pb(mp(i, d));
    }
}

void minimize(long long& a, const long long b)
{
    if (a > b) a = b;
}

long long temp[2][mn];
int cur = 1, pre = 0;

void dfs(int u)
{
    st[++ r] = u;
    FOR(i, 0, child(u) - 1)
    {
        int v = g[u][i].F;
        int w = g[u][i].S;
        dis[v] = dis[u] + w;
        dfs(v);
    }

    FORD(q, r, 1)
    {
        int p = st[q];
        FOR(t, 0, k)
            temp[cur][t] = 0;

        FOR(i, 0, child(u) - 1)
        {
            swap(cur, pre);
            int v = g[u][i].F;
            FOR(t, 0, k)
            {
                temp[cur][t] = maxC;
                FOR(j, 0, t)
                    minimize(temp[cur][t], temp[pre][j] + dp[v][t - j][p]);
            }
        }

        FOR(t, 0, k)
            noU[u][t][p] = temp[cur][t] + 1ll * tree[u] * (dis[u] - dis[p]);
    }

    FOR(t, 0, k)
        temp[cur][t] = 0;

    FOR(i, 0, child(u) - 1)
    {
        swap(cur, pre);
        int v = g[u][i].F;
        FOR(t, 0, k)
        {
            temp[cur][t] = maxC;
            FOR(j, 0, t)
                minimize(temp[cur][t], temp[pre][j] + dp[v][t - j][u]);
        }
    }

    FOR(t, 0, k)
        withU[u][t] = temp[cur][t];

    FOR(q, 1, r)
    {
        dp[u][0][st[q]] = noU[u][0][st[q]];
        FOR(t, 1, k)
            dp[u][t][st[q]] = min(noU[u][t][st[q]], withU[u][t - 1]);
    }
    r --;
}

void xuly()
{
    dfs(0);
    cout << noU[0][k][0];
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
