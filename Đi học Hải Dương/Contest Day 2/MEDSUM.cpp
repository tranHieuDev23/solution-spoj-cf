#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 4000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, l, rig = 0, a[201][20001], pos[201][20001], r[201];
int val[mn];
priority_queue< pair<int, int> > p;

void setup()
{
    cin >> n >> l;
    FOR(i, 1, n)
    FOR(j, 1, l)
        cin >> a[i][j];
}

void merging()
{
    FOR(i, 1, n)
        p.push(mp(- a[i][1], i)), r[i] = 1;
    while(!p.empty())
    {
        int w = - p.top().F;
        int u = p.top().S;
        p.pop();
        val[++ rig] = w;
        pos[u][r[u]] = rig;
        if (++ r[u] <= l)
            p.push(mp(- a[u][r[u]], u));
    }
}

int notGreat(int id, int x)
{
    int le = 0, ri = l + 1;
    while(ri - le > 1)
    {
        int mi = ((ri + le) >> 1);
        if (pos[id][mi] <= x)
            le = mi;
        else
            ri = mi;
    }
    return le;
}

int med(int x, int y)
{
    int le = 0, ri = rig;
    while(ri - le > 1)
    {
        int mi = ((ri + le) >> 1);
        int in = notGreat(x, mi) + notGreat(y, mi);
        if (in < l)
            le = mi;
        else
            ri = mi;
    }
    return val[ri];
}

void xuly()
{
    merging();
    long long ans = 0;
    FOR(i, 1, n - 1)
    FOR(j, i + 1, n)
        ans += med(i, j);
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MEDSUM.INP", "r", stdin);
    freopen("MEDSUM.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
