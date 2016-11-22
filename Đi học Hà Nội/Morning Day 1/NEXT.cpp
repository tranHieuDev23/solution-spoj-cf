#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 52
#define maxC 1000000000000000ll
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define bit(x) (1ll << (x))
#define isOne(x, y) (((x) >> (y)) & 1)

using namespace std;
long long x, k, c[mn][mn], bigger[mn], ans;
int numBit;

void setup()
{
    FOR(i, 0, mn - 1)
    {
        c[0][i] = c[i][i] = 1;
        FOR(j, 1, i - 1)
            c[j][i] = c[j - 1][i - 1] + c[j][i - 1];
    }
}

void prepare()
{
    bigger[0] = 0;
    numBit = isOne(x, 0);
    FOR(i, 1, mn - 1)
    if (isOne(x, i))
        bigger[i] = bigger[i - 1] + c[++ numBit][i];
    else
        bigger[i] = bigger[i - 1];
}

void calcAns()
{
    ans = 0;
    bool ok = false;
    long long dif = 0;

    FORD(i, mn - 1, 0)
    {
        if (!ok)
        {
            if (isOne(x, i))
                ans |= bit(i), numBit --;
            else
            {
                long long ifOne = c[numBit][i];
                dif = ifOne - bigger[i];
                if (dif <= k)
                {
                    ans |= bit(i);
                    numBit --;
                    ok = true;
                }
            }
        }
        else
        {
            long long ifOne = c[numBit][i];
            if (dif + ifOne <= k)
                ans |= bit(i), numBit --, dif += ifOne;
        }
        if (!numBit)
            break;
    }
    if (!ok || ans > maxC)
        ans = -1;
}


void xuly()
{
    cin >> x >> k;
    prepare();
    calcAns();
    cout << ans << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("NEXT.INP", "r", stdin);
    freopen("NEXT.OUT", "w", stdout);
    setup ();
    int t; cin >> t;
    while(t --)
        xuly ();
    return 0;
}
