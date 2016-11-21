#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
long long m, n, p, q, last = 0;

void setup()
{
    cin >> n >> m >> p >> q;
    FOR(i, 2, n)
        last = (last + m) % i;
}

void xuly()
{
    long long ans1 = (p + last) % n;
    long long ans2 = (q - last + n) % n;
    cout << ans1 << ' ' << ans2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("JOSEPHUS.INP", "r", stdin);
    freopen("JOSEPHUS.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
