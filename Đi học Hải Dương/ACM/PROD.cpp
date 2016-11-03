#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define mn2 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int a;
long long ans = 0;

struct bitTree
{
    long long tree[mn2];

    void update(int x, long long v)
    {
        for(; x < mn2; x += (x & (-x)))
            tree[x] = max(tree[x], v);
    }

    long long get(int x)
    {
        long long re = 0;
        for(; x; x -= (x & (-x)))
            re = max(re, tree[x]);
        return re;
    }
} tPro, tVal;

void setup()
{
    while(cin >> a)
    {
        long long x = tPro.get(a - 1);
        ans = max(ans, x * a);
        long long v = tVal.get(a - 1);
        tPro.update(a, v * a);
        tVal.update(a, a);
    }
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
    freopen("PROD.INP", "r", stdin);
    freopen("PROD.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
