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
long long countA, countB, maxA, maxB;

void setup()
{
    cin >> countA >> countB >> maxA >> maxB;
    if (maxA == 0)
    {
        cout << min(maxB, countB) << '\n';
        return;
    }
    if (maxB == 0)
    {
        cout << min(maxA, countA) << '\n';
        return;
    }
    if (countB > countA)
        swap(countA, countB), swap(maxA, maxB);
    long long canPlaceA = (countB + 1) * maxA;
    cout << countB + min(canPlaceA, countA) << '\n';
}

void xuly()
{

}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int t; cin >> t;
    FOR(i, 1, t)
        setup ();
    xuly ();
    return 0;
}
