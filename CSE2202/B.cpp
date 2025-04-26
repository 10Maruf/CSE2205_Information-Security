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

const int SIZE = 5;
ll buf[SIZE];
int bufferCount = 0;
ll Case = 1;

void solve()
{
    ll choice;

    while (true)
    {
        cout << "1.Produce   2.Consume   3.Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            if (bufferCount == SIZE)
            {
                cout << "Buffer is full" << endl;
            }
            else
            {
                cout << "Enter the value: ";
                cin >> buf[bufferCount];
                bufferCount++;
            }
        }
        else if (choice == 2)
        {
            if (bufferCount == 0)
            {
                cout << "Buffer is empty" << endl;
            }
            else
            {
                cout << "The consumed value is " << buf[0] << endl;
                for (int i = 1; i < bufferCount; i++)
                {
                    buf[i - 1] = buf[i];
                }
                bufferCount--;
            }
        }
        else if (choice == 3)
        {
            exit(0);
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }
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
