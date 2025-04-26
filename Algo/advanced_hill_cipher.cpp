#include<stdio.h>
#include<iostream>
using namespace std;

// Check how many bogus characters to add
int check(int x)
{
    if (x % 3 == 0)
        return 0;
    int a = x / 3;
    int b = 3 * (a + 1);
    int c = b - x;
    return c;
}

// Function to find modular inverse under mod 26
int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to get adjoint of 3x3 matrix
void adjoint(int k[3][3], int adj[3][3])
{
    adj[0][0] = (k[1][1]*k[2][2] - k[1][2]*k[2][1]);
    adj[0][1] = -(k[0][1]*k[2][2] - k[0][2]*k[2][1]);
    adj[0][2] = (k[0][1]*k[1][2] - k[0][2]*k[1][1]);
    adj[1][0] = -(k[1][0]*k[2][2] - k[1][2]*k[2][0]);
    adj[1][1] = (k[0][0]*k[2][2] - k[0][2]*k[2][0]);
    adj[1][2] = -(k[0][0]*k[1][2] - k[0][2]*k[1][0]);
    adj[2][0] = (k[1][0]*k[2][1] - k[1][1]*k[2][0]);
    adj[2][1] = -(k[0][0]*k[2][1] - k[0][1]*k[2][0]);
    adj[2][2] = (k[0][0]*k[1][1] - k[0][1]*k[1][0]);
}

// Function to get inverse key matrix
bool inverseKey(int k[3][3], int inv[3][3])
{
    int det = 0;
    // Find determinant
    det = k[0][0]*(k[1][1]*k[2][2]-k[1][2]*k[2][1])
        - k[0][1]*(k[1][0]*k[2][2]-k[1][2]*k[2][0])
        + k[0][2]*(k[1][0]*k[2][1]-k[1][1]*k[2][0]);
    det = det % 26;
    if (det < 0) det += 26;

    int invDet = modInverse(det, 26);
    if (invDet == -1)
        return false; // No modular inverse, matrix not invertible

    int adj[3][3];
    adjoint(k, adj);

    // Multiply adjoint matrix with modular inverse of determinant
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            inv[i][j] = adj[i][j] * invDet;
            inv[i][j] = inv[i][j] % 26;
            if (inv[i][j] < 0)
                inv[i][j] += 26;
        }
    }
    return true;
}

int main()
{
    int l, i, j;
    int temp1;
    int k[3][3];
    int p[3][1];
    int c[3][1];

    // Step 1: Input the string
    cout << "\nEnter the string to be processed (without spaces): ";
    string input;
    cin >> input;
    l = input.length();
    temp1 = check(l);
    if (temp1 > 0)
        cout << "You have to enter " << temp1 << " bogus characters.\n";

    char pi[l + temp1];
    for (i = 0; i < l; ++i)
    {
        pi[i] = toupper(input[i]); // Convert to uppercase for consistency
    }
    for (i = l; i < l + temp1; ++i)
    {
        pi[i] = 'X'; // Add bogus characters
    }

    // Step 2: Input the key matrix
    cout << "\nThis cipher has a key of length 9 (3x3 matrix).\nEnter the key matrix (9 integers): ";
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            cin >> k[i][j];
            k[i][j] = k[i][j] % 26; // Ensure values are within mod 26
        }
    }

    cout << "\nKey Matrix:\n";
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            cout << k[i][j] << " ";
        }
        cout << endl;
    }

    // Step 3: Choose operation
    cout << "\nChoose an operation:\n1. Encrypt\n2. Decrypt\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        // Encryption
        cout << "\n\nThe encoded cipher is: ";
        char cipher[l + temp1];
        int n = (l + temp1) / 3;
        int flag = 0, idx = 0;

        while (n > 0)
        {
            int count = 0;
            for (i = flag; i < flag + 3; ++i)
            {
                int temp3 = pi[i] - 'A';
                p[count][0] = temp3;
                count++;
            }

            for (i = 0; i < 3; ++i)
                c[i][0] = 0;

            for (i = 0; i < 3; ++i)
            {
                for (j = 0; j < 1; ++j)
                {
                    for (int k1 = 0; k1 < 3; ++k1)
                        c[i][j] += k[i][k1] * p[k1][j];
                }
            }

            for (i = 0; i < 3; ++i)
            {
                c[i][0] = c[i][0] % 26;
                char ch = (char)(c[i][0] + 'A');
                printf("%c", ch);
                cipher[idx++] = ch;
            }

            n--;
            flag += 3;
        }
        cout << endl;
    }
    else if (choice == 2)
    {
        // Decryption
        cout << "\n\nNow decrypting...\n";

        int inv[3][3];
        if (!inverseKey(k, inv))
        {
            cout << "The key matrix is not invertible. Decryption not possible.\n";
            return 1;
        }

        cout << "\nInverse Key Matrix:\n";
        for (i = 0; i < 3; ++i)
        {
            for (j = 0; j < 3; ++j)
            {
                cout << inv[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\nDecrypted text: ";
        int n = (l + temp1) / 3;
        int flag = 0;

        while (n > 0)
        {
            int count = 0;
            for (i = flag; i < flag + 3; ++i)
            {
                int temp3 = pi[i] - 'A';
                p[count][0] = temp3;
                count++;
            }

            for (i = 0; i < 3; ++i)
                c[i][0] = 0;

            for (i = 0; i < 3; ++i)
            {
                for (j = 0; j < 1; ++j)
                {
                    for (int k1 = 0; k1 < 3; ++k1)
                        c[i][j] += inv[i][k1] * p[k1][j];
                }
            }

            for (i = 0; i < 3; ++i)
            {
                c[i][0] = c[i][0] % 26;
                if (c[i][0] < 0)
                    c[i][0] += 26;
                printf("%c", (char)(c[i][0] + 'A'));
            }

            n--;
            flag += 3;
        }
        cout << endl;

        // Remove bogus characters from the end of the decrypted text
        cout << "\nDecrypted text without bogus characters: ";
        for (i = 0; i < l; ++i)
        {
            printf("%c", (char)(pi[i]));
        }
        cout << endl;
    }
    else
    {
        cout << "Invalid choice. Exiting.\n";
    }

    return 0;
}