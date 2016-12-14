#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define lim 10004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
typedef unsigned long long ull;

struct linkedChar
{
    char c;
    int next;
    linkedChar(char c = 'A', int next = 0): c(c), next(next) {}
} all[mn];

string s, t;
int k, dem = 0, l[21], ans = maxC, con[mn][mn];
ull hashVal[mn][mn], power[mn], vaccine[21];
map<ull, int> mark;

int valChar(char c)
{
    if (c == 'A')
        return 1;
    if (c == 'C')
        return 2;
    if (c == 'G')
        return 3;
    return 4;
}

void setup()
{
    cin >> s >> k;

    power[0] = 1;
    FOR(i, 1, int(s.size()))
    {
        all[i] = linkedChar(s[i - 1], i + 1);
        power[i] = power[i - 1] * 7;
    }
    all[0].next = 1;
    all[s.size()].next = 0;

    FOR(i, 1, k)
    {
        cin >> t;
        l[i] = t.size();
        FOR(j, 0, l[i] - 1)
            vaccine[i] = vaccine[i] * 7 + valChar(t[j]);
    }
}

ull getHash(int l, int r, int h)
{
    return hashVal[r][h] - hashVal[l - 1][h] * power[r - l + 1];
}

void duyet(int h)
{
    if (++ dem == lim)
    {
        cout << ans;
        exit(0);
    }

    int siz = 0;
    for(int id = all[0].next; id; id = all[id].next)
    {
        con[++ siz][h] = id;
        hashVal[siz][h] = hashVal[siz - 1][h] * 7 + valChar(all[id].c);
    }
    if (siz == 0)
    {
        cout << 0;
        exit(0);
    }

    ans = min(ans, siz);
    con[0][h] = con[siz + 1][h] = 0;

    FOR(i, 1, k)
    FOR(u, l[i], siz)
    {
        ull get = getHash(u - l[i] + 1, u, h);
        if (get != vaccine[i])
            continue;
        ull newHash = hashVal[u - l[i]][h] * power[siz - u] + getHash(u + 1, siz, h);
        if (mark[newHash])
            continue;
        mark[newHash] = 1;

        int idL = con[u - l[i]][h], idR = con[u + 1][h];
        int old = all[idL].next;
        all[idL].next = idR;
        duyet(h + 1);
        all[idL].next = old;
    }
}

void xuly()
{
    duyet(0);
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("VIRUS.INP", "r", stdin);
    freopen("VIRUS.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
