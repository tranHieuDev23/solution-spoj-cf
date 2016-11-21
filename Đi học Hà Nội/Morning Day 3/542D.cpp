#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 6800
#define mn2 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define szDiv (int(Div.size()))

using namespace std;
long long a;
vector< pair< long long, int> > pFac;
vector<long long> Div, Pri;
int szPri = 0;
vector<int> dp[mn], sumDp[mn];
map<long long, int> Map;
bool notP[mn2];

void factorize(long long x)
{
    long long sqt = sqrt(x);
    FOR(i, 2, sqt)
    if (x % i == 0)
    {
        pFac.pb(mp(i, 0));
        while(x % i == 0)
            x /= i, pFac[pFac.size() - 1].S ++;
        sqt = sqrt(x);
    }
    if (x != 1)
        pFac.pb(mp(x, 1));
}

void buildDiv(long long cur, int u)
{
    if (u == int(pFac.size()))
    {
        Div.pb(cur);
        return;
    }
    FOR(i, 0, pFac[u].S)
    {
        buildDiv(cur, u + 1);
        cur *= pFac[u].F;
    }
}

bool isPrime(long long x)
{
    if (x == 0 || x == 1)
        return false;
    long long sqt = sqrt(x);
    FOR(i, 2, sqt)
    if (x % i == 0)
        return false;
    return true;
}

void buildPri()
{
    Pri.resize(szDiv);
    FOR(i, 0, szDiv - 1)
        Map[Div[i]] = i + 1;

    long long sqt = sqrt(a), last = 0;

    FOR(i, 2, sqt)
    if (!notP[i])
    {
        for(int t = (i << 1); t <= sqt; t += i)
            notP[t] = true;
        long long val = i;
        while(val + 1 <= a)
        {
            if (int id = Map[val + 1])
            {
                if (last != i)
                    last = i, szPri ++;
                Pri[id - 1] = szPri;
            }
            val *= i;
        }
    }

    FOR(i, 0, szDiv - 1)
    if (!Pri[i])
    if (isPrime(Div[i] - 1))
    {
        if (last != Div[i] - 1)
            last = Div[i] - 1, szPri ++;
        Pri[i] = szPri;
    }
}

void setup()
{
    cin >> a;
    factorize(a);
    buildDiv(1, 0);
    sort(Div.begin(), Div.end());
    buildPri();
}

void xuly()
{
    sumDp[0].resize(szPri + 1);
    FOR(i, 0, szPri)
        sumDp[0][i] = 1;
    FOR(i, 0, szDiv - 1)
    {
        dp[i].resize(szPri + 1);
        sumDp[i].resize(szPri + 1);
        int id = szDiv - 1;
        FOR(j, 0, i)
        if (Pri[j] && Div[i] % Div[j] == 0)
        {
            long long Rem = Div[i] / Div[j];
            while(Rem < Div[id])
                id --;
            dp[i][Pri[j]] += sumDp[id][Pri[j] - 1];
        }

        FOR(j, 1, szPri)
            sumDp[i][j] = sumDp[i][j - 1] + dp[i][j];
    }
    cout << sumDp[szDiv - 1][szPri];
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
