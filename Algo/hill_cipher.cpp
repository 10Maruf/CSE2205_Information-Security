// A C++ program to illustrate Hill Cipher Technique with user input
#include <iostream>
#include <vector>
using namespace std;

// Function to find modular inverse of determinant under modulo 26
int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; // inverse doesn't exist
}

// Function to get the determinant of 2x2 matrix
int determinant(const vector<vector<int>>& key)
{
    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);
}

// Function to get the inverse key matrix (for 2x2 matrix)
vector<vector<int>> inverseKey(const vector<vector<int>>& key)
{
    int det = determinant(key);
    int invDet = modInverse(det, 26);

    vector<vector<int>> inv(2, vector<int>(2));

    if (invDet == -1) {
        inv[0][0] = inv[0][1] = inv[1][0] = inv[1][1] = -1;
        return inv;
    }

    inv[0][0] = (key[1][1] * invDet) % 26;
    inv[0][1] = (-key[0][1] * invDet + 26) % 26;
    inv[1][0] = (-key[1][0] * invDet + 26) % 26;
    inv[1][1] = (key[0][0] * invDet) % 26;

    return inv;
}

// Function to multiply 2x2 matrix with 2x1 vector
vector<int> multiply(const vector<vector<int>>& key, const vector<int>& vec)
{
    vector<int> res(2);
    res[0] = (key[0][0] * vec[0] + key[0][1] * vec[1]) % 26;
    res[1] = (key[1][0] * vec[0] + key[1][1] * vec[1]) % 26;
    return res;
}

// Function to encrypt the text
string encrypt(string text, const vector<vector<int>>& key)
{
    string result = "";

    if (text.length() % 2 != 0)
        text += 'X'; // padding if odd length

    for (int i = 0; i < text.length(); i += 2) {
        vector<int> vec = {text[i] - 'A', text[i+1] - 'A'};
        vector<int> res = multiply(key, vec);
        result += char(res[0] + 'A');
        result += char(res[1] + 'A');
    }

    return result;
}

// Function to decrypt the text
string decrypt(string text, const vector<vector<int>>& key)
{
    string result = "";

    vector<vector<int>> invKey = inverseKey(key);

    if (invKey[0][0] == -1) {
        return "Decryption not possible! Key matrix is not invertible.";
    }

    for (int i = 0; i < text.length(); i += 2) {
        vector<int> vec = {text[i] - 'A', text[i+1] - 'A'};
        vector<int> res = multiply(invKey, vec);
        result += char((res[0] + 26) % 26 + 'A');
        result += char((res[1] + 26) % 26 + 'A');
    }

    return result;
}

int main()
{
    string text;
    vector<vector<int>> key(2, vector<int>(2));
    int choice;

    cout << "Enter the 2x2 key matrix (row-wise):\n";
    cin >> key[0][0] >> key[0][1];
    cin >> key[1][0] >> key[1][1];

    cout << "Enter the text (only letters, uppercase preferred): ";
    cin.ignore();
    getline(cin, text);

    cout << "Choose:\n1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;

    for (int i = 0; i < text.length(); i++) {
        if (islower(text[i]))
            text[i] = toupper(text[i]);
    }

    if (choice == 1) {
        cout << "\nEncrypted Text: " << encrypt(text, key) << endl;
    }
    else if (choice == 2) {
        cout << "\nDecrypted Text: " << decrypt(text, key) << endl;
    }
    else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}
// Use a 2×2 key matrix for encrypting/decrypting in pairs.

// Text is padded if its length is odd.

// Only supports letters (A-Z).

// Decryption requires finding modular inverse of determinant