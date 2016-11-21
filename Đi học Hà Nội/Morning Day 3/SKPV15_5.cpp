#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define maxC 1000000009
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int m, n, k, prime[mn], facA[mn], facB[mn];
long long ans = 1;

void prepare()
{
    FOR(i, 2, mn - 1)
    if (!prime[i])
        for(int t = i; t < mn; t += i)
            prime[t] = i;
}

void scanVal(int* fac)
{
    int x; cin >> x;
    while(prime[x])
    {
        fac[prime[x]] ++;
        x /= prime[x];
    }
}

void setup()
{
    prepare();
    cin >> m >> n >> k;
    FOR(i, 1, m)
        scanVal(facA);
    FOR(i, 1, n)
        scanVal(facB);
}

long long power(long long a, int b)
{
    if (a <= 0)
        return 0;
    long long re = 1;
    while(b)
    {
        if (b & 1)
            re = (re * a) % maxC;
        a = (a * a) % maxC;
        b >>= 1;
    }
    return re;
}

long long add(long long const a, long long const b)
{
    long long re = (a + b) % maxC;
    return (re + maxC) % maxC;
}

void xuly()
{
    FOR(i, 2, mn - 1)
    {
        if (facA[i] > facB[i])
        {
            cout << 0;
            return;
        }
        if (facA[i] < facB[i])
        {
            if (k < 2)
            {
                cout << 0;
                return;
            }
            long long wayAll = power(facB[i] - facA[i] + 1, k);
            long long wayBad = add(power(facB[i] - facA[i], k) << 1, - power(facB[i] - facA[i] - 1, k));
            ans = (ans * add(wayAll, - wayBad)) % maxC;
        }
    }
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
