#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 502
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int c, n, m, order[5], r;
pair<int, int> card[mn];
pair<int, int> st[mn];

bool comp(pair<int, int>& a, pair<int, int>& b)
{
    if (a.F != b.F)
        return order[a.F] < order[b.F];
    return a.S <= b.S;
}

void setup()
{
    cin >> c >> n;
    m = c * n;
    FOR(i, 1, m)
        cin >> card[i].F >> card[i].S;
    FOR(i, 1, c)
        order[i] = i;
}

int binarySearch(pair<int, int> v)
{
    int lef = 0, rig = r + 1;
    while(rig - lef > 1)
    {
        int mid = (rig + lef) >> 1;
        if (comp(st[mid], v))
            lef = mid;
        else
            rig = mid;
    }
    return lef;
}

int calc()
{
    r = 0;
    int ret = 0;
    FOR(i, 1, m)
    {
        int lis = binarySearch(card[i]) + 1;
        ret = max(ret, lis);
        r = max(r, lis);
        st[lis] = card[i];
    }
    return m - ret;
}

void xuly()
{
    int ans = maxC;
    do
        ans = min(ans, calc());
    while (next_permutation(order + 1, order + c + 1));
    cout << ans;
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
