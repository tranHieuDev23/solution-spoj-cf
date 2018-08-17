#include<bits/stdc++.h>
#define FOR(i, j, k) for(int i = j; i <= k; i ++)
#define FORD(i, j, k) for(int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define mp make_pair

using namespace std;
const int NBIT = 18;
const int DEGREE = 1 << NBIT;
const double PI = acos(-1);
typedef complex<double> cplx;
cplx W[DEGREE];

int reverseBit(int mask)
{
    for(int i = 0, j = NBIT - 1; i < j; i ++, j --)
    if (((mask >> i) & 1) != ((mask >> j) & 1))
    {
        mask ^= 1 << i;
        mask ^= 1 << j;
    }
    return mask;
}

void fft(vector<cplx>& v, bool invert = false)
{
    v.resize(DEGREE);
    FOR(i, 0, DEGREE - 1)
    {
        int j = reverseBit(i);
        if (i < j)
            swap(v[i], v[j]);
    }
    vector<cplx> newV = vector<cplx>(DEGREE);
    for(int step = 1;  step < DEGREE; step <<= 1)
    {
        double angle = PI / step;
        if (invert)
            angle = -angle;
        W[0] = cplx(1);
        cplx wn = cplx(cos(angle), sin(angle));
        FOR(i, 1, step - 1)
            W[i] = W[i - 1] * wn;

        int startEven = 0;
        int startOdd = step;
        while(startEven < DEGREE)
        {
            FOR(i, 0, step - 1)
            {
                newV[startEven + i] = v[startEven + i] + W[i] * v[startOdd + i];
                newV[startOdd + i] = v[startEven + i] - W[i] * v[startOdd + i];
            }
            startEven += (step << 1);
            startOdd = startEven + step;
        }

        FOR(i, 0, DEGREE - 1)
            v[i] = newV[i];
    }
    if (invert)
        FOR(i, 0, DEGREE - 1)
            v[i] /= DEGREE;
}

int n;
vector<cplx> a, b;
const int offset = 50000;

void setup()
{
    cin >> n;
    a.resize(DEGREE);
    b.resize(DEGREE);
    int x;
    FOR(i, 1, n)
    {
        cin >> x;
        a[x + offset] += 1.0;
    }
    FOR(i, 1, n)
    {
        cin >> x;
        b[x + offset] += 1.0;
    }
}

void xuly()
{
    fft(a);
    fft(b);
    FOR(i, 0, DEGREE - 1)
        a[i] = a[i] * b[i];
    fft(a, true);
    int x;
    long long ans = 0;
    FOR(i, 1, n)
    {
        cin >> x;
        ans += round(a[x + offset * 2].real());
    }
    cout << ans << '\n';
}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    setup();
    xuly();
    return 0;
}