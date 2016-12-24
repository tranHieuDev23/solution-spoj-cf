#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn], ans = 0, temp[mn];

int lis(int s, int t)
{
    int r = 1;
    temp[1] = a[s];
    FOR(i, s + 1, t)
    if (a[i] > a[s])
    {
        int id = lower_bound(temp + 1, temp + r + 1, a[i]) - temp;
        r = max(r, id);
        temp[id] = a[i];
    }
    return r;
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> a[i];
        a[i + n] = a[i];
    }
    FOR(i, 1, n)
        ans = max(ans, lis(i, i + n - 1));
    cout << ans;
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("LWEEL.INP", "r", stdin);
    freopen("LWEEL.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
