#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 1000006
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int n, m, f[mn];
string a, b;

void setup()
{
    cin >> a >> b;
    m = a.size();
    n = b.size();
}

void prepareKMP()
{
    f[0] = -1, f[1] = 0;
    int id = 0;
    FOR(i, 2, n)
    {
        while(id != -1 && b[id] != b[i - 1])
            id = f[id];
        f[i] = ++ id;
    }
}

void findOccurance()
{
    int id = 0;
    FOR(i, 1, m)
    {
        while(id != -1 && b[id] != a[i - 1])
            id = f[id];
        if (++ id == n)
            cout << i - n + 1 << ' ', id = f[id];
    }
}

void xuly()
{
    prepareKMP();
    findOccurance();
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
