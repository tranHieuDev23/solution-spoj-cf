#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, k;
long long h[mn], sumH[mn];

void setup()
{
    cin >> n >> k;
    FOR(i, 1, n)
        cin >> h[i];
    sort(h + 1, h + n + 1);
    FOR(i, 1, n)
        sumH[i] = sumH[i - 1] + h[i];
}

int high(long long k)
{
    int l = 1, r = n + 1;
    while(r - l > 1)
    {
        int g = (l + r) >> 1;
        long long cut = (sumH[n] - sumH[g - 1]) - h[g - 1] * (n - g + 1);
        if (cut >= k)
            l = g;
        else
            r = g;
    }

    long long sum = sumH[n] - sumH[l - 1];
    int length = n - l + 1;
    int lef = h[l - 1], rig = h[l];
    while(rig - lef > 1)
    {
        long long g = (lef + rig) >> 1;
        long long cut = sum - g * length;
        if (cut >= k)
            lef = g;
        else
            rig = g;
    }
    return lef;
}

void xuly()
{
    long long q;
    while(k --)
    {
        cin >> q;
        cout << high(q) << ' ';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SAW.INP", "r", stdin);
    freopen("SAW.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
