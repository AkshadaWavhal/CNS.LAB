//W.A.P. to implement Advanced Columnar Transposition technique.
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to encrypt the plaintext using Advanced Columnar Transposition Cipher
string encryptAdvancedColumnar(string plaintext, string key) {
    // Remove spaces from the plaintext
    plaintext.erase(remove(plaintext.begin(), plaintext.end(), ' '), plaintext.end());

    // Calculate the number of columns (length of the key) and rows
    int numCols = key.length();
    int numRows = (plaintext.length() + numCols - 1) / numCols; // Round up to fill the grid

    // Create a 2D vector to represent the grid
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    // Fill the grid with the plaintext row by row
    int index = 0;
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            if (index < plaintext.length()) {
                grid[r][c] = plaintext[index++];
            }
        }
    }

    // Create a vector of pairs (key character, column index)
    vector<pair<char, int>> keyIndex;
    for (int i = 0; i < key.length(); i++) {
        keyIndex.push_back(make_pair(key[i], i));
    }

    // Sort the vector of pairs by key character
    sort(keyIndex.begin(), keyIndex.end());

    // Create the ciphertext by reading the columns in the sorted order of the key
    string ciphertext = "";
    for (auto& pair : keyIndex) {
        int col = pair.second;
        for (int r = 0; r < numRows; r++) {
            if (grid[r][col] != ' ') {
                ciphertext += grid[r][col];
            }
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using Advanced Columnar Transposition Cipher
string decryptAdvancedColumnar(string ciphertext, string key) {
    // Calculate the number of columns (length of the key) and rows
    int numCols = key.length();
    int numRows = (ciphertext.length() + numCols - 1) / numCols; // Round up to fill the grid

    // Create a vector of pairs (key character, column index)
    vector<pair<char, int>> keyIndex;
    for (int i = 0; i < key.length(); i++) {
        keyIndex.push_back(make_pair(key[i], i));
    }

    // Sort the vector of pairs by key character
    sort(keyIndex.begin(), keyIndex.end());

    // Create a grid to hold the decrypted message
    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    // Fill the grid with the ciphertext
    int index = 0;
    for (auto& pair : keyIndex) {
        int col = pair.second;
        for (int r = 0; r < numRows; r++) {
            if (index < ciphertext.length()) {
                grid[r][col] = ciphertext[index++];
            }
        }
    }

    // Create the plaintext by reading the grid row by row
    string plaintext = "";
    for (int r = 0; r < numRows; r++) {
        for (int c = 0; c < numCols; c++) {
            if (grid[r][c] != ' ') {
                plaintext += grid[r][c];
            }
        }
    }

    return plaintext;
}

int main() {
    string plaintext, ciphertext, decryptedText, key;

    // Input plaintext and key
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);
    
    cout << "Enter the key: ";
    getline(cin, key);

    // Encrypt the message
    ciphertext = encryptAdvancedColumnar(plaintext, key);
    cout << "Encrypted Message: " << ciphertext << endl;

    // Decrypt the message
    decryptedText = decryptAdvancedColumnar(ciphertext, key);
    cout << "Decrypted Message: " << decryptedText << endl;

    return 0;
}


