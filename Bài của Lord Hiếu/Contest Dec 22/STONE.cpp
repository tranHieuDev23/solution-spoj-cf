#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define mn2 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define bitPos(x) (1 << (x))

using namespace std;

int nextInt()
{
    char c = ' ';
    while(c == ' ' || c == '\n')
        c = getchar();
    int x = c - '0';
    while(true)
    {
        c = getchar();
        if (c == ' ' || c == '\n' || c == EOF)
            break;
        x = x * 10 + c - '0';
    }
    return x;
}

int m, n, k, v[mn];
int numRange = 0, sum[mn];
pair<int, int> range[mn2];

int getFirst(int const v, int const num)
{
    return v & (bitPos(num) - 1);
}

int getLast(int const v, int const num)
{
    return v & (-1 ^ (bitPos(8 - num) - 1));
}

void setup()
{
    m = nextInt(), n = nextInt(), k = nextInt();
    FOR(i, 1, m)
        v[i] = nextInt();
    int c, p, d, q;
    FOR(i, 1, n)
    {
        c = nextInt(), p = nextInt();
        d = nextInt(), q = nextInt();
        c ++, d ++;
        if (c + 1 <= d - 1)
            range[++ numRange] = mp(c + 1, d - 1);
        int firstC = getFirst(v[c], p + 1);
        int lastD = getLast(v[d], 8 - q);
        if (c == d)
            v[c] = firstC ^ lastD;
        else
        {
            v[c] ^= firstC;
            v[d] ^= lastD;
        }
    }
}

void prepare()
{
    sort(range + 1, range + numRange + 1);
    int id = 0;
    FOR(i, 1, numRange)
    {
        id = max(id, range[i].F - 1);
        while(id < range[i].S)
            v[++ id] = 0;
    }

    FOR(i, 1, m)
        sum[i] = sum[i - 1] + v[i];
}

bool query()
{
    int c, p, d, q;
    c = nextInt(), p = nextInt();
    d = nextInt(), q = nextInt();
    c ++, d ++;
    int firstC = getFirst(v[c], p + 1);
    int lastD = getLast(v[d], 8 - q);
    if (c == d)
        return firstC & lastD;
    if (c + 1 <= d - 1)
        if (sum[d - 1] - sum[c])
            return true;
    return firstC | lastD;
}

void xuly()
{
    prepare();
    while(k --)
        if (query())
            printf("YES\n");
        else
            printf("PASS\n");
}

int main()
{
    freopen("STONE.INP", "r", stdin);
    freopen("STONE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
