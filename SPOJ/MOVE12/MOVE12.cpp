#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 100005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, c[mn], t[mn];
pair<int, int> range[mn];
priority_queue<int> p;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
        cin >> c[i] >> t[i];
}

bool check(int x)
{
    FOR(i, 1, n)
    {
        int step = x / t[i];
        range[i] = mp(max(c[i] - step, 1), min(c[i] + step, n));
    }

    sort(range + 1, range + n + 1);
    range[n + 1].F = maxC;
    while(!p.empty())
        p.pop();
    int id = 0;

    FOR(r, 1, n)
    {
        while(range[id + 1].F <= r)
            p.push(- range[++ id].S);
        while(!p.empty())
        {
            if (- p.top() < r)
                p.pop();
            else
                break;
        }
        if (p.empty())
            return false;
        p.pop();
    }
    return true;
}

void xuly()
{
    int l = -1, r = n * 10000;
    while(r - l > 1)
    {
        int g = (l + r) >> 1;
        if (check(g))
            r = g;
        else
            l = g;
    }
    cout << r;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    setup ();
    xuly ();
    return 0;
}
