#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define mn2 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int ls, n, l, f[mn2];
char s[mn], a[mn2];

void setup()
{
    scanf("%d%d", &ls, &n);
    FOR(i, 1, ls)
        scanf(" %c", s + i);
}

void prepareKMP()
{
    f[0] = -1, f[1] = 0;
    int id = 0;
    FOR(i, 2, l)
    {
        while(id != -1 && a[i] != a[id + 1])
            id = f[id];
        f[i] = ++ id;
    }
}

void query()
{
    scanf("%d", &l);
    FOR(i, 1, l)
        scanf(" %c", a + i);
    prepareKMP();
    int id = 0, ans = 0;
    FOR(i, 1, ls)
    {
        while(id != -1 && s[i] != a[id + 1])
            id = f[id];
        if (++ id == l)
            ans ++, id = f[id];
    }
    printf("%d\n", ans);
}

void xuly()
{
    FOR(i, 1, n)
        query();
}

int main()
{
    freopen("STR01.INP", "r", stdin);
    freopen("STR01.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
