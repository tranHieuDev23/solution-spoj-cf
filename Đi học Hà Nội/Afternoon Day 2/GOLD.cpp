#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define mid ((l + r) >> 1)
#define lc (id << 1)
#define rc (lc + 1)

using namespace std;
int n, l1, l2, ans = 0, dp[mn], deq[mn], l = 1, r = 1;

void readInt(int* x)
{
    *x = 0;
    char c;
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            return;
        *x = (*x) * 10 + (c - '0');
    }
}

void printInt(int x)
{
    bool okZero = false;
    for(int i = 1000000000; i; i /= 10)
    {
        int digit = x / i;
        x -= digit * i;
        if (digit)
        {
            putchar('0' + digit);
            okZero = true;
        }
        else if (okZero)
            putchar('0');
    }
}

void pushing(int id)
{
    deq[++ r] = id;
    while(dp[deq[l]] < dp[id])
        l ++;
}

void setup()
{
    readInt(&n);
    readInt(&l1);
    readInt(&l2);
    deq[r] = 0;
    int a;
    FOR(i, 1, n)
    {
        readInt(&a);
        while(l <= r && deq[l] < i - l2)
            l ++;
        if (i > l1)
            pushing(i - l1);
        dp[i] = dp[deq[l]] + a;
        ans = max(ans, dp[i]);
    }
    printInt(ans);
}

void xuly()
{

}

int main()
{
    freopen("GOLD.INP", "r", stdin);
    freopen("GOLD.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
