#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define sqtmn 1003
#define mn2 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, a[mn2], big[mn], fac[mn][8], r[mn];
int num[mn], wrong, l, ans;

void prepare()
{
    FOR(i, 2, sqtmn - 1)
    if (!big[i])
    for(int t = i; t < mn; t += i)
        big[t] = i;
}

void factor(int x)
{
    if (r[x])
        return;
    int cur = x;
    while(big[cur])
    {
        if (big[cur] != fac[x][r[x]])
            fac[x][++ r[x]] = big[cur];
        cur /= big[cur];
    }
    if (cur != 1)
        fac[x][++ r[x]] = cur;
}

void add(int id)
{
    FOR(i, 1, r[a[id]])
        wrong += (++ num[fac[a[id]][i]] == 2);
}

void del(int id)
{
    FOR(i, 1, r[a[id]])
        wrong -= (-- num[fac[a[id]][i]] == 1);
}

void setup()
{
    scanf("%d", &n);
    l = 1;
    ans = 1;
    wrong = 0;
    FOR(r, 1, n)
    {
        scanf("%d", &a[r]);
        factor(a[r]);
        add(r);
        while(wrong)
            del(l ++);
        ans = max(ans, r - l + 1);
    }
    while(l <= n)
        del(l ++);
    if (ans == 1)
        printf("-1\n");
    else
        printf("%d\n", ans);

}

int main()
{
    freopen("LCM.INP", "r", stdin);
    freopen("LCM.OUT", "w", stdout);
    prepare();
    int t; scanf("%d", &t);
    FOR(i, 1, t)
        setup ();
    return 0;
}
