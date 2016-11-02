#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 30004
#define maxC 1000000070000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, h[mn];
long long sl[mn], sr[mn], sumUp[mn], sumDown[mn], ans = maxC;
vector<int> allP;
bool notP[mn], good[mn], good2[mn];

void prepare()
{
    notP[0] = notP[1] = true;
    FOR(i, 2, n)
    if (!notP[i])
    {
        for(int t = (i << 1); t <= n; t += i)
            notP[t] = true;
        allP.pb(i);
        if (!notP[i - 2])
        {
            good[i - 2] = true;
            if (!notP[i - 4])
                good2[i - 4] = true;
        }
    }
    FOR(i, 1, n)
    {
        sl[i] = sl[i - 1] + h[i];
        sumUp[i] = sumUp[i - 1] + sl[i];
    }
    FORD(i, n, 1)
    {
        sr[i] = sr[i + 1] + h[i];
        sumDown[i] = sumDown[i + 1] + sr[i];
    }
}

long long toL(int l, int r)
{
    return sumDown[l] - sumDown[r + 1] - sr[r + 1] * (r - l + 1);
}

long long toR(int l, int r)
{
    return sumUp[r] - sumUp[l - 1] - sl[l - 1] * (r - l + 1);
}
void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> h[i];
    prepare();
}

void check(int l, int r, int p)
{
    int g = ((l + r) >> 1);
    long long share = toL(l + 1, g) + toR(g + 1, r - 1);
    long long leftL = toR(1, l - 1);
    long long righR = toL(r + 1, n);
    ans = min(ans, leftL + share + righR);
    if (!good[p])
        return;
    int idL = l - 2, idR = r + 2;
    long long leftLId = (idL > 0? toR(1, idL - 1) : maxC);
    long long righRId = (idR <= n? toL(idR + 1, n) : maxC);
    ans = min(ans, leftLId + h[l - 1] + share + righR);
    ans = min(ans, leftL + share + h[r + 1] + righRId);
    if (!good2[p])
        return;
    ans = min(ans, leftLId + h[l - 1] + share + h[r + 1] + righRId);
}

void xuly()
{
    FOR(i, 1, n)
    {
        ans = min(ans, toR(1, i - 1) + toL(i + 1, n));
        FOR(j, 0, int(allP.size()) - 1)
        {
            int id = i + allP[j];
            if (id > n)
                break;
            check(i, id, allP[j]);
        }
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("MOUNTAIN.INP", "r", stdin);
    freopen("MOUNTAIN.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
