#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 100000000000ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m;
long long h[mn], p[mn];

void setup()
{
    cin >> n >> m;
    FOR(i, 1, n)
        cin >> h[i];
    FOR(i, 1, m)
        cin >> p[i];
}

bool check(long long t)
{
    int rig = m;
    FORD(i, n, 1)
    {
        if (p[rig] <= h[i])
        {
            while(rig && h[i] - p[rig] <= t)
                rig --;
        }
        else
        {
            if (p[rig] - h[i] > t)
                return false;
            long long leftFirst = max(p[rig] + h[i] - t + 1, 0ll) >> 1;
            long long rightFirst = (p[rig] << 1) - h[i] - t;
            long long downLim = min(leftFirst, rightFirst);
            while(rig && p[rig] >= downLim)
                rig --;
        }
        if (!rig)
            return true;
    }
    return false;
}

void xuly()
{
    long long l = -1, r = maxC;
    while(r - l > 1)
    {
        long long g = ((l + r) >> 1);
        if (check(g))
            r = g;
        else
            l = g;
    }
    cout << r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("READTIME.INP", "r", stdin);
    freopen("READTIME.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
