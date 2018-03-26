#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <cmath>
using namespace std;

enum
{
    VALID_BITS = 30,
    MAX_LENGTH = 300000
};


unsigned a[MAX_LENGTH], p[MAX_LENGTH], ans[MAX_LENGTH];
class point
{
public:
    point *next[2];
    point *parent;
    unsigned weight;
    point()
    {
        parent = next[0] = next[1] = nullptr;
        weight = 0;
    }
};

void dfs(point *v, unsigned x, int deep)
{
    if (!v)
        return;

    if (deep == 30) {
        cout << x << '\n';
        return;
    }



    for (int bit = 0; bit < 2; ++bit) {
        dfs(v->next[bit], (x << 1) + bit, deep + 1);
    }
}


int main()
{
    int n;
    cin >> n;


    point top;
    point *v, *t;
    top.parent = &top;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ans[i] = a[i];
    }


    for (int i = 0; i < n; ++i)
        cin >> p[i];


    //tree initialization
    for (int i = 0; i < n; ++i) {
        unsigned x = p[i];
        v = &top;
        for (int shift = VALID_BITS - 1; shift >= 0; --shift) {
            unsigned bit = (x >> shift) & 1;
            if (!(v->next[bit]))
                v->next[bit] = new point;
            (v->next[bit])->parent = v;
            v = v->next[bit];
        }
        v->weight++;
    }

    for (int i = 0; i < n; ++i) {

        unsigned x = a[i];
        v = &top;

        unsigned mask = 0;
        for (int shift = VALID_BITS - 1; shift >= 0; --shift) {
            unsigned bit = (x >> shift) & 1;
            unsigned go_bit = bit;
            if (!(v->next[bit]))
                go_bit = 1 - bit;
            mask = (mask << 1) + go_bit;
            v = v->next[go_bit];
        }
        ans[i] = ans[i] ^ mask;

        v->weight--;
        if (v->weight == 0) {   //removing invalid tale
            t = v;
            v = v->parent;
            delete t;
            int num = 0;
            while (!(v->next[0] && v->next[1]) && (v->parent != v)) {
                num++;
                t = v;
                v = v->parent;
                delete t;
            }
            int delete_bit = (mask >> num) & 1;
            v->next[delete_bit] = nullptr;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }

    return 0;
}
