#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, f[mn], loop[mn], low[mn], g[mn];
bool done[mn];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> f[i], low[i] = n + 1;
    FOR(i, 1, n)
    if (!loop[i])
    {
        int dem = 0, u = i;
        while(true)
        {
            loop[u] = -1, dem ++;
            if (loop[u = f[u]] == -1)
                break;
        }
        while(true)
        {
            loop[u] = dem;
            if (loop[u = f[u]] != -1)
                break;
        }
        if (!done[loop[i]])
        {
            done[loop[i]] = true;
            for(int t = loop[i]; t <= n; t += loop[i])
                low[t] = min(low[t], i);
        }
    }
    FOR(i, 1, n)
    {
        if (!g[i])
        {
            int id = i, v = low[loop[i]];
            FOR(j, 1, loop[i])
            {
                g[id] = v;
                id = f[id], v = f[v];
            }
        }
        cout << g[i] << ' ';
    }
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("COMMUTE.INP", "r", stdin);
    freopen("COMMUTE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
