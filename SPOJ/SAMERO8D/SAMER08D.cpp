#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int k;
string a, b;
int n, m, equa[mn][mn], dp[mn][mn];

void setup()
{
    cin >> a >> b;
    n = a.size();
    m = b.size();
}

void xuly()
{
    FOR(i, 1, n)
    FOR(j, 1, m)
    if (a[i - 1] == b[j - 1])
        equa[i][j] = equa[i - 1][j - 1] + 1;
    else
        equa[i][j] = 0;

    FOR(i, 1, n)
    FOR(j, 1, m)
    {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        if (equa[i][j] >= k)
        {
            FOR(z, k, equa[i][j])
                dp[i][j] = max(dp[i][j], dp[i - z][j - z] + z);
        }
    }

    cout << dp[n][m] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    while(cin >> k)
    {
        if (k == 0)
            break;
        setup ();
        xuly ();
    }
    return 0;
}
