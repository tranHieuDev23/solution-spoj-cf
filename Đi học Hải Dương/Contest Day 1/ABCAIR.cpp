#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 20004
#define mn2 202
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, k, q, pos[mn], dis[mn2][mn2], lowTo[mn][mn2], lowFrom[mn2][mn];
pair< pair<int, int> , int > e[mn];
vector< pair<int, int> > in[mn], out[mn];

void setup()
{
    cin >> n >> m >> k >> q;
    FOR(i, 1, m)
        cin >> e[i].F.F >> e[i].F.S >> e[i].S;
    int u;
    FOR(i, 1, k)
    {
        cin >> u;
        pos[u] = i;
        FOR(j, 1, i - 1)
            dis[i][j] = dis[j][i] = maxC;
    }
}

void prepare()
{
    FOR(i, 1, m)
    {
        int u = e[i].F.F;
        int v = e[i].F.S;
        int d = e[i].S;
        if (pos[u] && pos[v])
            dis[pos[u]][pos[v]] = min(dis[pos[u]][pos[v]], d);
        if (!pos[v])
            in[v].pb(mp(pos[u], d));
        if (!pos[u])
            out[u].pb(mp(pos[v], d));
    }
    FOR(u, 1, n)
    if (in[u].size() && out[u].size())
    {
        FOR(j, 0, int(in[u].size()) - 1)
        {
            int a = in[u][j].F, da = in[u][j].S;
            FOR(k, 0, int(out[u].size()) - 1)
            {
                int b = out[u][k].F, db = out[u][k].S;
                dis[a][b] = min(dis[a][b], da + db);
            }
        }
    }
    FOR(i, 1, k)
    FOR(p, 1, k)
    FOR(q, 1, k)
        dis[p][q] = min(dis[p][q], dis[p][i] + dis[i][q]);
}

void calcLow(int u)
{
    FOR(i, 1, k)
        lowTo[u][i] = lowFrom[i][u] = maxC;
    FOR(i, 1, k)
    {
        FOR(j, 0, int(out[u].size()) - 1)
            lowTo[u][i] = min(lowTo[u][i], out[u][j].S + dis[out[u][j].F][i]);
        FOR(j, 0, int(in[u].size()) - 1)
            lowFrom[i][u] = min(lowFrom[i][u], dis[i][in[u][j].F] + in[u][j].S);
    }
}

int getAns(int u, int v)
{
    if (pos[u] && pos[v])
        return dis[pos[u]][pos[v]];
    if (pos[v])
        return lowTo[u][pos[v]];
    if (pos[u])
        return lowFrom[pos[u]][v];
    int re = maxC;
    FOR(i, 0, int(out[u].size()) - 1)
        re = min(re, out[u][i].S + lowFrom[out[u][i].F][v]);
    return re;
}

void xuly()
{
    prepare();
    FOR(i, 1, n)
    if (!pos[i])
        calcLow(i);
    int a, b, satis = 0;
    long long sum = 0;
    FOR(i, 1, q)
    {
        cin >> a >> b;
        int ans = getAns(a, b);
        if (ans != maxC)
            satis ++, sum += ans;
    }
    cout << satis << '\n' << sum;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("ABCAIR.INP", "r", stdin);
    freopen("ABCAIR.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
