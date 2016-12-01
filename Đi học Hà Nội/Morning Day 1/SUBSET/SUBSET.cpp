#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, id[mn];
long long l, r, w[mn];
bool dp[81][mn], sub5 = true, use[mn];
vector< pair<long long, int> > allSum[3];
vector<int> ans;

void setup()
{
    cin >> n >> l >> r;
    FOR(i, 1, n)
    {
        cin >> w[i];
        if (w[i] != i)
            sub5 = false;
    }
}

void makeallSum(int st, int cur, int rig, long long sum, int bit, int vec)
{
    allSum[vec].pb(mp(sum, bit));
    FOR(i, cur + 1, rig)
        makeallSum(st, i, rig, sum + w[i], bit | (1ll << (i - st)), vec);
}

void subtask12()
{
    int half = n >> 1;
    makeallSum(1, 0, half, 0, 0, 1);
    makeallSum(half + 1, half, n, 0, 0, 2);
    sort(allSum[1].begin(), allSum[1].end());
    sort(allSum[2].begin(), allSum[2].end());
    int id1 = allSum[1].size() - 1;
    FOR(id2, 0, int(allSum[2].size() - 1))
    {
        while(allSum[1][id1].F + allSum[2][id2].F > r)
        {
            if(-- id1 == -1)
                return;
        }
        if(l <= allSum[1][id1].F + allSum[2][id2].F)
        {
            int bit1 = allSum[1][id1].S;
            int bit2 = allSum[2][id2].S;
            FOR(i, 1, half)
            if ((bit1 >> (i - 1)) & 1)
                ans.pb(i);
            FOR(i, half + 1, n)
            if ((bit2 >> (i - half - 1)) & 1)
                ans.pb(i);
            cout << ans.size() << '\n';
            FOR(i, 0, int(ans.size()) - 1)
                cout << ans[i] << ' ';
            exit(0);
        }
    }
}

void traceBack(int u, int sum)
{
    if (sum == 0)
        return;
    if (dp[u - 1][sum])
        traceBack(u - 1, sum);
    else
    {
        ans.pb(u);
        traceBack(u - 1, sum - w[u]);
    }
}

void subtask3()
{
    dp[0][0] = true;
    FOR(i, 1, n)
    {
        FOR(j, 0, w[i - 1])
            dp[i][j] = dp[i - 1][j];
        FOR(j, w[i], r)
            dp[i][j] = dp[i - 1][j] | dp[i - 1][j - w[i]];
    }
    FOR(i, l, r)
    if (dp[n][i])
    {
        traceBack(n, i);
        cout << ans.size() << '\n';
        FORD(i, int(ans.size()) - 1, 0)
            cout << ans[i] << ' ';
        exit(0);
    }
}

void subtask5()
{
    long long sum = 0;
    int dem = 0;
    FOR(i, 1, n)
    {
        use[i] = true;
        dem ++;
        sum += w[i];
        if (l <= sum && sum <= r)
            break;
        if (r < sum)
        {
            use[sum - r] = false;
            dem --;
            break;
        }
    }
    cout << dem << '\n';
    FOR(i, 1, n)
    if (use[i])
        cout << i << ' ';
    exit(0);
}

bool comp(int& a, int& b)
{
    return w[a] < w[b];
}

void subtask6()
{
    FOR(i, 1, n)
        id[i] = i;
    sort(id + 1, id + n + 1, comp);
    long long sum = 0;
    int first = 1;
    FOR(i, 1, n)
    {
        sum += w[id[i]];
        if (r < sum)
            sum -= w[id[first ++]];
        if (l <= sum && sum <= r)
        {
            FOR(j, first, i)
                ans.pb(id[j]);
            sort(ans.begin(), ans.end());
            cout << ans.size() << '\n';
            FOR(i, 0, int(ans.size()) - 1)
                cout << ans[i] << ' ';
            cout << '\n' << sum << '\n';
            return;
        }
    }
}

void xuly()
{
    if (n <= 40)
        subtask12();
    if (n <= 80 && r <= 100000)
        subtask3();
    if (sub5)
        subtask5();
    subtask6();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("SUBSET.INP", "r", stdin);
    freopen("SUBSET.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
