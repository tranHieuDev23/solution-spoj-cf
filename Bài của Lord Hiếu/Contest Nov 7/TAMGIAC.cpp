#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 900
#define mn2 30001
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn];

struct bitTree
{
    int tree[mn2];

    void update(int x)
    {
        for(; x < mn2; x += (x & (-x)))
            tree[x] ++;
    }

    int get(int x)
    {
        int re = 0;
        for(; x; x -= (x & (-x)))
            re += tree[x];
        return re;
    }
} t;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    memset(t.tree, 0, sizeof(t.tree));
}

void xuly()
{
    int ans = 0, numPair = 0;
    FOR(i, 2, n)
    {
        ans += numPair - t.get(a[i] - 1);
        numPair += i - 1;
        FOR(j, 1, i - 1)
            t.update(a[i] + a[j]);
    }
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("TAMGIAC.INP", "r", stdin);
    freopen("TAMGIAC.OUT", "w", stdout);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
