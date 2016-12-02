#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 20004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, r, st[mn], lis[mn];
pair<int, int> doll[mn];

bool com(pair<int, int>& a, pair<int, int>& b)
{
    if (a.F != b.F)
        return a.F < b.F;
    return a.S > b.S;
}

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> doll[i].F >> doll[i].S;
    sort(doll + 1, doll + n + 1, com);
    r = 0;
}

void xuly()
{
    int ans = 0;
    FORD(i, n, 1)
    {
        lis[i] = upper_bound(st + 1, st + r + 1, doll[i].S) - st;
        r = max(r, lis[i]);
        st[lis[i]] = doll[i].S;
        ans = max(ans, lis[i]);
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
