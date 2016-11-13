#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define maxC 20004
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn], ans = 0, l = 0;
bool ok[mn];

bool good(int x)
{
    int k = sqrt(x << 1);
    return (x << 1) == (k + 1) * k;
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> a[i];
        ok[i] = good(a[i]);
    }
}

void xuly()
{
    FOR(r, 1, n)
    if (ok[r])
    {
        if (!ok[r - 1] || a[r - 1] > a[r])
            l = r;
        ans = max(ans, r - l + 1);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MAXISEQ.INP", "r", stdin);
    freopen("MAXISEQ.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
