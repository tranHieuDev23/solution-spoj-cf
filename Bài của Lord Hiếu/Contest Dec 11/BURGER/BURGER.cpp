#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define bitPos(x, i) ((x >> i) & 1)

using namespace std;

int add(int const a, int const b)
{
    int re = a + b;
    if (re >= maxC)
        re -= maxC;
    return re;
}

int n, k, xorA[mn], low[mn], high[mn];
int dp[mn][2], cur = 1, pre = 0;

struct trie
{
    int sum;
    trie* child[2];

    trie()
    {
        sum = 0;
        child[0] = child[1] = NULL;
    }

    void clear()
    {
        sum = 0;
        FOR(i, 0, 1)
        if (child[i] != NULL)
            child[i] -> clear();
    }
} t;

void setup()
{
    cin >> n >> k;
    FOR(i, 1, n)
    {
        cin >> xorA[i];
        xorA[i] ^= xorA[i - 1];
    }
    FOR(i, 1, k)
        cin >> low[i] >> high[i];
}

void prepare()
{
    FOR(i, 0, n - 1)
    {
        trie* p = &t;
        FORD(j, 31, 0)
        {
            int z = bitPos(xorA[i], j);
            if (p -> child[z] == NULL)
                p -> child[z] = new trie();
            p = p -> child[z];
        }
    }
}

void update(int Xor, int val)
{
    trie* p = &t;
    FORD(i, 31, 0)
    {
        p = p -> child[bitPos(Xor, i)];
        p -> sum = add(p -> sum, val);
    }
}

int getLow(int u, int Xor, int pos, trie* p)
{
    int ret = 0;
    FORD(i, pos - 1, -1)
    {
        if (i == -1)
        {
            ret = add(ret, p -> sum);
            break;
        }

        int z = bitPos(Xor, i);
        int x = bitPos(low[u], i);

        if (x == 0)
            if (p -> child[z ^ 1] != NULL)
                ret = add(ret, p -> child[z ^ 1] -> sum);

        if (p -> child[z ^ x] == NULL)
            break;
        p = p -> child[z ^ x];
    }
    return ret;
}

int getHigh(int u, int Xor, int pos, trie* p)
{
    int ret = 0;
    FORD(i, pos - 1, -1)
    {
        if (i == -1)
        {
            ret = add(ret, p -> sum);
            break;
        }

        int z = bitPos(Xor, i);
        int x = bitPos(high[u], i);

        if (x == 1)
            if (p -> child[z ^ 0] != NULL)
                ret = add(ret, p -> child[z ^ 0] -> sum);

        if (p -> child[z ^ x] == NULL)
            break;
        p = p -> child[z ^ x];
    }
    return ret;
}

int getSumDp(int u, int Xor)
{
    trie* p = &t;
    FORD(i, 31, 0)
    {
        int z = bitPos(Xor, i);
        int x = bitPos(low[u], i);
        int y = bitPos(high[u], i);
        if (x == y)
        {
            z ^= x;
            if (p -> child[z] == NULL)
                return 0;
            p = p -> child[z];
        }
        else
        {
            int ret = 0;
            if (p -> child[z ^ 0] != NULL)
                ret = add(ret, getLow(u, Xor, i, p -> child[z ^ 0]));
            if (p -> child[z ^ 1] != NULL)
                ret = add(ret, getHigh(u, Xor, i, p -> child[z ^ 1]));
            return ret;
        }
    }
    return p -> sum;
}

void xuly()
{
    prepare();
    dp[0][cur] = 1;
    FOR(j, 1, k)
    {
        t.clear();
        swap(cur, pre);
        dp[0][cur] = 0;
        FOR(i, 1, n)
        {
            update(xorA[i - 1], dp[i - 1][pre]);
            dp[i][cur] = getSumDp(j, xorA[i]);
        }
    }
    cout << dp[n][cur];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("BURGER.INP", "r", stdin);
    freopen("BURGER.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
