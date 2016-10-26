#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, q, d[mn], u[mn2], v[mn2], w[mn2], temp[mn2];

int root(int x)
{
    if (d[x])
        return (d[x] = root(d[x]));
    return x;
}

void setup()
{
    cin >> n >> m >> q;
    FOR(i, 1, m)
        cin >> u[i] >> v[i] >> w[i];
}

void xuly()
{
    memset(d, 0, sizeof(int) * (n + 1));
    int k, s, id, we, dem = 0; cin >> k >> s;
    FOR(i, 1, m)
        temp[i] = w[i];
    FOR(i, 1, s)
    {
        cin >> id >> we;
        temp[id] = we;
    }
    FOR(i, 1, m)
    if (temp[i] < temp[k])
    {
        int r1 = root(u[i]);
        int r2 = root(v[i]);
        if (r1 == r2)
            continue;
        d[r1] = r2;
        if (++ dem == n - 1)
            break;
    }
    int r1 = root(u[k]);
    int r2 = root(v[k]);
    if (r1 == r2)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        while(q --)
            xuly ();
    }
    return 0;
}
