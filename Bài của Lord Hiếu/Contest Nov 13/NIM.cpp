#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 2000006
#define maxC 1000000000007ll
#define pb push_back
#define F first
#define S second
#define mp make_pair

using namespace std;
int numLostPos = 1, t;
long long allLostPos[mn], x;
long long sqt = 1, endRange = 3;

long long getLostPos(long long last)
{
    while(last + sqt + 1 > endRange)
    {
        sqt ++;
        endRange = (sqt + 1) * (sqt + 1) - 1;
    }
    return last + sqt + 1;
}

void setup()
{
    allLostPos[numLostPos] = 0;
    while(allLostPos[numLostPos] < maxC)
    {
        numLostPos ++;
        allLostPos[numLostPos] = getLostPos(allLostPos[numLostPos - 1]);
    }
}

void xuly()
{
    cin >> t;
    while(t --)
    {
        cin >> x;
        int pos = lower_bound(allLostPos + 1, allLostPos + numLostPos + 1, x) - allLostPos;
        cout << (allLostPos[pos] == x? "STEVE\n" : "BILL\n");
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("NIM.INP", "r", stdin);
    freopen("NIM.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
