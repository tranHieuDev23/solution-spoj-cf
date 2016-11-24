#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define sum(l, r) (a[r] - a[l - 1])

using namespace std;
int n, up[mn], ans[mn];
long long s, a[mn];

void setup()
{
    cin >> n >> s;
    FOR(i, 1, n)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }
}

void calcUp()
{
    int id = n;
    FORD(i, n, 1)
    {
        while(sum(i, id) > s)
            id --;
        up[i] = id;
    }
}

bool check(int x, int u)
{
    if (!u)
        return false;
    if (x - u > up[x] - x + 1)
        return false;
    return up[u] >= x - 1;
}

void calcAns()
{
    int id = n;
    FORD(i, n, 2)
    if (up[i] >= i)
    while(check(i, id - 1))
        ans[-- id] = i;
    FOR(u, 1, n - 1)
        ans[u] = max(((ans[u] - u) << 1), 0);
}

void xuly()
{
    calcUp();
    calcAns();
    FOR(i, 1, n)
        cout << ans[i] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("INTEREST.INP", "r", stdin);
    freopen("INTEREST.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
