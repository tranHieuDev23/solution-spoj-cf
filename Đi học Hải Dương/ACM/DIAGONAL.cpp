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
int n, a[mn], pre[mn], suf[mn], ans = 0;

void setup()
{
    cin >> n;
    FOR(u, 1, n)
    {
        FOR(i, 1, n)
        {
            cin >> a[i];
            pre[i] = pre[i - 1] + a[i];
        }
        FORD(i, n, 1)
            suf[i] = suf[i + 1] + a[i];
        if (a[u] < pre[u - 1] + suf[u + 1])
        {
            cout << "NO";
            return;
        }
        ans += a[u] > pre[u - 1] + suf[u + 1];
    }
    if (ans)
        cout << "YES\n" << ans;
    else
        cout << "NO";
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("DIAGONAL.INP", "r", stdin);
    freopen("DIAGONAL.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
