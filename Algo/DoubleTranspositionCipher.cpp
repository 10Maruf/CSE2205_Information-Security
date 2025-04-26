// DoubleTranspositionCipher.cpp
// A C++ program to perform Double Row-Column Transposition Cipher encryption and decryption

#include <iostream>
#include <algorithm>
using namespace std;

// Function to perform single encryption
string singleEncrypt(string text, string key) {
    int col = key.length();
    int row = (text.length() + col - 1) / col;

    char matrix[row][col];
    int idx = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (idx < text.length()) {
                matrix[i][j] = text[idx++];
            } else {
                matrix[i][j] = 'X'; // Padding with 'X'
            }
        }
    }

    int key_order[col];
    for (int i = 0; i < col; i++) key_order[i] = i;
    sort(key_order, key_order + col, [&key](int a, int b) {
        return key[a] < key[b];
    });

    string cipher = "";
    for (int i = 0; i < col; i++) {
        int col_idx = key_order[i];
        for (int j = 0; j < row; j++) {
            cipher += matrix[j][col_idx];
        }
    }

    return cipher;
}

// Function to perform single decryption
string singleDecrypt(string cipher, string key) {
    int col = key.length();
    int row = (cipher.length() + col - 1) / col;

    char matrix[row][col];

    int key_order[col];
    for (int i = 0; i < col; i++) key_order[i] = i;
    sort(key_order, key_order + col, [&key](int a, int b) {
        return key[a] < key[b];
    });

    int idx = 0;
    for (int i = 0; i < col; i++) {
        int col_idx = key_order[i];
        for (int j = 0; j < row; j++) {
            if (idx < cipher.length()) {
                matrix[j][col_idx] = cipher[idx++];
            }
        }
    }

    string text = "";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            text += matrix[i][j];
        }
    }

    return text;
}

// Double Encryption
string doubleEncrypt(string text, string key1, string key2) {
    string first = singleEncrypt(text, key1);
    string second = singleEncrypt(first, key2);
    return second;
}

// Double Decryption
string doubleDecrypt(string cipher, string key1, string key2) {
    string first = singleDecrypt(cipher, key2);
    string second = singleDecrypt(first, key1);
    return second;
}

int main() {
    string text, key1, key2;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the first key: ";
    cin >> key1;

    cout << "Enter the second key: ";
    cin >> key2;

    cout << "Choose:\n1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nEncrypted Text: " << doubleEncrypt(text, key1, key2) << endl;
    }
    else if (choice == 2) {
        cout << "\nDecrypted Text: " << doubleDecrypt(text, key1, key2) << endl;
    }
    else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}
