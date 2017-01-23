#include <bits/stdc++.h>
#define FOR(i, j, k) for(int i = j; i <= k; i ++)
#define FORD(i, j, k) for(int i = j; i >= k; i --)
#define maxC 1000000007
#define mn 100005
#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;
int n, k, group[mn][20];
int sa[mn], pos[mn], lcp[mn];
char s[mn];
pair< pair<int, int> , int > suf[mn];

void buildSA()
{
    FOR(i, 0, n - 1)
        group[i][0] = s[i];
    for(int cnt = 1, step = 1; (cnt >> 1) < n; cnt <<= 1, step ++)
    {
        FOR(i, 0, n - 1)
        {
            suf[i].F.F = group[i][step - 1];
            suf[i].F.S = i + cnt < n? group[i + cnt][step - 1] : -1;
            suf[i].S = i;
        }
        sort(suf, suf + n);
        FOR(i, 0, n - 1)
        {
            if (i && suf[i].F == suf[i - 1].F)
                group[suf[i].S][step] = group[suf[i - 1].S][step];
            else
                group[suf[i].S][step] = i;
        }
    }
    FOR(i, 0, n - 1)
        sa[i] = suf[i].S;
}

void buildLCP()
{
    FOR(i, 0, n - 1)
        pos[sa[i]] = i;
    for(int i = 0, val = 0; i < n; i ++, val = max(val - 1, 0))
    {
        if (pos[i] == n - 1)
        {
            lcp[n - 1] = val = 0;
            continue;
        }
        int j = sa[pos[i] + 1];
        while(i + val < n && j + val < n && s[i + val] == s[j + val])
            val ++;
        lcp[pos[i]] = val;
    }
}

void setup()
{
    scanf("%d%d%s", &n, &k, s);
    buildSA();
    buildLCP();
}

void xuly()
{
    int ans = 0;
    FOR(i, 0, n - 1)
    {
        int length = n - sa[i];
        ans += (length >= k && lcp[i] < k);
    }
    printf("%d\n", ans);
}

int main()
{
    int t; scanf("%d", &t);
    while(t --)
    {
        setup();
        xuly();
    }
    return 0;
}
