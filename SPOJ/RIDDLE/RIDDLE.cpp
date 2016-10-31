#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)

using namespace std;
int n, k, a[mn], tem[mn];

void setup()
{
    cin >> n >> k;
    FOR(i, 1, n)
        cin >> a[i];
}

bool ok(int x)
{
    FOR(i, 1, x)
        tem[i] = a[i];
    sort(tem + 1, tem + x + 1);
    int hig = 0;
    FOR(i, 1, x)
    {
        if (tem[i] > hig + 1)
            return false;
        hig += tem[i];
        if (hig >= k)
            return true;
    }
    return false;
}

void xuly()
{
    int l = 0, r = n + 1;
    while(r - l > 1)
    {
        if (ok(mid))
            r = mid;
        else
            l = mid;
    }
    if (r == n + 1)
        cout << "-1\n";
    else
        cout << r << '\n';
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
        xuly ();
    }
    return 0;
}
