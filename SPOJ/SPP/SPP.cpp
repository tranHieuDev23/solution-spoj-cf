#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 20
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int k, b[mn], c[mn];
long long m, n, p, sumB[mn];

long long add(const long long a, const long long b)
{
    return (a + b) % p;
}

long long mul(const long long a, const long long b)
{
    return (a * b) % p;
}

struct matrix
{
    int m, n;
    long long a[mn][mn];

    matrix(int m = 0, int n = 0): m(m), n(n)
    {
        FOR(i, 1, m)
        FOR(j, 1, n)
            a[i][j] = 0;
    }

    matrix operator * (const matrix& x) const
    {
        matrix re = matrix(m, x.n);
        FOR(i, 1, re.m)
        FOR(j, 1, re.n)
        FOR(k, 1, n)
            re.a[i][j] = add(re.a[i][j], mul(a[i][k], x.a[k][j]));
        return re;
    }
} multiplier, base;

matrix power(matrix& a, long long b)
{
    if (b == 1)
        return a;
    matrix z = power(a, b >> 1);
    z = z * z;
    if (b & 1)
        z = z * a;
    return z;
}

void setup()
{
    cin >> k;
    FOR(i, 1, k)
    {
        cin >> b[i];
        sumB[i] = sumB[i - 1] + b[i];
    }
    FOR(i, 1, k)
        cin >> c[i];
    cin >> m >> n >> p;
}

long long calcSumB(long long x)
{
    multiplier = matrix(k + 1, k + 1);
    FOR(i, 1, k - 1)
        multiplier.a[i][i + 1] = 1;
    FOR(i, 1, k)
        multiplier.a[k][k + 1 - i] = multiplier.a[k + 1][k + 1 - i] = c[i] % p;
    multiplier.a[k + 1][k + 1] = 1;
    multiplier = power(multiplier, x - k);

    base = matrix(k + 1, 1);
    FOR(i, 1, k)
        base.a[i][1] = b[i] % p;
    base.a[k + 1][1] = sumB[k] % p;

    base = multiplier * base;
    return base.a[k + 1][1];
}

void xuly()
{
    long long sumBM, sumBN;
    if (m - 1 <= k)
        sumBM = sumB[m - 1] % p;
    else
        sumBM = calcSumB(m - 1);
    if (n <= k)
        sumBN = sumB[n] % p;
    else
        sumBN = calcSumB(n);
    long long ans = (sumBN - sumBM) % p;
    ans = (ans + p) % p;
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int c; cin >> c;
    while(c --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
