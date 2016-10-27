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
int n, m, k;
bool done[mn];
long long d1[mn], d2[mn];
vector< pair<int, int> > g[mn];
priority_queue< pair<long long, int> > p;

void setup()
{
    cin >> n >> m >> k;
    int u, v, w;
    FOR(i, 1, m)
    {
        cin >> u >> v >> w;
        g[u].pb(mp(v, w));
        g[v].pb(mp(u, w));
    }
}

void xuly()
{
    memset(d1, 60, sizeof(long long) * n);
    memset(d2, 60, sizeof(long long) * n);
    int u;
    FOR(i, 1, k)
    {
        cin >> u;
        d1[u] = d2[u] = 0;
        p.push(mp(0, u));
    }
    while(!p.empty())
    {
        int u = p.top().S;
        long long w = - p.top().F;
        p.pop();
        if (done[u])
            continue;
        done[u] = true;
        if (!u)
        {
            cout << w;
            return;
        }
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i].F;
            int e = g[u][i].S;
            if (w + e >= d2[v])
                continue;
            if (w + e < d1[v])
            {
                d2[v] = d1[v];
                d1[v] = w + e;
            }
            else
                d2[v] = w + e;
            p.push(mp(- d2[v], v));
        }
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
