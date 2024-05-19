#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

class Message {
private:
    std::string encryptedMessage;
    std::string decryptedMessage;
    std::string key;

    std::string generateRandomKey(size_t length);
    std::string encrypt(const std::string& plaintext, const std::string& key);
    std::string decrypt(const std::string& ciphertext, const std::string& key);

public:
    explicit Message(size_t keyLength = 16);

    void encryptMessage(const std::string& plaintext);
    void decryptMessage(const std::string& ciphertext);

    std::string getEncryptedMessage() const;
    std::string getDecryptedMessage() const;
    std::string getKey() const;
};

#endif // MESSAGE_HPP

