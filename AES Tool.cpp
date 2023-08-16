#include <iostream>
#include <fstream>
#include <string>
#include <openssl/aes.h>

const int AES_KEY_SIZE = 256;
const int BLOCK_SIZE = AES_BLOCK_SIZE;

// Generate a random encryption key
void generateKey(unsigned char *key) {
    // In a real-world scenario, use a secure random number generator
    for (int i = 0; i < AES_KEY_SIZE / 8; ++i) {
        key[i] = static_cast<unsigned char>(rand() % 256);
    }
}

// Encrypt a file using AES algorithm
void encryptFile(const std::string &inputFilename, const std::string &outputFilename, const unsigned char *key) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, AES_KEY_SIZE, &aesKey);

    std::ifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename, std::ios::binary);

    unsigned char inBlock[BLOCK_SIZE];
    unsigned char outBlock[BLOCK_SIZE];

    while (inputFile) {
        inputFile.read(reinterpret_cast<char *>(inBlock), BLOCK_SIZE);
        int bytesRead = inputFile.gcount();

        AES_encrypt(inBlock, outBlock, &aesKey);

        outputFile.write(reinterpret_cast<char *>(outBlock), bytesRead);
    }
}

// Decrypt a file using AES algorithm
void decryptFile(const std::string &inputFilename, const std::string &outputFilename, const unsigned char *key) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, AES_KEY_SIZE, &aesKey);

    std::ifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename, std::ios::binary);

    unsigned char inBlock[BLOCK_SIZE];
    unsigned char outBlock[BLOCK_SIZE];

    while (inputFile) {
        inputFile.read(reinterpret_cast<char *>(inBlock), BLOCK_SIZE);
        int bytesRead = inputFile.gcount();

        AES_decrypt(inBlock, outBlock, &aesKey);

        outputFile.write(reinterpret_cast<char *>(outBlock), bytesRead);
    }
}

int main() {
    unsigned char key[AES_KEY_SIZE / 8];
    generateKey(key);

    std::string inputFile = "input.txt";
    std::string encryptedFile = "encrypted.bin";
    std::string decryptedFile = "decrypted.txt";

    encryptFile(inputFile, encryptedFile, key);
    decryptFile(encryptedFile, decryptedFile, key);

    std::cout << "File encryption/decryption completed." << std::endl;

    return 0;
}
