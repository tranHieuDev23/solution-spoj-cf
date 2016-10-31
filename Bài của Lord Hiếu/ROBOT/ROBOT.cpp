#include <bits/stdc++.h>
#define FOR(i, j, k) for(int i = j; i <= k; i ++)
#define FORD(i, j, k) for(int i = j; i >= k; i --)
#define mn 100005
#define mn2 300005
#define F first
#define S second
#define mp make_pair
#define pb push_back
#define fb(x) (x & (-x))
#define cn(c) (c == 'N'? 0 : (c == 'E'? 1 : (c == 'S'? 2 : 3)))

using namespace std;
struct bitTree
{
    int tree[mn2];
    void update(int x, int v)
    {
        for(; x < mn2; x += fb(x))
            tree[x] += v;
    }
    int getSum(int x)
    {
        int re = 0;
        for(; x; x -= fb(x))
            re += tree[x];
        return re;
    }
} t;
struct bot
{
    int x, y, dir;
    bot() {x = y = dir = 0;}
    bot(int _x, int _y, int _dir) {x = _x, y = _y, dir = _dir;}
} robot[mn];
int n, m, k, conRow[mn2], conCol[mn2], numRow, numCol, low[mn2], high[mn2];
vector<int> col, row;
map<int, int> mapRow, mapCol;
vector<bot> after;
long long ans = 0;

void setup()
{
    int x, y, z;
    char c;
    cin >> n >> m >> k;
    FOR(i, 1, k)
    {
        cin >> x >> y >> c;
        z = cn(c);
        robot[i] = bot(x, y, z);
        row.pb(x);
        row.pb(x + 1);
        row.pb(x - 1);
        col.pb(y);
        col.pb(y + 1);
        col.pb(y - 1);
    }
}

void thuGon()
{
    col.pb(1), col.pb(m);
    row.pb(1), row.pb(n);
    sort(col.begin(), col.end());
    sort(row.begin(), row.end());
    mapCol[col[0]] = (numCol = 1);
    mapRow[row[0]] = (numRow = 1);
    conCol[1] = col[0];
    conRow[1] = row[0];
    FOR(i, 1, int(col.size()) - 1)
    if (col[i] != col[i - 1])
    {
        mapCol[col[i]] = (++ numCol);
        conCol[numCol] = col[i];
    }
    FOR(i, 1, int(row.size()) - 1)
    if (row[i] != row[i - 1])
    {
        mapRow[row[i]] = (++ numRow);
        conRow[numRow] = row[i];
    }
}

void gopCot()
{
    memset(high, 0, sizeof(high));
    memset(low, 61, sizeof(low));
    FOR(i, 1, k)
    if ((robot[i].dir & 1) == 0)
    {
        int x = mapRow[robot[i].x];
        int y = mapCol[robot[i].y];
        if (robot[i].dir == 2)
            high[y] = max(high[y], x);
        else
            low[y] = min(low[y], x);
    }
    FOR(i, 1, numCol)
    {
        if (high[i])
        {
            if (low[i] <= numRow)
            {
                if (low[i] <= high[i] + 1)
                    after.pb(bot(1, i, 0)), ans += n;
                else
                {
                    after.pb(bot(high[i], i, 2)), ans += conRow[high[i]];
                    after.pb(bot(low[i], i, 0)), ans += n - conRow[low[i]] + 1;
                }
            }
            else
                after.pb(bot(high[i], i, 2)), ans += conRow[high[i]];
            continue;
        }
        if (low[i] <= numRow)
            after.pb(bot(low[i], i, 0)), ans += n - conRow[low[i]] + 1;
    }
}

void gopHang()
{
    memset(high, 0, sizeof(high));
    memset(low, 61, sizeof(low));
    FOR(i, 1, k)
    if (robot[i].dir & 1)
    {
        int x = mapRow[robot[i].x];
        int y = mapCol[robot[i].y];
        if (robot[i].dir == 3)
            high[x] = max(high[x], y);
        else
            low[x] = min(low[x], y);
    }
    FOR(i, 1, numRow)
    {
        if (high[i])
        {
            if (low[i] <= numCol)
            {
                if (low[i] <= high[i] + 1)
                    after.pb(bot(i, 1, 1)), ans += m;
                else
                {
                    after.pb(bot(i, high[i], 3)), ans += conCol[high[i]];
                    after.pb(bot(i, low[i], 1)), ans += m - conCol[low[i]] + 1;
                }
            }
            else
                after.pb(bot(i, high[i], 3)), ans += conCol[high[i]];
            continue;
        }
        if (low[i] <= numCol)
            after.pb(bot(i, low[i], 1)), ans += m - conCol[low[i]] + 1;
    }
}

struct node
{
    int x, y, id;
    node() {x = y = id = 0;}
    node(int _x, int _y, int _id){x = _x, y = _y, id = _id;}
};
vector<node> st;
bool comp(node a, node b)
{
    if (a.y != b.y)
        return a.y < b.y;
    if (a.id != b.id)
        return a.id < b.id;
    return a.x < b.x;
}

void sol()
{
    FOR(i, 0, int(after.size()) - 1)
    {
        int x = after[i].x;
        int y = after[i].y;
        int dir = after[i].dir;
        if (dir == 1)
            st.pb(node(x, y, -1));
        if (dir == 3)
        {
            st.pb(node(x, 0, -1));
            st.pb(node(x, y + 1, -2));
        }
        if ((dir & 1) == 0)
            st.pb(node(x, y, i));
    }
    sort(st.begin(), st.end(), comp);
    FOR(i, 0, int(st.size()) - 1)
    {
        if (st[i].id == -1)
            t.update(st[i].x, 1);
        if (st[i].id == -2)
            t.update(st[i].x, -1);
        if (st[i].id >= 0)
        {
            int x = after[st[i].id].x;
            int dir = after[st[i].id].dir;
            if (dir == 2)
                ans -= t.getSum(x);
            else
                ans -= t.getSum(numRow) - t.getSum(x - 1);
        }
    }
}

void xuly()
{
    thuGon();
    gopCot();
    gopHang();
    sol();
    cout << ans;
}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("ROBOT.INP", "r", stdin);
    freopen("ROBOT.OUT", "w", stdout);
    setup();
    xuly();
    return 0;
}
