#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100050
#define maxC 100000
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn];
long long sumA = 0, sumE = 0, ans = 0;
char s[6];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> a[i];
        sumA += a[i];
    }
}

void linking()
{
    sort(a + 1, a + n + 1);
    for(int l = 2, r = n - 1; l < r; l += 2, r -= 2)
        swap(a[l], a[r]);
    FOR(i, 1, n - 1)
        sumE += 1ll * a[i] * a[i + 1];
    sumE += 1ll * a[n] * a[1];
    sumE %= maxC;
}

void calcAns()
{
    int odd = 0;
    FOR(i, 1, n)
    {
        long long add = (sumA - a[i]) * a[i];
        odd += add & 1;
        ans = (ans + (add >> 1)) % maxC;
    }
    ans = (ans + (odd >> 1)) % maxC;
    ans = (ans + maxC - sumE) % maxC;
}

void xuly()
{
    linking();
    calcAns();
    FOR(i, 1, 5)
    {
        s[i] = '0' + ans % 10;
        ans /= 10;
    }
    FORD(i, 5, 1)
        cout << s[i];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("NUMPOLY.INP", "r", stdin);
    freopen("NUMPOLY.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
