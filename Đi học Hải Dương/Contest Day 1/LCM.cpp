#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define sqrtmn 1003
#define mn2 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
vector<int> allP, fac[mn2];
bool notPrime[sqrtmn];
int n, num[mn], l, ans, wrong;

void prepare()
{
    notPrime[0] = notPrime[1] = true;
    FOR(i, 2, sqrtmn - 1)
    if (!notPrime[i])
    {
        for(int t = (i << 1); t < sqrtmn; t += i)
            notPrime[t] = true;
        allP.pb(i);
    }
}

void factoring(int x, int id)
{
    int sqt = sqrt(x);
    fac[id].clear();
    FOR(i, 0, int(allP.size()) - 1)
    {
        if (allP[i] > sqt)
            break;
        if (x % allP[i] == 0)
        {
            fac[id].pb(allP[i]);
            while(x % allP[i] == 0)
                x /= allP[i];
            sqt = sqrt(x);
        }
    }
    if (x != 1)
        fac[id].pb(x);
}

void add(int id)
{
    FOR(i, 0, int(fac[id].size()) - 1)
        wrong += (++ num[fac[id][i]] == 2);
}

void rem(int id)
{
    FOR(i, 0, int(fac[id].size()) - 1)
        wrong -= (-- num[fac[id][i]] == 1);
}

void deal(int r)
{
    int x; cin >> x;
    factoring(x, r);
    add(r);
    while(wrong)
        rem(l ++);
    ans = max(ans, r - l + 1);
}

void setup()
{
    cin >> n;
    l = ans = 1;
    wrong = 0;
    FOR(i, 1, n)
        deal(i);
    while(l <= n)
        rem(l ++);
    if (ans > 1)
        cout << ans << '\n';
    else
        cout << "-1\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("LCM.INP", "r", stdin);
    freopen("LCM.OUT", "w", stdout);
    prepare();
    int t; cin >> t;
    FOR(i, 1, t)
        setup ();
    return 0;
}
