// C++ Program for implementation of RSA Algorithm (String Version)

#include <bits/stdc++.h>
using namespace std;

// Function to compute base^expo mod m
int power(int base, int expo, int m) {
    int res = 1;
    base = base % m;
    while (expo > 0) {
        if (expo & 1)
            res = (res * 1LL * base) % m;
        base = (base * 1LL * base) % m;
        expo = expo / 2;
    }
    return res;
}

// Function to find modular inverse of e modulo phi(n)
int modInverse(int e, int phi) {
    for (int d = 2; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1;
}

// RSA Key Generation
void generateKeys(int &e, int &d, int &n) {
    int p = 7919;
    int q = 1009;
    
    n = p * q;
    int phi = (p - 1) * (q - 1);

    for (e = 2; e < phi; e++) {
        if (__gcd(e, phi) == 1)
            break;
    }

    d = modInverse(e, phi);
}

// Encrypt a single character
int encryptChar(char m, int e, int n) {
    return power((int)m, e, n);
}

// Decrypt a single character
char decryptChar(int c, int d, int n) {
    return (char)power(c, d, n);
}

int main() {
    int e, d, n;
    generateKeys(e, d, n);

    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";

    string msg;
    cout << "Enter the message: ";
    getline(cin, msg);  // ✅ no cin.ignore()

    // Encrypt the string
    vector<int> cipher;
    for (char ch : msg) {
        cipher.push_back(encryptChar(ch, e, n));
    }

    cout << "\nEncrypted Message (numbers): ";
    for (int c : cipher)
        cout << c << " ";
    cout << endl;

    // Decrypt the cipher
    string decrypted = "";
    for (int c : cipher) {
        decrypted += decryptChar(c, d, n);
    }

    cout << "\nDecrypted Message: " << decrypted << endl;

    return 0;
}
