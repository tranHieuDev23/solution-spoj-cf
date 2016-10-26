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
int n, m, l, mark[mn], num = 0, trace[mn], traceE[mn];
long long d[mn], ans = 0;
queue<int> q;
vector<long long> far;
vector< pair<int, int> > g[mn];

void setup()
{
    cin >> n >> m >> l;
    int u, v, w;
    FOR(i, 1, m)
    {
        cin >> u >> v >> w;
        u ++, v ++;
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }
}

int bfs(int s)
{
    mark[s] = ++ num;
    d[s] = 0;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        if (d[u] > d[s])
            s = u;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            if (mark[v] == num)
                continue;
            mark[v] = num;
            d[v] = d[u] + g[u][i].S;
            trace[v] = u;
            traceE[v] = g[u][i].S;
            q.push(v);
        }
    }
    return s;
}

long long getFar(int u)
{
    int v1 = bfs(u);
    int v2 = bfs(v1);
    ans = max(ans, d[v2]);
    long long disV1 = d[v2];
    long long disV2 = 0;
    long long best = d[v2];
    while(v2 != v1)
    {
        disV1 -= traceE[v2];
        disV2 += traceE[v2];
        best = min(best, max(disV1, disV2));
        v2 = trace[v2];
    }
    return best;
}

void xuly()
{
    FOR(i, 1, n)
    if (!mark[i])
        far.pb(getFar(i));
    sort(far.begin(), far.end(), greater<long long>());
    if (far.size() >= 2)
        ans = max(ans, far[0] + far[1] + l);
    if (far.size() >= 3)
        ans = max(ans, far[1] + far[2] + (l << 1));
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
