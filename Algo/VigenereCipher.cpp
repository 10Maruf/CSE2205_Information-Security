// VigenereCipher.cpp
// A C++ program to perform Vigenere Cipher encryption and decryption

#include <iostream>
using namespace std;

// Function to generate the full key matching the length of text
string generateKey(string text, string key) {
    int x = text.length();
    int keyLength = key.length();
    for (int i = 0; key.length() < x; i++) {
        key += key[i % keyLength];
    }
    return key;
}

// Function to encrypt the text
string encrypt(string text, string key) {
    string cipher = "";
    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char baseKey = isupper(key[i]) ? 'A' : 'a';
            cipher += (char)(((text[i] - base + key[i] - baseKey) % 26) + base);
        } else {
            cipher += text[i]; // Non-alphabetic characters unchanged
        }
    }
    return cipher;
}

// Function to decrypt the text
string decrypt(string cipher, string key) {
    string text = "";
    for (int i = 0; i < cipher.length(); i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            char baseKey = isupper(key[i]) ? 'A' : 'a';
            text += (char)(((cipher[i] - base - (key[i] - baseKey) + 26) % 26) + base);
        } else {
            text += cipher[i]; // Non-alphabetic characters unchanged
        }
    }
    return text;
}

int main() {
    string text, key;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the key (no spaces, match case sensitivity): ";
    cin >> key;

    string fullKey = generateKey(text, key);
    cout << "\nGenerated Full Key: " << fullKey << endl;

    cout << "\nChoose:\n1. Encrypt\n2. Decrypt\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nEncrypted Text: " << encrypt(text, fullKey) << endl;
    }
    else if (choice == 2) {
        cout << "\nDecrypted Text: " << decrypt(text, fullKey) << endl;
    }
    else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}
