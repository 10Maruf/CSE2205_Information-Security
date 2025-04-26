// A C++ program to illustrate Multiplicative Cipher Technique with user input
#include <iostream>
using namespace std;

// Function to find modular inverse of a under modulo m
int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1; // inverse doesn't exist
}

// Function to encrypt the text
string encrypt(string text, int key)
{
    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (isupper(text[i]))
            result += char((key * (text[i] - 'A')) % 26 + 'A');
        else if (islower(text[i]))
            result += char((key * (text[i] - 'a')) % 26 + 'a');
        else
            result += text[i]; // Keep non-letter characters unchanged
    }

    return result;
}

// Function to decrypt the text
string decrypt(string text, int key)
{
    int inv = modInverse(key, 26);
    if (inv == -1)
    {
        return "Decryption not possible! No modular inverse.";
    }

    string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        if (isupper(text[i]))
            result += char((inv * (text[i] - 'A')) % 26 + 'A');
        else if (islower(text[i]))
            result += char((inv * (text[i] - 'a')) % 26 + 'a');
        else
            result += text[i]; // Keep non-letter characters unchanged
    }

    return result;
}

int main()
{
    string text;
    int key;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the key (must be coprime with 26): ";
    cin >> key;

    cout << "Choose:\n1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nEncrypted Text: " << encrypt(text, key) << endl;
    }
    else if (choice == 2)
    {
        cout << "\nDecrypted Text: " << decrypt(text, key) << endl;
    }
    else
    {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}
