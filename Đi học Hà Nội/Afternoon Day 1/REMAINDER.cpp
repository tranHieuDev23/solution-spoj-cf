#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
long long x, n, m, ten, power10;

long long add(long long a, long long const b)
{
    if ((a += b) >= m)
        a -= m;
    return a;
}

long long mul(long long const a, long long const b)
{
    if (b == 1)
        return a;
    long long z = mul(a, b >> 1);
    z = add(z, z);
    if (b & 1)
        z = add(z, a);
    return z;
}

long long Mul(long long const a, long long const b)
{
    if (b)
        return mul(a, b);
    return 0;
}

long long calc(long long x, long long n)
{
    if (n == 1)
        return x;
    long long z = calc(x, n >> 1);
    z = add(Mul(z, ten), z);
    ten = Mul(ten, ten);
    if (n & 1)
    {
        z = add(Mul(z, power10), x);
        ten = Mul(ten, power10);
    }
    return z;
}

long long calcPower10(long long x)
{
    long long re = 1;
    while(x)
        x /= 10, re *= 10;
    return re % m;
}

void setup()
{
    cin >> x >> n >> m;
    ten = power10 = calcPower10(x);
    cout << calc(x % m, n) << '\n';
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("REMAINDER.INP", "r", stdin);
    freopen("REMAINDER.OUT", "w", stdout);
    int t; cin >> t;
    while(t --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
