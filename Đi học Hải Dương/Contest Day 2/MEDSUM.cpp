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
int n, l, mem = 0, a[mn][mn2], r[mn], num[mn], numNum[mn2];
int val[mn * mn2], id[mn * mn2];
priority_queue< pair<int, int> > p;

void setup()
{
    scanf("%d%d", &n, &l);
    FOR(i, 1, n)
    {
        FOR(j, 1, l)
            scanf("%d", &a[i][j]);
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
        r[u] ++, mem ++;
        val[mem] = w;
        id[mem] = u;
        if (r[u] == l)
            continue;
        p.push(mp(- a[u][r[u] + 1], u));
    }
}

void xuly()
{
    merging();
    long long ans = 0;
    numNum[0] = n;
    FOR(i, 1, mem)
    {
        int u = id[i];
        numNum[num[u]] --;
        num[u] ++;
        numNum[num[u]] ++;
        long long good = numNum[l - num[u]];
        if (num[u] == l - num[u])
            good --;
        ans += good * val[i];
    }
    ans = ((ans % maxC) + maxC) % maxC;
    printf("%I64d", ans);
}

int main()
{
    freopen("MEDSUM.INP", "r", stdin);
    freopen("MEDSUM.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
