//W.A.P. to implement Rail fence technique
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to encrypt the plaintext using Rail Fence Cipher
string encryptRailFence(string text, int key) {
    // Create a 2D array to store the zigzag pattern
    vector<vector<char>> rail(key, vector<char>(text.length(), '\0'));
    
    // Initialize variables
    int row = 0, col = 0;
    bool goingDown = false; // Flag to indicate direction (up or down)
    
    // Fill the rail matrix with characters of the plaintext
    for (int i = 0; i < text.length(); i++) {
        rail[row][col++] = text[i];
        
        // Change direction at the top or bottom rail
        if (row == 0 || row == key - 1) {
            goingDown = !goingDown;
        }
        
        // Move the row up or down
        row += (goingDown ? 1 : -1);
    }

    // Generate the ciphertext by reading the matrix row by row
    string ciphertext = "";
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < text.length(); j++) {
            if (rail[i][j] != '\0') {
                ciphertext += rail[i][j];
            }
        }
    }

    return ciphertext;
}

// Function to decrypt the ciphertext using Rail Fence Cipher
string decryptRailFence(string cipherText, int key) {
    // Create a 2D array to store the zigzag pattern
    vector<vector<char>> rail(key, vector<char>(cipherText.length(), '\0'));
    
    // Initialize variables
    int row = 0, col = 0;
    bool goingDown = false;
    
    // Mark the positions where the characters of the ciphertext should be placed
    for (int i = 0; i < cipherText.length(); i++) {
        rail[row][col++] = '*'; // Mark positions
        if (row == 0 || row == key - 1) {
            goingDown = !goingDown;
        }
        row += (goingDown ? 1 : -1);
    }

    // Fill the rail matrix with the ciphertext
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < cipherText.length(); j++) {
            if (rail[i][j] == '*' && index < cipherText.length()) {
                rail[i][j] = cipherText[index++];
            }
        }
    }

    // Read the matrix row by row to get the decrypted message
    string decryptedText = "";
    row = 0, col = 0;
    for (int i = 0; i < cipherText.length(); i++) {
        decryptedText += rail[row][col++];
        if (row == 0 || row == key - 1) {
            goingDown = !goingDown;
        }
        row += (goingDown ? 1 : -1);
    }

    return decryptedText;
}

int main() {
    string text;
    int key;

    // Input plaintext and key
    cout << "Enter the plaintext: ";
    getline(cin, text);
    
    cout << "Enter the key (number of rails): ";
    cin >> key;

    // Encrypt the message
    string encryptedText = encryptRailFence(text, key);
    cout << "Encrypted Message: " << encryptedText << endl;

    // Decrypt the message
    string decryptedText = decryptRailFence(encryptedText, key);
    cout << "Decrypted Message: " << decryptedText << endl;

    return 0;
}

