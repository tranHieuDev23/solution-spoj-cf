#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 300005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn], st[mn], r;
int preLow[mn], preHig[mn], aftLow[mn], aftHig[mn];

bool comp(int& a, int& b, int code)
{
    if (code == 0)
        return a < b;
    if (code == 1)
        return a <= b;
    if (code == 2)
        return a >= b;
    return a > b;
}

void stacking(int* mang, int code)
{
    r = 0;
    FOR(i, 1, n)
    {
        while(r && !comp(a[st[r]], a[i], code))
            r --;
        mang[i] = st[r];
        st[++ r] = i;
    }
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
}

void xuly()
{
    stacking(preLow, 0);
    stacking(preHig, 2);
    reverse(a + 1, a + n + 1);
    stacking(aftLow, 1);
    stacking(aftHig, 3);
    reverse(a + 1, a + n + 1);
    reverse(aftLow + 1, aftLow + n + 1);
    reverse(aftHig + 1, aftHig + n + 1);
    FOR(i, 1, n)
    {
        aftHig[i] = n + 1 - aftHig[i];
        aftLow[i] = n + 1 - aftLow[i];
    }
    long long ans = 0;
    FOR(i, 1, n)
    {
        preHig[i] = i - preHig[i];
        preLow[i] = i - preLow[i];
        aftHig[i] = aftHig[i] - i;
        aftLow[i] = aftLow[i] - i;
        long long rangeMax = 1ll * preHig[i] * aftHig[i];
        long long rangeMin = 1ll * preLow[i] * aftLow[i];
        ans += (rangeMax - rangeMin) * a[i];
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("DIFFER.INP", "r", stdin);
    freopen("DIFFER.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
