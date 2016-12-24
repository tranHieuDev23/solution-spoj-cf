#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 50004
#define mn2 230
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn];

void setup()
{
    int t; cin >> t;
    FOR(q, 1, t)
    {
        cin >> n;
        FOR(i, 1, n)
            cin >> a[i];
        cout << "Case #" << q << ": " << min(a[1], a[n]) << '\n';
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
    freopen("NEGGAME.INP", "r", stdin);
    freopen("NEGGAME.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
