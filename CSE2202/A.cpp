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
/*
 "The harder the problem, the sweeter the victory. Keep coding!"
*/

ll Case = 1;

void solve()
{
    vec bt(20), p(20), wt(20), tat(20);
    ll n, total = 0, totalT = 0, pos, temp;
    float avg_wt, avg_tat;
    cout << "\nEnter Number of Process - ";
    cin >> n;

    cout << "\nEnter Burst Time:\n";
    for (ll i = 0; i < n; i++)
    {
        cout << "Enter Burst Time for Process " << i << "-- " << ": ";
        cin >> bt[i];
        p[i] = i;
    }
    for (ll i = 0; i < n; i++)
    {
        pos = i;
        for (ll j = i + 1; j < n; j++)
        {
            if (bt[j] < bt[pos])
                pos = j;
        }

        swap(bt[i], bt[pos]);
        swap(p[i], p[pos]);
    }

    wt[0] = 0;

    for (ll i = 1; i < n; i++)
    {
        wt[i] = 0;
        for (ll j = 0; j < i; j++)
            wt[i] += bt[j];
        total += wt[i];
    }

    avg_wt = static_cast<float>(total) / n;

    for (ll i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        totalT += tat[i];
    }

    avg_tat = static_cast<float>(totalT) / n;

    // Sorting results by process ID
    vector<tuple<ll, ll, ll, ll>> results;
    for (ll i = 0; i < n; i++)
    {
        results.push_back({p[i], bt[i], wt[i], tat[i]});
    }
    sort(results.begin(), results.end());

    for (const auto &result : results)
    {
        ll pid = get<0>(result);
        ll burst = get<1>(result);
        ll wait = get<2>(result);
        ll turn = get<3>(result);
        cout << "\np" << pid << "\t\t " << burst << "\t\t " << wait << "\t\t\t" << turn;
    }

    cout << fixed << setprecision(6);
    cout << "\n\nAverage Waiting Time -- " << avg_wt;
    cout << "\nAverage Turnaround Time -- " << avg_tat << "\n";
}

signed main()
{
    // IO;
    // ll t;
    // cin >> t;
    // while (t--)
    // {
    solve();
    // }

    return 0;
}
