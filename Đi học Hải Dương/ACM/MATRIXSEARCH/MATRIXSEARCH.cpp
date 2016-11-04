#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1005
#define maxC 1000000007
#define pb push_back

using namespace std;
int n, m, q, a[mn][mn];

struct bitTree
{
    int tree[mn];

    void update(int x, int v)
    {
        for(; x <= m; x += (x & (-x)))
            tree[x] += v;
    }

    int get(int x)
    {
        int re = 0;
        for(; x; x -= (x & (-x)))
            re += tree[x];
        return re;
    }
} t[mn];

int val(int const x, int const y)
{
    return a[x][y] + t[x].get(y);
}

void query2()
{
    int x; cin >> x;
    int r = 1, c = m;
    while(c && r <= n)
    {
        int v = val(r, c);
        if (v == x)
        {
            cout << "Y\n";
            return;
        }
        if (v < x)
            r ++;
        else
            c --;
    }
    cout << "N\n";
}

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
    FOR(j, 1, m)
        cin >> a[i][j];
}

void xuly()
{
    cin >> q;
    int type, r, c, v;
    FOR(i, 1, q)
    {
        cin >> type;
        if (type == 2)
        {
            cin >> r >> c >> v;
            FOR(j, r, n)
                t[j].update(c, v);
        }
        else
            query2();
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MATRIXSEARCH.INP", "r", stdin);
    freopen("MATRIXSEARCH.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
