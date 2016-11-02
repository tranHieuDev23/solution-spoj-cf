#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define base 29

using namespace std;
string s, t;
int n, m;
long long hashValS[mn], hashValV[mn], po[mn];

void buildHash(string& s, int& sz, long long* hashVal)
{
    sz = s.size();
    FOR(i, 1, sz)
        hashVal[i] = (hashVal[i - 1] * base + s[i - 1] - 'a') % maxC;
}

int gcd(int a, int b)
{
    if (b)
        return gcd(b, a % b);
    return a;
}

long long getHashVal(long long* hashVal, int l, int r)
{
    long long re = (hashVal[r] - hashVal[l - 1] * po[r - l + 1]) % maxC;
    return (re + maxC) % maxC;
}

bool check(int sz, int x, long long* hashVal, long long baseV)
{
    int l = 1, r = x;
    while(l <= sz)
    {
        if (getHashVal(hashVal, l, r) != baseV)
            return false;
        l = r + 1;
        r = l + x - 1;
    }
    return true;
}

void setup()
{
    cin >> s >> t;
    buildHash(s, n, hashValS);
    buildHash(t, m, hashValV);
    int x = gcd(n, m);
    po[0] = 1;
    FOR(i, 1, x)
        po[i] = (po[i - 1] * base) % maxC;
    long long baseVal = getHashVal(hashValS, 1, x);
    if (!check(n, x, hashValS, baseVal))
    {
        cout << "NO";
        return;
    }
    if (!check(m, x, hashValV, baseVal))
    {
        cout << "NO";
        return;
    }
    cout << s.substr(0, x);
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("BASESTRING.INP", "r", stdin);
    freopen("BASESTRING.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
