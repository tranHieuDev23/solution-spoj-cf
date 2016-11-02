#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)

using namespace std;
int n, m, r, belong[mn], co[mn], pos[mn], fin[mn];
int ans[mn], rig = 0, dif = 0;
map<int, int> num;
pair< pair<int, int> , int > q[mn];
vector<int> g[mn];

bool com(pair< pair<int, int> , int > a, pair< pair<int, int> , int > b)
{
    if (belong[a.F.S] != belong[b.F.S])
        return belong[a.F.S] < belong[b.F.S];
    return a.F.F < b.F.F;
}

void dfs(int u, int p)
{
    pos[u] = ++ rig;
    FOR(i, 0, int(g[u].size()) - 1)
    {
        int v = g[u][i];
        if (v == p)
            continue;
        dfs(v, u);
    }
    fin[u] = rig;
}

void setup()
{
    cin >> n >> m >> r;
    int u, v;
    FOR(i, 2, n)
    {
        cin >> u >> v;
        g[u].pb(v);
        g[v].pb(u);
    }
    FOR(i, 1, n)
        cin >> co[i];
}

void add(int val)
{
    dif += (++ num[val] == 1);
}

void del(int val)
{
    dif -= (-- num[val] == 0);
}

void xuly()
{
    int x = sqrt(n);
    FOR(i, 1, n)
        belong[i] = belong[i - 1] + (i % x == 1);
    dfs(r, 0);
    FOR(i, 1, m)
    {
        cin >> x;
        q[i] = mp(mp(pos[x], fin[x]), i);
    }
    sort(q + 1, q + m + 1, com);
    int l = 0, r = 0;
    FOR(i, 1, m)
    {
        int lef = q[i].F.F, rig = q[i].F.S;
        while(r < rig)
            add(co[++ r]);
        while(r > rig)
            del(co[r --]);
        while(l < lef)
            del(co[l ++]);
        while(l > lef)
            add(co[-- l]);
        ans[q[i].S] = dif;
    }
    FOR(i, 1, m)
        cout << ans[i] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("COLTREE.INP", "r", stdin);
    freopen("COLTREE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
