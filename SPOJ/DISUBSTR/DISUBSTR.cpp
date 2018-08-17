#include <bits/stdc++.h>
#define FOR(i, j, k) for(int i = j; i <= k; i ++)
#define FORD(i, j, k) for(int i = j; i >= k; i --)
#define maxC 1000000007
#define mn 1003
#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;
string s;
int n, group[mn][12], arr[mn];
int lcp[mn], pos[mn];
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
        arr[i] = suf[i].S;
}

void buildLCP()
{
    FOR(i, 0, n - 1)
        pos[arr[i]] = i;
    for(int i = 0, val = 0; i < n; i ++, val = max(0, val - 1))
    {
        if (pos[i] == n - 1)
        {
            val = 0;
            continue;
        }
        int j = arr[pos[i] + 1];
        while(i + val < n && j + val < n && s[i + val] == s[j + val])
            val ++;
        lcp[pos[i]] = val;
    }
}

void setup()
{
    cin >> s;
    n = s.size();
    buildSA();
    buildLCP();
}

void xuly()
{
    int ans = n - arr[0];
    FOR(i, 1, n - 1)
        ans += (n - arr[i]) - lcp[i - 1];
    cout << ans << '\n';
}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    while(t --)
    {
        setup();
        xuly();
    }
    return 0;
}
