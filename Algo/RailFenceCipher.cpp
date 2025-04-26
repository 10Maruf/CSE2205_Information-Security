// A C++ program to illustrate Rail Fence Cipher Technique (user input based)
#include <iostream>
using namespace std;

// Function to encrypt using Rail Fence Cipher
string encrypt(string text, int key)
{
    char rail[key][text.length()];

    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';

    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < text.length(); i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;

        rail[row][col++] = text[i];

        dir_down ? row++ : row--;
    }

    string result;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            if (rail[i][j] != '\n')
                result.push_back(rail[i][j]);

    return result;
}

// Function to decrypt using Rail Fence Cipher
string decrypt(string cipher, int key)
{
    char rail[key][cipher.length()];

    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    bool dir_down;
    int row = 0, col = 0;

    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        rail[row][col++] = '*';

        dir_down ? row++ : row--;
    }

    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*' && index < cipher.length())
                rail[i][j] = cipher[index++];

    string result;
    row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;

        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);

        dir_down ? row++ : row--;
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

    cout << "Enter the key (number of rails): ";
    cin >> key;

    cout << "Choose:\n1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;

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
