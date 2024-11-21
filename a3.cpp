#include <iostream>
#include <string>
using namespace std;

// Function to encrypt the text using Vigenère Cipher
string encryptVigenere(string text, string key) {
    string encryptedText = "";
    int keyIndex = 0;

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a'; // Determine if the character is uppercase or lowercase
            char keyChar = key[keyIndex % key.length()]; // Repeat the key as necessary
            int shift = toupper(keyChar) - 'A'; // Shift based on the key character (case-insensitive)

            // Encrypt the character
            char encryptedChar = ((text[i] - offset + shift) % 26) + offset;
            encryptedText += encryptedChar;

            keyIndex++; // Move to the next character in the key
        } else {
            encryptedText += text[i]; // Non-alphabet characters remain unchanged
        }
    }

    return encryptedText;
}

// Function to decrypt the text using Vigenère Cipher
string decryptVigenere(string text, string key) {
    string decryptedText = "";
    int keyIndex = 0;

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a'; // Determine if the character is uppercase or lowercase
            char keyChar = key[keyIndex % key.length()]; // Repeat the key as necessary
            int shift = toupper(keyChar) - 'A'; // Shift based on the key character (case-insensitive)

            // Decrypt the character
            char decryptedChar = ((text[i] - offset - shift + 26) % 26) + offset;
            decryptedText += decryptedChar;

            keyIndex++; // Move to the next character in the key
        } else {
            decryptedText += text[i]; // Non-alphabet characters remain unchanged
        }
    }

    return decryptedText;
}

int main() {
    string message, key, encryptedMessage, decryptedMessage;

    cout << "Enter the message: ";
    getline(cin, message);
    
    cout << "Enter the key: ";
    getline(cin, key);

    // Encrypt the message
    encryptedMessage = encryptVigenere(message, key);
    cout << "Encrypted Message: " << encryptedMessage << endl;

    // Decrypt the message
    decryptedMessage = decryptVigenere(encryptedMessage, key);
    cout << "Decrypted Message: " << decryptedMessage << endl;

    return 0;
}

