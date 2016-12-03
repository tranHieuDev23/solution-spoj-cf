#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1003
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define isOne(x, i) (((x) >> (i)) & 1)

using namespace std;
int n, major[mn], score[mn], order[5], state;
string group = "ABCDA1";
pair<int, int> temp[mn], st[mn];

void setup()
{
    cin >> n;
    string s;
    FOR(i, 1, n)
    {
        cin >> s >> score[i];
        major[i] = group.find(s);
    }
    FOR(i, 0, 4)
        order[i] = i;
}

int calc()
{
    FOR(i, 1, n)
    {
        if (isOne(state, major[i]))
            temp[i] = mp(order[major[i]], score[i]);
        else
            temp[i] = mp(order[major[i]], -score[i]);
    }
    int ret = 0, r = 0;
    FOR(i, 1, n)
    {
        int lis = upper_bound(st + 1, st + r + 1, temp[i]) - st;
        ret = max(ret, lis);
        r = max(r, lis);
        st[lis] = temp[i];
    }
    return n - ret;
}

void xuly()
{
    int ans = maxC;
    do
    {
        for(state = 0; state < 32; state ++)
            ans = min(ans, calc());
    }
    while (next_permutation(order, order + 5));
    cout << ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("DEGREE.INP", "r", stdin);
    freopen("DEGREE.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
