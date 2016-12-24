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
int n, a[mn], num[mn];
pair<int, int> temp[mn];
long long sumId[mn], ans;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> temp[i].F, temp[i].S = i;
    sort(temp + 1, temp + n + 1);
    int val = 0;
    FOR(i, 1, n)
    {
        if (temp[i].F != temp[i - 1].F)
            val ++;
        a[temp[i].S] = val;
    }
}

void xuly()
{
    ans = 0;
    FOR(i, 1, n)
    {
        int numSame = num[a[i]];
        long long sumSame = sumId[a[i]];
        ans += 1ll * i * numSame - sumSame - numSame;
        num[a[i]] ++;
        sumId[a[i]] += i;
    }
    cout << ans << '\n';
    FOR(i, 1, n)
        num[a[i]] = sumId[a[i]] = 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("TRIPLE.INP", "r", stdin);
    freopen("TRIPLE.OUT", "w", stdout);
    int t; cin >> t;
    FOR(i, 1, t)
    {
        cout << "Case #" << i << ": ";
        setup ();
        xuly ();
    }
    return 0;
}
