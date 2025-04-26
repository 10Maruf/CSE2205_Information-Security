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
#define vvi vector<vector<ll>>
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
/*
 "The harder the problem, the sweeter the victory. Keep coding!"
*/

ll Case = 1;

void solve()
{
    ll p, r;

    cout << "Enter the number of processes and resources: ";
    cin >> p >> r;

    vvi maxClaim(p, vec(r));
    vvi alloc(p, vec(r));
    vvi need(p, vec(r));
    vec total(r);
    vec avail(r);

    cout << "Enter the claim matrix:" << endl;
    for (auto &row : maxClaim)
        for (auto &val : row)
            cin >> val;

    cout << "Enter the allocation matrix:" << endl;
    for (auto &row : alloc)
        for (auto &val : row)
            cin >> val;

    cout << "Resource vector: ";
    for (auto &val : total)
        cin >> val;

    for (ll j = 0; j < r; j++)
    {
        ll sumAlloc = 0;
        for (const auto &row : alloc)
        {
            sumAlloc += row[j];
        }
        avail[j] = total[j] - sumAlloc;
    }

    for (ll i = 0; i < p; i++)
        for (ll j = 0; j < r; j++)
            need[i][j] = maxClaim[i][j] - alloc[i][j];

    vector<bool> done(p, false);
    bool safe = true;
    vec safety;

    while (safety.size() < p)
    {
        bool flagalloc = false;

        for (ll i = 0; i < p; i++)
        {
            if (!done[i])
            {
                bool alloccc = true;

                for (ll j = 0; j < r; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        alloccc = false;
                        break;
                    }
                }

                if (alloccc)
                {
                    cout << "All the resources can be allocated to Process " << (i + 1) << endl;
                    cout << "Process " << (i + 1) << " executed? (y/n): ";
                    string ans;
                    cin >> ans;

                    if (ans != "y" && ans != "Y")
                    {
                        safe = false;
                        break;
                    }

                    for (ll j = 0; j < r; j++)
                    {
                        avail[j] += alloc[i][j];
                    }

                    done[i] = true;
                    safety.pb(i + 1);

                    cout << "Available Resources are: ";
                    for (const auto &val : avail)
                        cout << val << " ";
                    cout << endl;

                    flagalloc = true;
                }
            }
        }

        if (!flagalloc)
            break;
    }

    if (safe && safety.size() == p)
    {
        cout << "System is in safe mode" << endl;
        cout << "The given state is a safe state" << endl;
    }
    else
    {
        cout << "System is NOT in a safe state" << endl;
    }
}

signed main()
{
    solve();
    return 0;
}
