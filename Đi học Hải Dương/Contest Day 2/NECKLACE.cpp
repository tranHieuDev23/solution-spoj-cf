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
int n, k;
long long dp[mn], inv[mn];

long long power(long long a, int b)
{
    long long re = 1;
    while(b)
    {
        if (b & 1)
            re = (re * a) % maxC;
        a = (a * a) % maxC;
        b >>= 1;
    }
    return re;
}

void add(long long& a, long long const b)
{
    a = (a + b) % maxC;
    a = (a + maxC) % maxC;
}

void setup()
{
    cin >> n >> k;
    memset(dp, 0, sizeof(long long) * (n + 1));
    long long hat = 1;
    long long ans = 0;
    FOR(i, 1, n)
    {
        hat = (hat * k) % maxC;
        if (n % i)
            continue;
        add(dp[i], hat);
        for(int t = (i << 1); t <= n; t += i)
            add(dp[t], - dp[i]);
        add(ans, (dp[i] * inv[i]) % maxC);
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("NECKLACE.INP", "r", stdin);
    freopen("NECKLACE.OUT", "w", stdout);
    FOR(i, 1, mn - 1)
        inv[i] = power(i, maxC - 2);
    int t; cin >> t;
    while(t --)
        setup ();
    return 0;
}
