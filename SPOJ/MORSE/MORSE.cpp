#include <bits/stdc++.h>
#define FOR(i, j, k) for (int i = j; i <= k; i ++)
#define FORD(i, j, k) for (int i = j; i >= k; i --)
#define mn 200005
#define mn2 10004
#define maxC 1000000007
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define val(c) ((c) == '-')

using namespace std;
string morse, s, z;
string alphabet[] =
{
    ".-", "-...", "-.-.", "-..",
    ".", "..-.", "--.", "....",
    "..", ".---", "-.-", ".-..",
    "--", "-.", "---", ".--.",
    "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-",
    "-.--", "--.."
};
int n, m, r;
long long dp[mn2];

struct trie
{
    int num, child[2];

    trie()
    {
        num = child[0] = child[1] = 0;
    }
} t[mn];


void setup()
{
    cin >> morse >> n;
    t[r = 1] = trie();
    FOR(i, 1, n)
    {
        cin >> z;
        m = z.size();
        s = "";
        FOR(j, 0, m - 1)
            s += alphabet[z[j] - 'A'];
        m = s.size();
        int p = 1;
        FOR(j, 0, m - 1)
        {
            int z = val(s[j]);
            if (!t[p].child[z])
            {
                t[p].child[z] = ++ r;
                t[r] = trie();
            }
            p = t[p].child[z];
        }
        t[p].num ++;
    }
    m = morse.size();
}

void xuly()
{
    dp[m] = 1;
    FORD(i, m - 1, 0)
    {
        dp[i] = 0;
        int p = 1;
        FOR(j, i, m - 1)
        {
            int z = val(morse[j]);
            if (!t[p].child[z])
                break;
            p = t[p].child[z];
            dp[i] += dp[j + 1] * t[p].num;
        }
    }
    cout << dp[0] << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int d; cin >> d;
    while(d --)
    {
        setup ();
        xuly ();
    }
    return 0;
}
