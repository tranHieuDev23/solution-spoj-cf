#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn], odd[mn], even[mn];
long long lef[mn], rig[mn], sumOdd[mn], best = 0, ans = 0;

void setup()
{
    cin >> n;
    FOR(i, 2, n)
    {
        cin >> a[i];
        if (a[i] & 1)
            odd[i] = a[i], even[i] = a[i] - 1;
        else
            odd[i] = a[i] - 1, even[i] = a[i];
        sumOdd[i] = sumOdd[i - 1] + odd[i];
    }
}

void xuly()
{
    FOR(i, 2, n)
    if (a[i] == 1)
        lef[i] = 0;
    else
        lef[i] = even[i] + lef[i - 1];

    FORD(i, n - 1, 1)
    if (a[i + 1] == 1)
        rig[i] = 0;
    else
        rig[i] = even[i + 1] + rig[i + 1];

    FOR(i, 2, n)
    {
        best = max(best, lef[i] - sumOdd[i]);
        ans = max(ans, best + sumOdd[i] + rig[i]);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("BRIDGES.INP", "r", stdin);
    freopen("BRIDGES.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
