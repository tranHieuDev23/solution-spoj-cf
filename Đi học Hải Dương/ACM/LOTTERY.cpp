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
int n, k, r = 0, num[mn], a, b;
pair<int, int> p[mn];
map<int, int> Map;

void setup()
{
    cin >> n >> k;
    int x;
    FOR(i, 1, n)
    {
        cin >> x;
        if (Map[x] == 0)
        {
            Map[x] = ++ r;
            p[r].F = x;
        }
        p[Map[x]].S ++;
    }
    cin >> a >> b;
}

int firstToDivine(int a, int b)
{
    int x = a / b;
    return (x + (a % b != 0)) * b;
}

void xuly()
{
    FOR(i, 1, r)
    {
        int st = firstToDivine(a, p[i].F);
        for(; st <= b; st += p[i].F)
            num[st - a] += p[i].S;
    }
    int ans = 0;
    FOR(i, 0, b - a)
        ans += (num[i] == k);
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("LOTTERY.INP", "r", stdin);
    freopen("LOTTERY.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
