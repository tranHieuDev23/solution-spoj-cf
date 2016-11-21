#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 123456789
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, k, a[mn];
long long ans;

void multi(long long& a, long long b)
{
    a = (a * b) % maxC;
}

void setup()
{
    cin >> n >> k;
    FOR(i, 1, n)
        cin >> a[i];
    ans = 1;
}

void evenK()
{
    int l = 1, r = n - 1;
    while(k)
    {
        long long lef = 1ll * a[l] * a[l + 1];
        long long rig = 1ll * a[r] * a[r + 1];
        if (lef < rig)
            multi(ans, rig % maxC), r -= 2;
        else
            multi(ans, lef % maxC), l += 2;
        k -= 2;
    }
}

void xuly()
{
    sort(a + 1, a + n + 1);
    if (k & 1)
    {
        if (a[n] < 0)
        {
            FORD(i, n, n - k + 1)
                multi(ans, a[i]);
        }
        else
        {
            ans = a[n];
            n --, k --;
            evenK();
        }
    }
    else
        evenK();
    cout << (ans + maxC) % maxC << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("PRODUCT.INP", "r", stdin);
    freopen("PRODUCT.OUT", "w", stdout);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
