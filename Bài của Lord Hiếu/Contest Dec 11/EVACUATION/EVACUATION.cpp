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
int n, last[mn];
vector< pair< int , pair<int, int> > > g[mn];
priority_queue< pair<int, int> > p;

void setup()
{
    cin >> n;
    int u, v, d, t;
    FOR(i, 2, n)
    {
        cin >> u >> v >> d >> t;
        g[u].pb(mp(v, mp(d, t)));
        g[v].pb(mp(u, mp(d, t)));
    }
}

void xuly()
{
    int ans = 0;
    FOR(u, 1, n)
    if (g[u].size() == 1)
    {
        last[u] = maxC;
        p.push(mp(maxC, u));
    }
    else
        last[u] = -1;
    while(!p.empty())
    {
        int u = p.top().S;
        int w = p.top().F;
        p.pop();
        if (w != last[u])
            continue;
        if (w < 0)
            break;
        ans ++;
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int d = g[u][i].S.F;
            int t = g[u][i].S.S;
            int z = min(w, t) - d;
            if (last[v] < z)
            {
                last[v] = z;
                p.push(mp(z, v));
            }
        }
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("EVACUATION.INP", "r", stdin);
    freopen("EVACUATION.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
