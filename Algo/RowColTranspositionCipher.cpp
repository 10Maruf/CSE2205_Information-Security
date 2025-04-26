// RowColTranspositionCipher.cpp
// A C++ program to perform Row-Column Transposition Cipher encryption and decryption

#include <iostream>
#include <algorithm>
using namespace std;

// Function to encrypt the text
string encrypt(string text, string key) {
    int col = key.length();
    int row = (text.length() + col - 1) / col;

    // Fill the matrix row by row
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

    // Determine the order of columns based on key
    int key_order[col];
    for (int i = 0; i < col; i++) {
        key_order[i] = i;
    }
    sort(key_order, key_order + col, [&key](int a, int b) {
        return key[a] < key[b];
    });

    // Read the matrix column-wise according to sorted key
    string cipher = "";
    for (int i = 0; i < col; i++) {
        int col_idx = key_order[i];
        for (int j = 0; j < row; j++) {
            cipher += matrix[j][col_idx];
        }
    }

    return cipher;
}

// Function to decrypt the text
string decrypt(string cipher, string key) {
    int col = key.length();
    int row = (cipher.length() + col - 1) / col;

    // Create an empty matrix
    char matrix[row][col];

    // Determine the order of columns based on key
    int key_order[col];
    for (int i = 0; i < col; i++) {
        key_order[i] = i;
    }
    sort(key_order, key_order + col, [&key](int a, int b) {
        return key[a] < key[b];
    });

    // Fill the matrix column by column according to sorted key
    int idx = 0;
    for (int i = 0; i < col; i++) {
        int col_idx = key_order[i];
        for (int j = 0; j < row; j++) {
            if (idx < cipher.length()) {
                matrix[j][col_idx] = cipher[idx++];
            }
        }
    }

    // Read the matrix row-wise to get the original text
    string text = "";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            text += matrix[i][j];
        }
    }

    return text;
}

int main() {
    string text, key;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the key (no spaces, lowercase or uppercase letters): ";
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
