#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 20
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define bitPos(x) (1 << (x))
#define isIn(i, x) (((i) >> (x)) & 1)

using namespace std;
string s;
int n, m, digit[mn], num[10];
long long fac[mn], dp[bitPos(mn)][100];

void setup()
{
    cin >> s >> m;
    n = s.size();
    fac[0] = 1;
    FOR(i, 1, n)
    {
        digit[i] = s[i - 1] - '0';
        num[digit[i]] ++;
        if (digit[i])
            dp[bitPos(i - 1)][digit[i] % m] = 1;
        fac[i] = fac[i - 1] * i;
    }
}

void xuly()
{
    int last = bitPos(n) - 1;
    FOR(u, 1, last - 1)
    FOR(cur, 0, m - 1)
    if (dp[u][cur])
    {
        FOR(i, 1, n)
        if (!isIn(u, i - 1))
        {
            int v = u | bitPos(i - 1);
            int nex = (cur * 10 + digit[i]) % m;
            dp[v][nex] += dp[u][cur];
        }
    }
    long long dup = fac[num[0]];
    FOR(i, 1, 9)
        dup = dup * fac[num[i]];
    long long ans = dp[last][0] / dup;
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("PERMN.INP", "r", stdin);
    freopen("PERMN.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
