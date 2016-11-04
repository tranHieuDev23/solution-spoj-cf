#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 201
#define mn2 20004
#define maxC 1000000000
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, l, mem = 0, a[mn][mn2], pos[mn][mn2], r[mn];
int val[mn * mn2];
priority_queue< pair<int, int> > p;

void setup()
{
    cin >> n >> l;
    FOR(i, 1, n)
    {
        FOR(j, 1, l)
            cin >> a[i][j];
        p.push(mp(- a[i][1], i));
    }
}

void merging()
{
    while(!p.empty())
    {
        int u = p.top().S;
        int w = - p.top().F;
        p.pop();
        pos[u][++ r[u]] = ++ mem;
        val[mem] = w;
        if (r[u] == l)
            continue;
        p.push(mp(- a[u][r[u] + 1], u));
    }
}

int getNum(int x, int u)
{
    int lef = 0, rig = l + 1;
    while(rig - lef > 1)
    {
        int mid = ((rig + lef) >> 1);
        if (pos[u][mid] <= x)
            lef = mid;
        else
            rig = mid;
    }
    return lef;
}

int getAns(int x, int y)
{
    int lef = 0, rig = mem;
    while(rig - lef > 1)
    {
        int mid = ((lef + rig) >> 1);
        int num = getNum(mid, x) + getNum(mid, y);
        if (num < l)
            lef = mid;
        else
            rig = mid;
    }
    return val[rig];
}

void xuly()
{
    merging();
    long long ans = 0;
    FOR(i, 1, n - 1)
    FOR(j, i + 1, n)
        ans = (ans + getAns(i, j)) % maxC;
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
