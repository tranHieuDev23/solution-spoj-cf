#include <bits/stdc++.h>

using namespace std;
map< vector<int>, int > Map;
vector<int> x, tem;
int n, k, dem = 0;

void dfs(int z)
{
    if (z == n)
    {
        if (Map[x] == 0)
        {
            dem ++;
            for(int i = 0; i < n; i ++)
            {
                tem.clear();
                for(int j = i; j < n; j ++)
                    tem.push_back(x[j]);
                for(int j = 0; j < i; j ++)
                    tem.push_back(x[j]);
                Map[tem] = 1;
            }
        }
        return;
    }
    for(int i = 1; i <= k; i ++)
    {
        x[z] = i;
        dfs(z + 1);
    }
}

int main()
{
    cin >> n >> k;
    x.resize(n);
    dfs(0);
    cout << dem;
    return 0;
}
