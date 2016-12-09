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
} tR[2], tC[2];
int n, q, lastR[mn], lastC[mn], color[mn];

void setup()
{
    cin >> n >> q;
    FOR(i, 1, n)
        lastR[i] = 1, lastC[i] = 2;
    tR[0].update(1, n);
    tC[0].update(2, n);
}

void query1(int id)
{
    int i; cin >> i >> color[id];
    tR[color[lastR[i]]].update(lastR[i], -1);
    lastR[i] = id;
    tR[color[lastR[i]]].update(lastR[i], 1);
}

void query2(int id)
{
    int i; cin >> i >> color[id];
    tC[color[lastC[i]]].update(lastC[i], -1);
    lastC[i] = id;
    tC[color[lastC[i]]].update(lastC[i], 1);
}

int query3()
{
    int i; cin >> i;
    int id = lastR[i], ret;
    if (color[id] == 0)
        ret = n - (tC[1].get(mn - 1) - tC[1].get(id));
    else
        ret = tC[0].get(mn - 1) - tC[0].get(id);
    return ret;
}

int query4()
{
    int i; cin >> i;
    int id = lastC[i], ret;
    if (color[id] == 0)
        ret = n - (tR[1].get(mn - 1) - tR[1].get(id));
    else
        ret = tR[0].get(mn - 1) - tR[0].get(id);
    return ret;
}

void xuly()
{
    int t;
    FOR(i, 3, q + 2)
    {
        cin >> t;
        if (t == 1)
            query1(i);
        if (t == 2)
            query2(i);
        if (t == 3)
            cout << query3() << '\n';
        if (t == 4)
            cout << query4() << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MBOARD.INP", "r", stdin);
    freopen("MBOARD.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
