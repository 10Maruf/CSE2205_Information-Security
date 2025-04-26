// A C++ program to illustrate Caesar Cipher Technique with user input
#include <iostream>
using namespace std;

// Function to encrypt the text
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
            result += text[i]; // Keep non-letter characters unchanged
    }

    return result;
}

// Function to decrypt the text
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
            result += text[i]; // Keep non-letter characters unchanged
    }

    return result;
}

int main()
{
    string text;
    int s;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the shift: ";
    cin >> s;

    cout << "Choose:\n1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;

    if (choice == 1)
    {
        cout << "\nEncrypted Text: " << encrypt(text, s) << endl;
    }
    else if (choice == 2)
    {
        cout << "\nDecrypted Text: " << decrypt(text, s) << endl;
    }
    else
    {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}
