#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 100000000000000007ll
#define pb push_back
#define T first
#define A second.first
#define B second.second
#define mp make_pair

using namespace std;
typedef pair< long long , pair<long long, long long> > pizza;

struct line
{
    long long a, b;

    line(long long a = 0, long long b = 0): a(a), b(b) {}

    long long val(long long x)
    {
        return a * x + b;
    }

    double intersect(const line& x)
    {
        return 1.0 * (b - x.b) / (x.a - a);
    }
};
int n, b, r;
pizza p[mn];
line st[mn];
double rLim[mn];

void setup()
{
    cin >> n >> b;
    FOR(i, 1, n)
        cin >> p[i].T >> p[i].A >> p[i].B;
    sort(p + 1, p + n + 1);
}

long long getBest(int x)
{
    int lef = 0, rig = r;
    while(rig - lef > 1)
    {
        int mid = (lef + rig) >> 1;
        if (x <= rLim[mid])
            rig = mid;
        else
            lef = mid;
    }
    return st[rig].val(x);
}

void addLine(line& l)
{
    double x = l.intersect(st[r]);
    while(r && x <= rLim[r - 1])
        x = l.intersect(st[-- r]);
    st[++ r] = l;
    rLim[r - 1] = x;
    rLim[r] = maxC;
}

void xuly()
{
    st[r = 1] = line(0, 0);
    rLim[0] = -maxC, rLim[1] = maxC;
    long long sumA = 0;
    long long sumB = 0;
    long long sumBX = 0;
    long long ans;
    FOR(i, 1, n)
    {
        sumA += p[i].A;
        sumB += p[i].B;
        sumBX += p[i].B * p[i].T;
        ans = getBest(p[i].T) + sumA - p[i].T * sumB + sumBX - b;
        line l = line(sumB, ans - sumA - sumBX);
        addLine(l);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("VMPIZZA.INP", "r", stdin);
    freopen("VMPIZZA.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
