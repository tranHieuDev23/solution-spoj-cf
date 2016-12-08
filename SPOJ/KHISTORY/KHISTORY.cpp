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
int n, m, num[mn], low[mn], rig = 0;
int belong[mn], numScc = 0, dp[mn][3];
vector<int> g1[mn], g2[mn];
stack<int> st;
bool mark[mn];

void setup()
{
    cin >> n >> m;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        g1[u].pb(v);
        g1[v].pb(u);
    }
}

void dfs(int u, int p)
{
    num[u] = low[u] = ++ rig;
    st.push(u);
    FOR(i, 0, int(g1[u].size()) - 1)
    {
        int v = g1[u][i];
        if (v == p)
            continue;
        if (num[v])
            low[u] = min(low[u], num[v]);
        else
        {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        }
    }
    if (low[u] == num[u])
    {
        numScc ++;
        while(true)
        {
            int v = st.top();
            st.pop();
            belong[v] = numScc;
            if (v == u)
                break;
        }
    }
}

void calcDp(int u, int p)
{
    mark[u] = true;
    int sumZero = 0;
    int sumDp = 0;
    FOR(i, 0, int(g2[u].size()) - 1)
    {
        int v = g2[u][i];
        if (v == p)
            continue;
        calcDp(v, u);
        sumZero += dp[v][0];
        sumDp += min(dp[v][1], dp[v][2]);
    }

    dp[u][0] = min(sumZero + 1, sumDp);
    dp[u][2] = sumZero + 1;

    dp[u][1] = maxC;
    FOR(i, 0, int(g2[u].size()) - 1)
    {
        int v = g2[u][i];
        if (v == p)
            continue;
        int val = sumDp - min(dp[v][1], dp[v][2]) + dp[v][2];
        dp[u][1] = min(dp[u][1], val);
    }
}

void xuly()
{
    FOR(u, 1, n)
    if (!num[u])
        dfs(u, 0);
    FOR(u, 1, n)
    FOR(i, 0, int(g1[u].size()) - 1)
    {
        int v = g1[u][i];
        if (belong[v] == belong[u])
            continue;
        g2[belong[u]].pb(belong[v]);
    }

    int ans = 0;
    FOR(i, 1, numScc)
    if (!mark[i])
    {
        calcDp(i, 0);
        ans += min(dp[i][1], dp[i][2]);
    }

    cout << ans;
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
