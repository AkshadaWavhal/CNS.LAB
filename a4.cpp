#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

// Function to find the inverse of a 2x2 matrix modulo 26
bool inverseMatrix2x2(vector<vector<int>>& matrix, vector<vector<int>>& invMatrix) {
    int determinant = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    if (determinant == 0 || std::gcd(determinant, 26) != 1) {
        cout << "Matrix is not invertible." << endl;
        return false;
    }
    
    int detInv = 0;
    // Find modular inverse of determinant mod 26
    for (int i = 1; i < 26; i++) {
        if ((determinant * i) % 26 == 1) {
            detInv = i;
            break;
        }
    }

    invMatrix[0][0] = (detInv * matrix[1][1]) % 26;
    invMatrix[0][1] = (-detInv * matrix[0][1]) % 26;
    invMatrix[1][0] = (-detInv * matrix[1][0]) % 26;
    invMatrix[1][1] = (detInv * matrix[0][0]) % 26;

    // Adjust negative values to be positive in modulo 26
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (invMatrix[i][j] < 0) {
                invMatrix[i][j] += 26;
            }
        }
    }

    return true;
}

// Function to multiply a 2x2 matrix with a vector and return the result mod 26
vector<int> multiplyMatrixVector(vector<vector<int>>& matrix, vector<int>& vec) {
    vector<int> result(2);
    for (int i = 0; i < 2; i++) {
        result[i] = 0;
        for (int j = 0; j < 2; j++) {
            result[i] = (result[i] + matrix[i][j] * vec[j]) % 26;
        }
    }
    return result;
}

// Function to encrypt a message using Hill Cipher
string encryptHill(string plaintext, vector<vector<int>>& keyMatrix) {
    // Ensure plaintext is in uppercase and handle non-alphabet characters
    for (char &ch : plaintext) {
        if (isalpha(ch)) {
            ch = toupper(ch);
        }
    }

    string ciphertext = "";
    vector<int> plainVec(2);

    // Process the plaintext in blocks of 2 characters
    for (size_t i = 0; i < plaintext.length(); i += 2) {
        // Fill the vector with corresponding letter values (A=0, B=1, ..., Z=25)
        plainVec[0] = plaintext[i] - 'A';
        if (i + 1 < plaintext.length()) {
            plainVec[1] = plaintext[i + 1] - 'A';
        } else {
            plainVec[1] = 'X' - 'A';  // If there's a single character, pad with 'X'
        }

        // Encrypt the block by multiplying with the key matrix
        vector<int> encryptedVec = multiplyMatrixVector(keyMatrix, plainVec);

        // Convert the result back to characters
        ciphertext += (encryptedVec[0] + 'A');
        ciphertext += (encryptedVec[1] + 'A');
    }

    return ciphertext;
}

// Function to decrypt a message using Hill Cipher
string decryptHill(string ciphertext, vector<vector<int>>& keyMatrix) {
    string plaintext = "";
    vector<int> cipherVec(2);
    
    // Find the inverse of the key matrix
    vector<vector<int>> invMatrix(2, vector<int>(2));
    if (!inverseMatrix2x2(keyMatrix, invMatrix)) {
        return "Decryption failed due to non-invertible matrix.";
    }

    // Process the ciphertext in blocks of 2 characters
    for (size_t i = 0; i < ciphertext.length(); i += 2) {
        // Fill the vector with corresponding letter values (A=0, B=1, ..., Z=25)
        cipherVec[0] = ciphertext[i] - 'A';
        cipherVec[1] = ciphertext[i + 1] - 'A';

        // Decrypt the block by multiplying with the inverse of the key matrix
        vector<int> decryptedVec = multiplyMatrixVector(invMatrix, cipherVec);

        // Convert the result back to characters
        plaintext += (decryptedVec[0] + 'A');
        plaintext += (decryptedVec[1] + 'A');
    }

    return plaintext;
}

int main() {
    // Define the key matrix for Hill Cipher (2x2)
    vector<vector<int>> keyMatrix = {{6, 24}, {1, 16}};  // Example matrix

    string plaintext, ciphertext, decryptedText;

    // Input plaintext
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    // Encrypt the message
    ciphertext = encryptHill(plaintext, keyMatrix);
    cout << "Encrypted Message: " << ciphertext << endl;

    // Decrypt the message
    decryptedText = decryptHill(ciphertext, keyMatrix);
    cout << "Decrypted Message: " << decryptedText << endl;

    return 0;
}

