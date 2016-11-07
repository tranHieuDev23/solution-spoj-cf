#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 500005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, len[mn], r;
long long sumL[mn], m;
pair<int, long long> best;

struct bitTree
{
    int tree[mn];

    void update(int x, int v)
    {
        for(; x <= n; x += (x & (-x)))
            tree[x] = min(tree[x], v);
    }

    int get(int x)
    {
        int re = maxC;
        for(; x; x -= (x & (-x)))
            re = min(re, tree[x]);
        return re;
    }
} t;


void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
    {
        cin >> len[i];
        sumL[i] = sumL[i - 1] + len[i];
    }
    memset(t.tree, 60, sizeof(int) * (n + 1));
}

long long cost(int l, int r)
{
    long long sum = sumL[r] - sumL[l - 1];
    long long aft = 1ll * t.get(r) * (r - l + 1);
    return sum - aft;
}

void xuly()
{
    best = mp(1, 0), r = n;
    FORD(l, n, 1)
    {
        t.update(l, len[l]);
        long long curCost = cost(l, r);
        while(curCost > m)
            curCost = cost(l, -- r);
        best = max(best, mp(r - l + 1, - curCost));
    }
    cout << best.F << ' ' << - best.S << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("NAILS.INP", "r", stdin);
    freopen("NAILS.OUT", "w", stdout);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
