#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)

using namespace std;
int n, h[mn];
long long sum, k;

void setup()
{
    cin >> n >> k;
    sum = 0;
    int r;
    FOR(i, 1, n)
    {
        cin >> h[i] >> r;
        sum += h[i];
    }
    if (sum < k)
    {
        cout << "-1\n";
        return;
    }
    sort(h + 1, h + n + 1, greater<int>());
    sum = 0;
    FOR(i, 1, n)
    if ((sum += h[i]) >= k)
    {
        cout << i << '\n';
        return;
    }
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("VOL.INP", "r", stdin);
    freopen("VOL.OUT", "w", stdout);
    int t; cin >> t;
    while(t --)
        setup ();
    xuly ();
    return 0;
}
