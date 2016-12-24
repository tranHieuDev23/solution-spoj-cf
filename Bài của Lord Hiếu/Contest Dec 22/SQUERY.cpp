#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 50004
#define mn2 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, sqt, q, a[mn], belong[mn], st[mn2], ed[mn2];
int num[mn2][mn], temp[mn];
long long sameMem[mn][mn2], sameGroup[mn2][mn2];

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> a[i];
    cin >> q;
}

void prepare()
{
    sqt = max(n / 1000, 2);
    FOR(i, 1, n)
    {
        if (i % sqt == 1)
        {
            belong[i] = belong[i - 1] + 1;
            st[belong[i]] = i;
        }
        else
            belong[i] = belong[i - 1];
        ed[belong[i]] = i;
        num[belong[i]][a[i]] ++;
    }

    FOR(i, 1, n)
    FOR(j, 1, belong[n])
    {
        sameMem[i][j] = num[j][a[i]];
        sameGroup[belong[i]][j] += sameMem[i][j];
        sameMem[i][j] += sameMem[i][j - 1];
    }

    FOR(i, 1, belong[n])
    FOR(j, 1, belong[n])
        sameGroup[i][j] += sameGroup[i - 1][j] + sameGroup[i][j - 1] - sameGroup[i - 1][j - 1];
}

long long query()
{
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    long long ret = 0;
    int gl1 = belong[l1], gr1 = belong[r1], gl2 = belong[l2], gr2 = belong[r2];

    if (gl1 == gr1 && gl2 == gr2)
    {
        FOR(i, l1, r1)
            temp[a[i]] ++;
        FOR(i, l2, r2)
            ret += temp[a[i]];
        FOR(i, l1, r1)
            temp[a[i]] --;
        return ret;
    }

    if (gl2 == gr2)
        swap(l1, l2), swap(r1, r2);

    FOR(i, l2, ed[gl2])
        temp[a[i]] ++;
    FOR(i, st[gr2], r2)
        temp[a[i]] ++;

    if (gl1 == gr1)
    FOR(i, l1, r1)
        ret += sameMem[i][gr2 - 1] - sameMem[i][gl2] + temp[a[i]];
    else
    {
        ret = sameGroup[gr1 - 1][gr2 - 1] - sameGroup[gl1][gr2 - 1] - sameGroup[gr1 - 1][gl2] + sameGroup[gl1][gl2];
        FOR(i, l1, ed[gl1])
            ret += sameMem[i][gr2 - 1] - sameMem[i][gl2] + temp[a[i]];
        FOR(i, st[gr1], r1)
            ret += sameMem[i][gr2 - 1] - sameMem[i][gl2] + temp[a[i]];
    }

    FOR(i, l2, ed[gl2])
        temp[a[i]] --;
    FOR(i, st[gr2], r2)
        temp[a[i]] --;

    return ret;
}

void xuly()
{
    while(q --)
        cout << query() << '\n';
}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SQUERY.INP", "r", stdin);
    freopen("SQUERY.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
