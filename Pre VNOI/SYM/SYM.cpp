#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;

struct TPoint
{
    int x, y;

    TPoint(int x = 0, int y = 0): x(x), y(y) {};

    bool operator == (const TPoint& a) const
    {
        return x == a.x && y == a.y;
    }

    bool operator < (const TPoint& a) const
    {
        if (x != a.x)
            return x < a.x;
        return y < a.y;
    }

    long long Distance(const TPoint& a)
    {
        return 1ll * (x - a.x) * (x - a.x) + 1ll * (y - a.y) * (y - a.y);
    }

    TPoint middlePoint(const TPoint& a)
    {
        return TPoint((x + a.x) >> 1, (y + a.y) >> 1);
    }
} point[mn];

typedef TPoint TVector;

int gcd(int a, int b)
{
    while(b)
    {
        int c = b;
        b = a % b;
        a = c;
    }
    return a;
}

void optimize(int& a, int& b)
{
    if (!a && !b)
        return;
    if (!a)
    {
        b = 1;
        return;
    }
    if (!b)
    {
        a = 1;
        return;
    }
    if (a < 0)
        a = -a, b = -b;
    int c = gcd(a, abs(b));
    a /= c, b /= c;
}

struct TLine
{
    int a, b, c;

    TLine(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {};

    TLine(const TPoint& vec, const TPoint& x)
    {
        a = vec.x, b = vec.y;
        optimize(a, b);
        c = - (a * x.x + b * x.y);
    }

    bool operator == (const TLine& x) const
    {
        return a == x.a && b == x.b && c == x.c;
    }

    bool operator < (const TLine& x) const
    {
        if (a != x.a) return a < x.a;
        if (b != x.b) return b < x.b;
            return c < x.c;
    }
};

TLine lineOver(const TPoint& x, const TPoint& y)
{
    TVector vec = TVector(y.y - x.y, x.x - y.x);
    return TLine(vec, x);
}

TLine middleLine(TPoint x, TPoint y)
{
    TVector vec = TVector(x.x - y.x, x.y - y.y);
    TPoint mid = x.middlePoint(y);
    return TLine(vec, mid);
}

int n, otherPoint[mn], id;
map<TPoint , int> numOne;
map<TPoint , int>::iterator it1;
map<TLine, int> numTwo, last, numLine;
map<TLine, int>::iterator it2;

bool comp(int a, int b)
{
    return point[id].Distance(point[a]) < point[id].Distance(point[b]);
}

void setup()
{
    cin >> n;
    if (n == 1)
    {
        cout << "0 0";
        exit(0);
    }
    FOR(i, 1, n)
    {
        cin >> point[i].x >> point[i].y;
        point[i].x <<= 1, point[i].y <<= 1;
        otherPoint[i] = i;
    }
}

int query1()
{
    TPoint temp;
    FOR(i, 1, n)
        numOne[point[i]] = 1;
    FOR(i, 1, n - 1)
    FOR(j, i + 1, n)
    {
        temp = point[i].middlePoint(point[j]);
        numOne[temp] += 2;
    }
    int best = 1;
    for(it1 = numOne.begin(); it1 != numOne.end(); it1 ++)
        best = max(best, (*it1).S);
    return n - best;
}

void preparePoint(int u)
{
    id = u;
    sort(otherPoint + 1, otherPoint + n + 1, comp);
    int l = 1;
    long long lastD = 0;
    FOR(i, 2, n)
    {
        int v = otherPoint[i];
        if (point[u].Distance(point[v]) != lastD)
            l = i, lastD = point[u].Distance(point[v]);
        FORD(j, i - 1, l)
        {
            int z = otherPoint[j];
            TLine line = middleLine(point[v], point[z]);
            if (!last[line])
                last[line] = u, numTwo[line] = 1;
            else if (last[line] != u)
                numTwo[line] = 0;
        }
    }
}

int calcNum(int x)
{
    return sqrt(x << 1) + 1;
}

void prepareLineOver()
{
    FOR(i, 1, n - 1)
    FOR(j, i + 1, n)
    {
        TLine line = lineOver(point[i], point[j]);
        numLine[line] ++;
    }
    for(it2 = numLine.begin(); it2 != numLine.end(); it2 ++)
        numTwo[(*it2).F] += calcNum((*it2).S);
}

int query2()
{
    FOR(u, 1, n)
        preparePoint(u);
    prepareLineOver();
    FOR(i, 1, n - 1)
    FOR(j, i + 1, n)
    {
        TLine line = middleLine(point[i], point[j]);
        numTwo[line] += 2;
    }
    int best = 0;
    for(it2 = numTwo.begin(); it2 != numTwo.end(); it2 ++)
        best = max(best, (*it2).S);
    return n - best;
}

void xuly()
{
    cout << query1() << ' ' << query2();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SYM.INP", "r", stdin);
    freopen("SYM.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
