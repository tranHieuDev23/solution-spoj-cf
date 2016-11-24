#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000000000ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int m;
long long n, a, b, p[mn], r;

void setup()
{
    cin >> n >> m >> a >> b;
    FOR(i, 1, m)
        cin >> p[i];
    sort(p + 1, p + m + 1);
}

long long bestR(long long u, long long x)
{
    long long stepLef = u - r;
    long long moveLef = (stepLef - 1) * a;
    long long digLeft = stepLef * b;
    long long costLeft = moveLef + digLeft;

    if (costLeft > x)
    {
        long long remainDig = x - moveLef;
        if (remainDig < b)
            return -1;
        return r + remainDig / b;
    }

    long long costRig = x - costLeft;
    long long stepRig = costRig / ((a << 1) + b);

    long long remainRig = x - costLeft - moveLef;
    if (remainRig < 0)
        return u + stepRig;

    long long moveRig = remainRig / (a + b);
    return u + max(stepRig, moveRig);
}

bool check(long long x)
{
    r = 0;
    FOR(i, 1, m)
    {
        int u = p[i];
        if (r >= u)
        {
            long long costToR = (r - u) * a;
            if (costToR <= x)
                r += (x - costToR) / (a + b);
        }
        else
        {
            r = bestR(u, x);
            if (r == -1)
                return false;
        }
        if (r >= n)
            return true;
    }
    return false;
}

void xuly()
{
    long long l = 0, r = maxC;
    while(r - l > 1)
    {
        long long g = ((l + r) >> 1);
        if (check(g))
            r = g;
        else
            l = g;
    }
    cout << r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("HOLES.INP", "r", stdin);
    freopen("HOLES.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
