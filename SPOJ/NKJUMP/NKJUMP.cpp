#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn], out[mn], d[mn];
map<int, int> num;
vector<int> g[mn];
queue<int> q;

bool ok(int u, int v)
{
    if (a[u] <= a[v])
        return false;
    int dif = a[u] - a[v];
    return (dif == a[v]? num[dif] >= 2 : num[dif] >= 1);
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> a[i];
        num[a[i]] ++;
    }
    FOR(i, 1, n)
    FOR(j, 1, n)
    if (ok(i, j))
        g[i].pb(j), out[j] ++;
}

void xuly()
{
    int ans = 1;
    FOR(i, 1, n)
    if (!out[i])
        d[i] = 1, q.push(i);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        ans = max(ans, d[u]);
        FOR(i, 0, int(g[u].size()) - 1)
        {
            int v = g[u][i];
            d[v] = max(d[v], d[u] + 1);
            if (-- out[v] == 0)
                q.push(v);
        }
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
