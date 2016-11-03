#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 50004
#define maxC 123457
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int k, n, mem[mn], dp[mn][1 << 10];

void setup()
{
    scanf("%d%d", &k, &n);
    int t, c;
    FOR(i, 1, n)
    {
        scanf("%d", &t);
        FOR(j, 1, t)
        {
            scanf("%d", &c);
            mem[i] |= (1 << c);
        }
    }
}

void add(int& a, int const b)
{
    if ((a += b) >= maxC)
        a -= maxC;
}

void xuly()
{
    int last = (1 << 10) - 1;
    dp[n + 1][0] = 1;
    FORD(i, n + 1, 2)
    FOR(u, 0, last)
    {
        add(dp[i - 1][u], dp[i][u]);
        int v = mem[i - 1] ^ (u & mem[i - 1]);
        add(dp[i - 1][v], dp[i][u]);
    }
    int ans = 0;
    FOR(i, 0, last)
    if (__builtin_popcount(i) >= k)
        add(ans, dp[1][i]);
    printf("%d", ans);
}

int main()
{
    freopen("KSTR.INP", "r", stdin);
    freopen("KSTR.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
