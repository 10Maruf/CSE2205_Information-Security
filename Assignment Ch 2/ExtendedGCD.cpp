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
    ll a, b, s1 = 1, s2 = 0, t1 = 0, t2 = 1, q, r, s, t;
    cin >> a >> b;

    for (ll r1 = a, r2 = b; r2;)
    {
        q = r1 / r2, r = r1 % r2;
        r1 = r2, r2 = r;
        s = s1 - q * s2, s1 = s2, s2 = s;
        t = t1 - q * t2, t1 = t2, t2 = t;
    }

    cout << "GCD: " << a * s1 + b * t1 << endl
         << "S: " << s1 << endl
         << "T: " << t1 << endl;
}

signed main()
{
    IO;
    int t;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
