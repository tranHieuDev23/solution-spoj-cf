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
int n, a[mn], l = 1, ans = 0;

bool inU(int x)
{
    int l = 1, r = maxC;
    while(r - l > 1)
    {
        int g = ((l + r) >> 1);
        if (((g + 1) * g / 2) <= x)
            l = g;
        else
            r = g;
    }
    return (((l + 1) * l) / 2) == x;
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
}

void xuly()
{
    FOR(r, 1, n + 1)
    {
        bool XinU = inU(a[r]);
        if (!XinU || a[r] < a[r - 1])
            ans = max(ans, r - l);
        if (!XinU)
            l = r + 1;
        else if (a[r] < a[r - 1])
            l = r;
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
