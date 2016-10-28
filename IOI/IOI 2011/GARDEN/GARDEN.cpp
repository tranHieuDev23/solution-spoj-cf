#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 150005
#define mn2 300005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, p, q, to[mn2], disV0[mn2];
int disV1[mn2], loopV0, loopV1, mark[mn2], num = 0;
vector< pair<int, int> > g[mn];
vector<int> pre[mn2];
queue<int> que;

void setup()
{
    cin >> n >> m >> p;
    p ++;
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        u ++, v ++;
        if (int(g[u].size()) < 2)
            g[u].pb(mp(v, i));
        if (int(g[v].size()) < 2)
            g[v].pb(mp(u, i));
    }
}

void dfs(int u, int done, int cur)
{
    int v = g[u][done].F;
    int vDon = (g[u][done].S == g[v][0].S);
    int nex = v + vDon * n;
    to[cur] = nex;
    pre[nex].pb(cur);
    if (!to[nex])
        dfs(v, vDon, nex);
}

void bfs(int st, int* mang)
{
    FOR(i, 1, (n << 1))
        mang[i] = maxC;
    mang[st] = 0;
    que.push(st);
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        FOR(i, 0, int(pre[u].size()) - 1)
        {
            int v = pre[u][i];
            if (mang[v] == maxC)
            {
                mark[v] = num;
                mang[v] = mang[u] + 1;
                que.push(v);
            }
        }
    }
}

int calcLoop(int st)
{
    int u = st, re = 0;
    mark[st] = ++ num;
    while(true)
    {
        u = to[u];
        re ++;
        if (mark[u] == num)
            break;
        mark[u] = num;
    }
    return (u == st? re : maxC);
}

void prepare()
{
    FOR(u, 1, n)
    if (int(g[u].size()) == 1)
        g[u].pb(g[u][0]);
    FOR(u, 1, (n << 1))
    if (!to[u])
        dfs((u > n? u - n : u), (u > n), u);
    bfs(p, disV0);
    bfs(p + n, disV1);
    loopV0 = calcLoop(p);
    loopV1 = calcLoop(p + n);
}

bool ok(int u, int g)
{
    if (disV0[u] <= g && (g - disV0[u]) % loopV0 == 0)
        return true;
    if (disV1[u] <= g && (g - disV1[u]) % loopV1 == 0)
        return true;
    return false;
}

void xuly()
{
    prepare();
    cin >> q;
    int g, ans;
    FOR(i, 1, q)
    {
        cin >> g, ans = 0;
        FOR(u, 1, n)
            ans += ok(u, g);
        cout << ans << ' ';
    }
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
