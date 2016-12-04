#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 1000000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, l[mn], r[mn], bestPos[mn][mn];
long long dp[mn][mn];

void setup()
{
    cin >> m;
    FOR(i, 1, m)
    {
        cin >> r[i];
        l[i + 1] = r[i] + 1;
    }
    l[1] = 1;
    r[m + 1] = n;
}

void xuly()
{
    FOR(rig, 1, m + 1)
    {
        dp[rig][rig] = 0;
        bestPos[rig][rig] = rig;
        FORD(lef, rig - 1, 1)
        {
            dp[lef][rig] = maxC;
            FOR(mid, bestPos[lef][rig - 1], bestPos[lef + 1][rig])
            {
                if (mid + 1 > rig)
                    break;
                long long cost = dp[lef][mid] + dp[mid + 1][rig] + r[rig] - l[lef] + 1;
                if (cost < dp[lef][rig])
                    dp[lef][rig] = cost, bestPos[lef][rig] = mid;
            }
        }
    }
    cout << dp[1][m + 1] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    while(cin >> n)
    {
        setup ();
        xuly ();
    }
    return 0;
}
