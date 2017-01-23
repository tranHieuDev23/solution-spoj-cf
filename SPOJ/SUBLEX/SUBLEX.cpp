#include <bits/stdc++.h>
#define FOR(i, j, k) for(int i = j; i <= k; i ++)
#define FORD(i, j, k) for(int i = j; i >= k; i --)
#define maxC 1000000007
#define mn 90004
#define pb push_back
#define mp make_pair
#define F first
#define S second

using namespace std;
string s;
int n, q, group[mn][18];
int sa[mn], pos[mn], lcp[mn];
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
            val = 0;
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
    cin >> s >> q;
    n = s.size();
    buildSA();
    buildLCP();
}

pair<int, int> query(int x)
{
    int depth = 0;
    FOR(i, 0, n - 1)
    {
        if (i)
            depth = lcp[i - 1];
        x --;
        int length = n - sa[i];
        int remain = length - depth - 1;
        if (x > remain)
            x -= remain;
        else
            return mp(sa[i], sa[i] + depth + x);
    }
    return mp(0, -1);
}

void xuly()
{
    int k;
    while(q --)
    {
        cin >> k;
        pair<int, int> ans = query(k);
        FOR(i, ans.F, ans.S)
            cout << s[i];
        cout << '\n';
    }
}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("FILE.INP", "r", stdin);
    freopen("FILE.OUT", "w", stdout);
    setup();
    xuly();
    return 0;
}
