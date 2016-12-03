#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 10004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, dp[mn][2], choice[mn][2];
vector<int> g[mn], child[mn];
deque<int> route;
bool mark[mn];

void setup()
{
    cin >> n;
    FOR(u, 1, n)
    {
        g[u].clear();
        child[u].clear();
        mark[u] = false;
    }
    int u, v;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
}

bool comp(int& a, int& b)
{
    return dp[a][1] - dp[a][0] < dp[b][1] - dp[b][0];
}

void dfs(int u, int p)
{
    int sumDp = 0;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p)
            continue;
        dfs(v, u);
        child[u].pb(v);
        sumDp += dp[v][0];
    }

    if (child[u].size() == 0)
    {
        dp[u][0] = dp[u][1] = 1;
        choice[u][0] = choice[u][1] = 1;
        return;
    }

    if (child[u].size() == 1)
    {
        int v = child[u][0];
        if (dp[v][0] + 1 < dp[v][1])
            dp[u][1] = dp[v][0] + 1, choice[u][1] = 1;
        else
            dp[u][1] = dp[v][1], choice[u][1] = 2;
        dp[u][0] = dp[u][1];
        choice[u][0] = choice[u][1];
        return;
    }

    sort(child[u].begin(), child[u].end(), comp);
    int v1 = child[u][0];
    int v2 = child[u][1];
    int dif1 = dp[v1][1] - dp[v1][0];
    int dif2 = dp[v2][1] - dp[v2][0];

    if (sumDp + 1 < sumDp + dif1)
        dp[u][1] = sumDp + 1, choice[u][1] = 1;
    else
        dp[u][1] = sumDp + dif1, choice[u][1] = 2;

    int mid = sumDp + dif1 + dif2 - 1;
    if (mid < dp[u][1])
        dp[u][0] = mid, choice[u][0] = 3;
    else
        dp[u][0] = dp[u][1], choice[u][0] = choice[u][1];
}

void routeStart(int u)
{
    while(true)
    {
        route.pb(u);
        if (choice[u][1] == 1)
            break;
        u = child[u][0];
    }
}

void routeMid(int u)
{
    route.push_front(u);
    int v1 = child[u][0];
    while(true)
    {
        route.push_front(v1);
        if (choice[v1][1] == 1)
            break;
        v1 = child[v1][0];
    }
    int v2 = child[u][1];
    while(true)
    {
        route.push_back(v2);
        if (choice[v2][1] == 1)
            break;
        v2 = child[v2][0];
    }
}

void flushAns()
{
    mark[route.front()] = true;
    cout << route.front();
    route.pop_front();
    while(!route.empty())
    {
        mark[route.front()] = true;
        cout << ' ' << route.front();
        route.pop_front();
    }
    cout << '\n';
}

void tracing(int u)
{
    if (!mark[u])
    {
        if (choice[u][0] == 3)
            routeMid(u);
        else
            routeStart(u);
        flushAns();
    }
    FOR(i, 0, int(child[u].size()) - 1)
    {
        int v = child[u][i];
        tracing(v);
    }
}

void xuly()
{
    dfs(1, 0);
    cout << dp[1][0] << '\n';
    tracing(1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("PT07F.INP", "r", stdin);
    freopen("PT07F.OUT", "w", stdout);
    int t; cin >> t;
    while (t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
