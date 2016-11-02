#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 25
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define bitPos(x) (1 << (x))
#define isIn(i, x) (((i) >> (x)) & 1)

using namespace std;
int n, m;
double x[mn], y[mn], c[mn][mn], dp[bitPos(21)][mn], ans = maxC;
bool mark[bitPos(21)][mn];

double dis(int a, int b)
{
    double difX = x[a] - x[b];
    double difY = y[a] - y[b];
    return sqrt(difX * difX + difY * difY);
}

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
    {
        cin >> x[i] >> y[i];
        FOR(j, 1, i - 1)
            c[i][j] = c[j][i] = dis(i, j);
        mark[bitPos(i - 1)][i] = true;
    }
    int u, v;
    FOR(i, 1, m)
    {
        cin >> u >> v;
        c[u][v] = c[v][u] = 0;
    }
}

void xuly()
{
    int last = bitPos(n) - 1;
    FOR(u, 1, last)
    FOR(i, 1, n)
    if (isIn(u, i - 1))
    {
        if (u == last)
        {
            ans = min(ans, dp[u][i]);
            continue;
        }
        FOR(j, 1, n)
        if (!isIn(u, j - 1))
        {
            int v = u | bitPos(j - 1);
            if (!mark[v][j] || dp[v][j] > dp[u][i] + c[i][j])
            {
                mark[v][j] = true;
                dp[v][j] = dp[u][i] + c[i][j];
            }
        }
    }
    if (ans == 0)
        cout << "YES";
    else
        cout << "NO\n" << fixed << setprecision(3) << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("BRIDGE.INP", "r", stdin);
    freopen("BRIDGE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
