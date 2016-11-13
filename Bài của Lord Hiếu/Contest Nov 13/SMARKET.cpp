#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 502
#define mn2 10004
#define mn3 100005
#define maxC 131131
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, s, c[mn], m[mn], use[mn];
int dp[mn3][mn], sumDp[mn2];

void add(int& a, int const b)
{
    a = (a + b) % maxC;
    a = (a + maxC) % maxC;
}

void setup()
{
    cin >> s >> n;
    dp[0][0] = 1;
    FOR(i, 1, n)
    {
        cin >> c[i] >> m[i];
        memset(sumDp, 0, sizeof(int) * c[i]);
        int mod = -1;
        FOR(v, 0, s)
        {
            if (++ mod == c[i])
                mod = 0;
            add(sumDp[mod], dp[v][i - 1]);
            int removeVal = v - c[i] * (m[i] + 1);
            if (removeVal >= 0)
                add(sumDp[mod], -dp[removeVal][i - 1]);
            dp[v][i] = sumDp[mod];
        }
    }
}

void calcUse(int remain, int u)
{
    if (!u)
        return;
    FOR(i, 0, m[u])
    if (dp[remain - c[u] * i][u - 1])
    {
        use[u] = i;
        calcUse(remain - c[u] * i, u - 1);
        return;
    }
}

void xuly()
{
    cout << dp[s][n] << '\n';
    if (dp[s][n])
    {
        calcUse(s, n);
        FOR(i, 1, n)
            cout << use[i] << ' ';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SMARKET.INP", "r", stdin);
    freopen("SMARKET.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
