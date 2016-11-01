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
int n;
vector<int> allV;
pair<int, int> line[mn];
map<int, int> Map;

struct bitTree
{
    int tree[mn];

    void update(int x)
    {
        for(; x <= n; x += (x & (-x)))
            tree[x] ++;
    }

    int get(int x)
    {
        int re = 0;
        for(; x; x -= (x & (-x)))
            re += tree[x];
        return re;
    }
} t;

void setup()
{
    cin >> n;
    FOR(i, 1, n)
    {
        cin >> line[i].F >> line[i].S;
        allV.pb(line[i].S);
    }
}

void xuly()
{
    sort(allV.begin(), allV.end());
    sort(line + 1, line + n + 1);
    FOR(i, 1, n)
        Map[allV[n - i]] = i;
    long long ans = 0;
    FOR(i, 1, n)
    {
        line[i].S = Map[line[i].S];
        ans += t.get(line[i].S);
        t.update(line[i].S);
    }
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("LPAIR.INP", "r", stdin);
    freopen("LPAIR.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
