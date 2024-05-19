//
// Created by manar on 5/16/24.
//
#include "Message.h"
#include <random>

// Generate a random key of given length
std::string Message::generateRandomKey(size_t length) {
    std::string key;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255); // ASCII range

    for (size_t i = 0; i < length; ++i) {
        key.push_back(static_cast<char>(dis(gen)));
    }

    return key;
}

// Encrypt plaintext using the key
std::string Message::encrypt(const std::string& plaintext, const std::string& key) {
    std::string ciphertext;

    for (size_t i = 0; i < plaintext.length(); ++i) {
        ciphertext += plaintext[i] ^ key[i % key.length()];
    }

    return ciphertext;
}
/*--------------------------------------------------------------------------------------------------------------------*/

// Decrypt ciphertext using the key
std::string Message::decrypt(const std::string& ciphertext, const std::string& key) {
    return encrypt(ciphertext, key); // XOR encryption and decryption are symmetric
}
/*--------------------------------------------------------------------------------------------------------------------*/

// Constructor with optional key length parameter
Message::Message(size_t keyLength) {
    key = generateRandomKey(keyLength);
}
/*--------------------------------------------------------------------------------------------------------------------*/

// Method to encrypt a message and save it
void Message::encryptMessage(const std::string& plaintext) {
    encryptedMessage = encrypt(plaintext, key);
    decryptedMessage = decrypt(encryptedMessage, key);
}
/*--------------------------------------------------------------------------------------------------------------------*/

// Method to decrypt a message and save it
void Message::decryptMessage(const std::string& ciphertext) {
    encryptedMessage = ciphertext;
    decryptedMessage = decrypt(ciphertext, key);
}
/*--------------------------------------------------------------------------------------------------------------------*/

// Getter methods
std::string Message::getEncryptedMessage() const {
    return encryptedMessage;
}
/*--------------------------------------------------------------------------------------------------------------------*/

std::string Message::getDecryptedMessage() const {
    return decryptedMessage;
}
/*--------------------------------------------------------------------------------------------------------------------*/

std::string Message::getKey() const {
    return key;
}
