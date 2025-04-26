
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

string Bin_to_Hex(string s);
string Hex_to_Bin(string s);
string Dec_to_Bin(int n);
string subkeys[16]; // store all round keys

// constants regarding the keys

const int pc_1[56] = {57, 49, 41, 33, 25, 17, 9,
					  1, 58, 50, 42, 34, 26, 18,
					  10, 2, 59, 51, 43, 35, 27,
					  19, 11, 3, 60, 52, 44, 36,
					  63, 55, 47, 39, 31, 23, 15,
					  7, 62, 54, 46, 38, 30, 22,
					  14, 6, 61, 53, 45, 37, 29,
					  21, 13, 5, 28, 20, 12, 4};

int num_leftShift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1}; // number of bits to shift for each iteration

const int pc_2[48] = {14, 17, 11, 24, 1, 5,
					  3, 28, 15, 6, 21, 10,
					  23, 19, 12, 4, 26, 8,
					  16, 7, 27, 20, 13, 2,
					  41, 52, 31, 37, 47, 55,
					  30, 40, 51, 45, 33, 48,
					  44, 49, 39, 56, 34, 53,
					  46, 42, 50, 36, 29, 32};

// constants regarding the plain text

const int IP_t[64] = {58, 50, 42, 34, 26, 18, 10, 2, // intital permutation table
					  60, 52, 44, 36, 28, 20, 12, 4,
					  62, 54, 46, 38, 30, 22, 14, 6,
					  64, 56, 48, 40, 32, 24, 16, 8,
					  57, 49, 41, 33, 25, 17, 9, 1,
					  59, 51, 43, 35, 27, 19, 11, 3,
					  61, 53, 45, 37, 29, 21, 13, 5,
					  63, 55, 47, 39, 31, 23, 15, 7};

const int E_t[48] = {32, 1, 2, 3, 4, 5, // expantion table
					 4, 5, 6, 7, 8, 9,
					 8, 9, 10, 11, 12, 13,
					 12, 13, 14, 15, 16, 17,
					 16, 17, 18, 19, 20, 21,
					 20, 21, 22, 23, 24, 25,
					 24, 25, 26, 27, 28, 29,
					 28, 29, 30, 31, 32, 1};

int S[8][4][16] = { // S-box
	{
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
	{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
	 {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
	 {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
	 {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
	{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
	 {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
	 {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
	 {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
	{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
	 {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
	 {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
	 {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
	{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
	 {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
	 {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
	 {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
	{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
	 {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
	 {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
	 {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
	{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
	 {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
	 {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
	 {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
	{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
	 {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
	 {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
	 {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

const int P[32] = {16, 7, 20, 21,
				   29, 12, 28, 17,
				   1, 15, 23, 26,
				   5, 18, 31, 10,
				   2, 8, 24, 14,
				   32, 27, 3, 9,
				   19, 13, 30, 6,
				   22, 11, 4, 25};

const int P_1[64] = {40, 8, 48, 16, 56, 24, 64, 32,
					 39, 7, 47, 15, 55, 23, 63, 31,
					 38, 6, 46, 14, 54, 22, 62, 30,
					 37, 5, 45, 13, 53, 21, 61, 29,
					 36, 4, 44, 12, 52, 20, 60, 28,
					 35, 3, 43, 11, 51, 19, 59, 27,
					 34, 2, 42, 10, 50, 18, 58, 26,
					 33, 1, 41, 9, 49, 17, 57, 25};

// some functions

string shift_bit(string s, int n)
{
	string k = "";

	for (int i = n; i < s.size(); i++)
		k += s[i];

	for (int i = 0; i < n; i++)
		k += s[i];

	return k;
}

// expanding according to expantion table E_t
string expand_R(const string &r32)
{
	string r;
	for (int j = 0; j < 48; j++)
		r += r32[E_t[j] - 1];
	return r;
}

string xor_add(string s1, string s2)
{
	string result = "";
	for (int j = 0; j < s1.size(); j++)
	{
		if (s1[j] != s2[j])
			result += '1';
		else
			result += '0';
	}
	return result;
}

string get_element_from_box(string s, int k)
{
	int dec1 = 0, dec2 = 0, pwr = 0;
	dec1 = (int)(s[0] - '0') * 2 + (int)(s[5] - '0');
	for (int i = s.size() - 2; i >= 1; i--)
	{
		dec2 += (int)(s[i] - '0') * pow(2, pwr++);
	}

	return Dec_to_Bin(S[k][dec1][dec2]);
}

void generate_subkeys(const string &key_hex)
{
	// 1) convert hex → 64-bit binary
	string key64 = Hex_to_Bin(key_hex);

	// 2) then permute key64 with pc_1, split C/D, shifts, pc_2…
	string perm;
	for (int i = 0; i < 56; i++)
		perm += key64[pc_1[i] - 1];
	string C = perm.substr(0, 28), D = perm.substr(28, 28);
	for (int i = 0; i < 16; i++)
	{
		C = shift_bit(C, num_leftShift[i]);
		D = shift_bit(D, num_leftShift[i]);
		string CD = C + D, sub;
		for (int j = 0; j < 48; j++)
			sub += CD[pc_2[j] - 1];
		subkeys[i] = sub;
	}
}

string encrypt(const string &plain_hex, const string &key_hex)
{
	// 1) Generate all 16 round subkeys
	generate_subkeys(key_hex);

	// 2) Convert plaintext from hex to 64-bit binary
	string bin = Hex_to_Bin(plain_hex);

	// 3) Initial Permutation (IP)
	string perm;
	perm.reserve(64);
	for (int i = 0; i < 64; ++i)
	{
		perm += bin[IP_t[i] - 1];
	}

	// 4) Split into Left and Right halves
	string L = perm.substr(0, 32);
	string R = perm.substr(32, 32);

	// 5) 16 Feistel Rounds
	for (int round = 0; round < 16; ++round)
	{
		// 5.1) Expand R from 32 to 48 bits
		string R_expanded = expand_R(R);

		// 5.2) XOR with round key
		string xored = xor_add(R_expanded, subkeys[round]);

		// 5.3) S-box substitution (48 -> 32 bits)
		string sbox_out;
		for (int i = 0; i < 8; ++i)
		{
			string chunk = xored.substr(i * 6, 6);
			sbox_out += get_element_from_box(chunk, i);
		}

		// 5.4) P-box permutation
		string p_out;
		p_out.reserve(32);
		for (int i = 0; i < 32; ++i)
		{
			p_out += sbox_out[P[i] - 1];
		}

		// 5.5) Feistel function and swap
		string newR = xor_add(L, p_out);
		L = R;
		R = newR;
	}

	// 6) Pre-output: combine R and L (note the swap)
	string combined = R + L;

	// 7) Final Permutation (inverse IP)
	string final_bin;
	final_bin.reserve(64);
	for (int i = 0; i < 64; ++i)
	{
		final_bin += combined[P_1[i] - 1];
	}

	// 8) Convert binary to hex and return
	return Bin_to_Hex(final_bin);
}
string decrypt(const string &cipher_hex, const string &key_hex)
{
	// 1) Generate subkeys in normal order
	generate_subkeys(key_hex);
	// 2) Reverse the subkey order for decryption
	reverse(subkeys, subkeys + 16);

	// 3) Convert ciphertext from hex to 64-bit binary
	string bin = Hex_to_Bin(cipher_hex);

	// 4) Initial Permutation (IP)
	string perm;
	perm.reserve(64);
	for (int i = 0; i < 64; ++i)
	{
		perm += bin[IP_t[i] - 1];
	}

	// 5) Split into Left and Right halves
	string L = perm.substr(0, 32);
	string R = perm.substr(32, 32);

	// 6) 16 Feistel Rounds (same as encrypt but with reversed subkeys)
	for (int round = 0; round < 16; ++round)
	{
		string R_expanded = expand_R(R);
		string xored = xor_add(R_expanded, subkeys[round]);

		string sbox_out;
		for (int i = 0; i < 8; ++i)
		{
			string chunk = xored.substr(i * 6, 6);
			sbox_out += get_element_from_box(chunk, i);
		}

		string p_out;
		p_out.reserve(32);
		for (int i = 0; i < 32; ++i)
		{
			p_out += sbox_out[P[i] - 1];
		}

		string newR = xor_add(L, p_out);
		L = R;
		R = newR;
	}

	// 7) Pre-output: combine R and L (note the swap)
	string combined = R + L;

	// 8) Final Permutation (inverse IP)
	string final_bin;
	final_bin.reserve(64);
	for (int i = 0; i < 64; ++i)
	{
		final_bin += combined[P_1[i] - 1];
	}

	// 9) Convert binary to hex and return
	return Bin_to_Hex(final_bin);
}

string Bin_to_Hex(string s)
{
	string hex = "";
	for (int i = 0; i < s.size(); i += 4)
	{
		string k = "";
		for (int j = i; j < i + 4; j++)
			k += s[j];
		if (k == "0000")
			hex += '0';
		else if (k == "0001")
			hex += '1';
		else if (k == "0010")
			hex += '2';
		else if (k == "0011")
			hex += '3';
		else if (k == "0100")
			hex += '4';
		else if (k == "0101")
			hex += '5';
		else if (k == "0110")
			hex += '6';
		else if (k == "0111")
			hex += '7';
		else if (k == "1000")
			hex += '8';
		else if (k == "1001")
			hex += '9';
		else if (k == "1010")
			hex += 'A';
		else if (k == "1011")
			hex += 'B';
		else if (k == "1100")
			hex += 'C';
		else if (k == "1101")
			hex += 'D';
		else if (k == "1110")
			hex += 'E';
		else if (k == "1111")
			hex += 'F';
	}
	return hex;
}

string Hex_to_Bin(string s)
{
	string bin = "";
	for (int i = 0; i < s.size(); i++)
	{
		switch (s[i])
		{
		case '0':
			bin += "0000";
			break;
		case '1':
			bin += "0001";
			break;
		case '2':
			bin += "0010";
			break;
		case '3':
			bin += "0011";
			break;
		case '4':
			bin += "0100";
			break;
		case '5':
			bin += "0101";
			break;
		case '6':
			bin += "0110";
			break;
		case '7':
			bin += "0111";
			break;
		case '8':
			bin += "1000";
			break;
		case '9':
			bin += "1001";
			break;
		case 'A':
		case 'a':
			bin += "1010";
			break;
		case 'B':
		case 'b':
			bin += "1011";
			break;
		case 'C':
		case 'c':
			bin += "1100";
			break;
		case 'D':
		case 'd':
			bin += "1101";
			break;
		case 'E':
		case 'e':
			bin += "1110";
			break;
		case 'F':
		case 'f':
			bin += "1111";
			break;
		}
	}
	return bin;
}

string Dec_to_Bin(int n)
{
	string bin = "";
	while (n > 0)
	{
		bin = (char)(n % 2 + '0') + bin;
		n /= 2;
	}
	while (bin.size() < 4)
		bin = '0' + bin;
	return bin;
}


int main()
{
	bool is_valid;
	string text, key;

	// 1) Read and validate text (plaintext or ciphertext)
	cout << "Enter text (16 hex chars): ";
	do
	{
		is_valid = true;
		cin >> text;
		if (text.size() != 16)
			is_valid = false;
		else
			for (char c : text)
				if (!isxdigit(c))
				{
					is_valid = false;
					break;
				}
		if (!is_valid)
			cout << "Invalid input, try again: ";
	} while (!is_valid);

	// 2) Read and validate key
	cout << "Enter key    (16 hex chars): ";
	do
	{
		is_valid = true;
		cin >> key;
		if (key.size() != 16)
			is_valid = false;
		else
			for (char c : key)
				if (!isxdigit(c))
				{
					is_valid = false;
					break;
				}
		if (!is_valid)
			cout << "Invalid input, try again: ";
	} while (!is_valid);

	// 3) Choose operation
	char choice;
	cout << "Choose operation: (E)ncrypt or (D)ecrypt: ";
	do
	{
		cin >> choice;
		choice = toupper(choice);
		if (choice != 'E' && choice != 'D')
			cout << "Invalid choice, enter E or D: ";
	} while (choice != 'E' && choice != 'D');

	// 4) Perform and print result
	if (choice == 'E')
	{
		string cipher = encrypt(text, key);
		cout << "Ciphertext: " << cipher << endl;
	}
	else
	{
		string plain = decrypt(text, key);
		cout << "Plaintext : " << plain << endl;
	}

	return 0;
}

// Enter PLAIN TEXT of EXACTLY 16 character written in hexadecimal : 123456ABCD132536
// Enter a KEY of EXACTLY 16 character written in hexadecimal : AABB09182736CCDD
// C0B7A8D05F3A829C