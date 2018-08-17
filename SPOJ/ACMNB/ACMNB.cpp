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
int n, ans = 0;
vector<int> dif;

void setup()
{
    cin >> n;
    int a, b;
    FOR(i, 1, (n << 1))
    {
        cin >> a >> b;
        ans += a;
        dif.pb(b - a);
    }
    sort(dif.begin(), dif.end());
    FOR(i, 0, n - 1)
        ans += dif[i];
    cout << ans;
}

void xuly()
{

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
