#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 10004
#define mn2 30004
#define mn3 175
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
struct bitTree
{
    int tree[mn];

    void update(int x, int v)
    {
        for(; x < mn; x += (x & (-x)))
            tree[x] += v;
    }

    int get(int x)
    {
        int re = 0;
        for(; x; x -= (x & (-x)))
            re += tree[x];
        return re;
    }
} tree[mn3];
int n, q, a[mn2], belong[mn2], sz[mn3];

void setup()
{
    cin >> n;
    int sqt = sqrt(n);
    FOR(i, 1, n)
    {
        cin >> a[i];
        belong[i] = belong[i - 1] + (i % sqt == 1);
        tree[belong[i]].update(a[i], 1);
        sz[belong[i]] ++;
    }
    cin >> q;
}

void query0()
{
    int i, v;
    cin >> i >> v;
    tree[belong[i]].update(a[i], -1);
    a[i] = v;
    tree[belong[i]].update(a[i], 1);
}

void query1()
{
    int u, v, k, ans = 0;
    cin >> u >> v >> k;
    if (belong[u] == belong[v])
    {
        FOR(i, u, v)
            ans += (a[i] > k);
        cout << ans << '\n';
        return;
    }
    FOR(i, belong[u] + 1, belong[v] - 1)
        ans += sz[i] - tree[i].get(k);
    FOR(i, u, n)
    {
        if (belong[i] != belong[u])
            break;
        ans += (a[i] > k);
    }
    FORD(i, v, 1)
    {
        if (belong[i] != belong[v])
            break;
        ans += (a[i] > k);
    }
    cout << ans << '\n';
}

void xuly()
{
    int t;
    while(q --)
    {
        cin >> t;
        if (t == 0)
            query0();
        else
            query1();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    setup ();
    xuly ();
    return 0;
}
