#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 12345678
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
long long a, b, c, d, intP, area, ans;

long long gcd(long long a, long long b)
{
    if (b)
        return gcd(b, a % b);
    return a;
}

void setup()
{
    cin >> a >> b >> c >> d;
    intP = (gcd(a, c) + gcd(b, d)) << 1;
    area = abs(a * d - b * c);
    ans = area - (intP >> 1) + 1;
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
    freopen("NPAIRS.INP", "r", stdin);
    freopen("NPAIRS.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
