#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 702
#define mn2 2003
#define maxC 30103
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn], ans = 0;

int add(int& a, int const b)
{
    if ((a += b) >= maxC)
        a -= maxC;
    return a;
}

struct bitTree
{
    int tree[mn][mn2];

    void update(int x, int y, int v)
    {
        for(; x <= n; x += (x & (-x)))
        for(int z = y; z <= mn2; z += (z & (-z)))
            add(tree[x][z], v);
    }

    int get(int x, int y)
    {
        int re = 0;
        for(; x; x -= (x & (-x)))
        for(int z = y; z; z -= (z & (-z)))
            add(re, tree[x][z]);
        return re;
    }
} t;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    FORD(i, n - 1, 1)
    FORD(j, n, i + 1)
    {
        int way = t.get(j - 1, a[i] + a[j] - 1);
        add(ans, way);
        t.update(j, a[i] + a[j], add(way, 1));
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
    freopen("SEQ2015.INP", "r", stdin);
    freopen("SEQ2015.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
