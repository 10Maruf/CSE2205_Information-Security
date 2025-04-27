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

int Case = 1;

string encrypt(string text, int s)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (isupper(text[i]))
            result += char((text[i] - 'A' + s) % 26 + 'A');
        else if (islower(text[i]))
            result += char((text[i] - 'a' + s) % 26 + 'a');
        else
            result += text[i];
    }

    return result;
}
string decrypt(string text, int s)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (isupper(text[i]))
            result += char((text[i] - 'A' - s + 26) % 26 + 'A');
        else if (islower(text[i]))
            result += char((text[i] - 'a' - s + 26) % 26 + 'a');
        else
            result += text[i];
    }

    return result;
}
void solve()
{
    string text;
    int s;

    cout << "Enter the plain text: ";
    getline(cin, text);

    srand(time(0));
    s = rand() % 26;
    cout << "Generated Key: " << s << endl;

    string encryptedText = encrypt(text, s);
    cout << "Encrypted Text: " << encryptedText << endl;

    string decryptedText = decrypt(encryptedText, s);
    cout << "Decrypted Text: " << decryptedText << endl;
}

signed main()
{
    // IO;
    // int t;
    // cin >> t;
    // while (t--)
    // {
    solve();
    // }

    return 0;
}
