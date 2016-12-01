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
int n, w[mn], num[mn];
long long ans = 0;

void lastSubtask()
{
    FOR(i, 3, n)
        ans += (i - 1) - ((i - 1) & 1);
    cout << ans;
    exit(0);
}

void setup()
{
    cin >> n;
    if (n > 3000)
        lastSubtask();
    FOR(i, 1, n)
        cin >> w[i];
    sort(w + 1, w + n + 1);
    int r = 0, last = 1;
    FOR(i, 2, n + 1)
    if (w[i] != w[i - 1])
    {
        w[++ r] = w[i - 1];
        num[r] = i - last;
        last = i;
    }
    n = r;
}

void xuly()
{
    FOR(b, 3, n)
    {
        int id = b - 1;
        FOR(a, 1, b - 1)
        {
            int c = w[b] - w[a];
            if (c == w[a])
            {
                id = a;
                continue;
            }
            while(w[id] > c)
                id --;
            if (w[id] == c)
                ans += 1ll * num[a] * num[b] * num[id];
        }
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("QD.INP", "r", stdin);
    freopen("QD.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
