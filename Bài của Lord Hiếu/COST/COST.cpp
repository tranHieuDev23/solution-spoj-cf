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
int n, a[mn], lef[mn], rig[mn], st[mn];
long long ans = 0;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    a[n + 1] = maxC;
}

bool com(int a, int b, int code)
{
    if (code)
        return a > b;
    return a >= b;
}

void stacking(int* mang, int code)
{
    int r = 0;
    FOR(i, 1, n)
    {
        while(r && !com(a[st[r]], a[i], code))
            r --;
        mang[i] = st[r];
        st[++ r] = i;
    }
}

void xuly()
{
    stacking(lef, 0);
    reverse(a + 1, a + n + 1);
    stacking(rig, 1);
    reverse(a + 1, a + n + 1);
    reverse(rig + 1, rig + n + 1);
    FOR(i, 1, n)
        rig[i] = n + 1 - rig[i];
    FOR(i, 1, n)
    {
        int x = lef[i];
        if (x == 0 || a[x] > a[rig[i]])
            x = rig[i];
        if (1 <= x && x <= n)
            ans += a[x];
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("COST.INP", "r", stdin);
    freopen("COST.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
