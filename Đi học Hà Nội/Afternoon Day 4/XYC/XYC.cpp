#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define mn2 110
#define maxC 1000000007
#define sumX(l, r) (numX[r] - numX[l - 1])
#define sumY(l, r) (numY[r] - numY[l - 1])

using namespace std;
string s;
int k, c[mn2], n;
int numX[mn], numY[mn], in[mn];
bool canEnd[mn][mn2], sumCanEnd[mn][mn2];
bool legitEnd[mn][mn2], canFindSuf[mn][mn2];
int closePre[mn][mn2], closeSuf[mn][mn2];

void setup()
{
    cin >> s >> k;
    FOR(i, 1, k)
        cin >> c[i];
    n = s.size();
    s = ' ' + s;
}

void calcCanEnd()
{
    FOR(i, 1, n)
    {
        numX[i] = numX[i - 1] + (s[i] == 'X');
        numY[i] = numY[i - 1] + (s[i] == 'Y');
    }

    FOR(i, c[1], n)
    {
        canEnd[i][1] = (sumY(i - c[1] + 1, i) == 0 && sumX(1, i - c[1]) == 0);
        sumCanEnd[i][1] = sumCanEnd[i - 1][1] | canEnd[i][1];
    }
    FOR(j, 2, k)
    FOR(i, c[j] + 1, n)
    {
        if (sumY(i - c[j] + 1, i) != 0)
            canEnd[i][j] = false;
        else if (s[i - c[j]] == 'X')
            canEnd[i][j] = false;
        else
            canEnd[i][j] = sumCanEnd[i - c[j] - 1][j - 1];
        sumCanEnd[i][j] = sumCanEnd[i - 1][j] | canEnd[i][j];
    }
}

void calcLegitEnd()
{
    int limit = n;
    FORD(j, k, 1)
    {
        int temp = -1;
        FOR(i, 1, limit)
        if (canEnd[i][j])
        {
            legitEnd[i][j] = true;
            in[i - c[j] + 1] ++, in[i + 1] --;
            temp = i - c[j] - 1;
        }
        limit = temp;
    }
}

void prepare()
{
    closePre[0][0] = 0;
    FOR(i, 1, k)
        closePre[0][i] = -maxC;
    FOR(i, 1, n)
    {
        closePre[i][0] = 0;
        FOR(j, 1, k)
        {
            if (legitEnd[i][j])
                closePre[i][j] = i;
            else
                closePre[i][j] = closePre[i - 1][j];
        }
    }

    FORD(i, n + 1, 2)
    {
        closeSuf[i][k + 1] = n + 1;
        FOR(j, 1, k)
        {
            if (i + c[j] - 1 > n)
                closeSuf[i][j] = maxC;
            else if (legitEnd[i + c[j] - 1][j])
                closeSuf[i][j] = i;
            else
                closeSuf[i][j] = closeSuf[i + 1][j];
        }
    }
}

void getAns()
{
    FOR(i, 1, n)
    {
        in[i] += in[i - 1];
        if (s[i] != '#')
            cout << s[i];
        else
        {
            bool canBeY = false;
            FOR(j, 0, k)
            {
                int& dow = closePre[i - 1][j];
                int& up = closeSuf[i + 1][j + 1];
                if (dow == -maxC || up == maxC)
                    continue;
                if (sumX(dow + 1, i - 1) == 0 && sumX(i + 1, up - 1) == 0)
                {
                    canBeY = true;
                    break;
                }
            }

            if (!in[i])
                cout << 'Y';
            if (!canBeY)
                cout << 'X';
            if (in[i] && canBeY)
                cout << '?';
        }
    }
}

void xuly()
{
    calcCanEnd();
    calcLegitEnd();
    prepare();
    getAns();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("XYC.INP", "r", stdin);
    freopen("XYC.OUT", "w", stdout);
    setup ();
    xuly ();
    return 0;
}
