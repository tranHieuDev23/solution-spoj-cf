#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 5000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n;
long long del, p, m, q, a[mn], suf[mn];

void setup()
{
    cin >> n >> del >> p >> q >> m;
    FOR(i, 1, n)
        a[i] = (p * i) % m + q + del * i;
    suf[n] = a[n];
    FORD(i, n - 1, 1)
        suf[i] = max(suf[i + 1], a[i]);
    long long ans = 1ll * maxC * maxC;
    long long sub = 0;
    long long pre = 0;
    long long add = del * n;
    FOR(i, 1, n)
    {
        ans = min(ans, max(pre, suf[i]) - sub);
        pre = max(pre, a[i] + add);
        sub += del;
    }
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
    setup ();
    xuly ();
    return 0;
}
