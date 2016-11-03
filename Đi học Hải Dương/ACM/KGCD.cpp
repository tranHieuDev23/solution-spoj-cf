#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define maxC 1000000007
#define pb push_back

using namespace std;
int num[mn];
int n, k, maxVal = 0;

void setup()
{
    cin >> n >> k;
    int x;
    FOR(i, 1, n)
    {
        cin >> x;
        num[x] ++;
        maxVal = max(maxVal, x);
    }
    FORD(i, maxVal, 2)
    {
        int dem = 0;
        for(int t = i; t <= maxVal; t += i)
            if ((dem += num[t]) >= k)
            {
                cout << i;
                return;
            }
    }
    cout << 1;
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("KGCD.INP", "r", stdin);
    freopen("KGCD.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
