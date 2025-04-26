/*maruf_bro*/

#include <bits/stdc++.h>
using namespace std;
#define IO                            \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define ld long double
#define ll long long
#define vec vector<ll>
#define pb push_back
#define fcin(n)       \
    for (auto &x : n) \
    cin >> x
#define fcout(n)     \
    for (auto x : n) \
    cout << x << " "
#define YES puts("YES")
#define NO puts("NO")
#define endl '\n'

int Case = 1;

void solve()
{
    ll a, n, r1, r2, t1 = 0, t2 = 1, q, r, t;
    cin >> a >> n;
    r1 = n, r2 = a;

    while (r2)
    {
        q = r1 / r2;
        r = r1 % r2;
        r1 = r2;
        r2 = r;
        t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }

    if (r1 == 1)
    {
        if (t1 < 0)
            t1 += n;
        cout << "Multiplicative Inverse: " << t1 << endl;
    }
    else
        cout << "No Multiplicative Inverse Exists!" << endl;
}

signed main()
{
    IO;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
