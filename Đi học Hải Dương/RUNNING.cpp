#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;
int n, t, x[mn], s[mn], pre[mn], nex[mn];
priority_queue< pair<double, pair<int, int> > > p;

void setup()
{
    cin >> n >> t;
    FOR(i, 1, n)
        cin >> x[i] >> s[i];
    s[n + 1] = maxC;
    s[0] = -maxC;
}

void prepare()
{
    FOR(i, 1, n)
        nex[i] = i + 1, pre[i] = i - 1;
    FOR(i, 1, n - 1)
    if (s[i] > s[i + 1])
    {
        int dis = x[i + 1] - x[i];
        int dif = s[i] - s[i + 1];
        double tim = 1.0 * dis / dif;
        p.push(mp(- tim, mp(i, i + 1)));
    }
}

void xuly()
{
    prepare();
    int ans = n;
    while(!p.empty())
    {
        int u = p.top().S.F;
        int v = p.top().S.S;
        double tim = - p.top().F;
        p.pop();
        if (tim > t)
            break;
        if (nex[u] != v)
            continue;
        ans --;
        int z = pre[u];
        nex[z] = v;
        pre[v] = z;
        if (s[z] > s[v])
        {
            int dis = x[v] - x[z];
            int dif = s[z] - s[v];
            double tim = 1.0 * dis / dif;
            p.push(mp(- tim, mp(z, v)));
        }
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("RUNNING.INP", "r", stdin);
    freopen("RUNNING.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
