#include<bits/stdc++.h>
#define FOR(i, j, k) for(int i = j; i <= k; i ++)
#define FORD(i, j, k) for(int i = j; i >= k; i --)
#define mn 300005
#define maxC 1000000007
#define pb push_back
#define mp make_pair

using namespace std;
bool srandSet = false;

int getRandom(int low, int high)
{
    if (!srandSet)
    {
        srand(time(NULL));
        srandSet = true;
    }
    int value = 1ll * rand() * rand();
    int range = high - low + 1;
    return ((value % range) + range) % range + low;
}

class Treap
{
    private:
        class TreapNode
        {
            public:
                pair<long long, int> value;
                int sum, priority;
                TreapNode *lc, *rc;

                TreapNode() {}

                TreapNode(pair<long long, int> value): value(value)
                {
                    sum = value.second;
                    priority = getRandom(1, maxC);
                    lc = rc = NULL;
                }
        };

        int getSum(TreapNode* node)
        {
            return node == NULL? 0 : node->sum;
        }

        void updateSum(TreapNode* node)
        {
            if (node != NULL)
                node->sum = getSum(node->lc) + getSum(node->rc) + node->value.second;
        }

        TreapNode* rightRotate(TreapNode* node)
        {
            TreapNode* newRoot = node->lc;
            TreapNode* newLeftChild = newRoot->rc;
            newRoot->rc = node;
            node->lc = newLeftChild;
            updateSum(node);
            updateSum(newRoot);
            return newRoot;
        }

        TreapNode* leftRotate(TreapNode* node)
        {
            TreapNode* newRoot = node->rc;
            TreapNode* newRightChild = newRoot->lc;
            newRoot->lc = node;
            node->rc = newRightChild;
            updateSum(node);
            updateSum(newRoot);
            return newRoot;
        }

        TreapNode* insert(TreapNode* node, pair<long long, int>value)
        {
            if (node == NULL)
                return new TreapNode(value);
            if (value.first == node->value.first)
            {
                node->value.second += value.second;
                updateSum(node);
                return node;
            }
            if (value < node->value)
            {
                node->lc = insert(node->lc, value);
                updateSum(node);
                if (node->lc->priority > node->priority)
                    node = rightRotate(node);
            }
            else
            {
                node->rc = insert(node->rc, value);
                updateSum(node);
                if (node->rc->priority > node->priority)
                    node = leftRotate(node);
            }
            return node;
        }

        int getSumSecond(TreapNode* node, long long first)
        {
            if (node == NULL)
                return 0;
            if (first < node->value.first)
                return getSumSecond(node->lc, first);
            return node->value.second + getSum(node->lc) + getSumSecond(node->rc, first);
        }

        TreapNode* root;

    public:

        Treap()
        {
            root = NULL;
        }

        void insert(pair<long long, int>value)
        {
            root = insert(root, value);
        }

        int getSumSecond(long long first)
        {
            return getSumSecond(root, first);
        }
};

int q;
long long l = 0;
Treap treap;

void setup()
{
    cin >> q;
    long long a, v;
    while(q --)
    {
        cin >> a >> v;
        a ^= l;
        v ^= l;
        treap.insert(mp(a, v));
        l = treap.getSumSecond(a);
        cout << a << ' ' << l << '\n';
    }
}

void xuly()
{

}

int main()
{
    iostream::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    setup();
    xuly();
    return 0;
}