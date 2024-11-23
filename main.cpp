#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

void xorEncryptDecrypt(const std::string& inputFile, const std::string& outputFile, const std::string& key) {
    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    char ch;
    size_t keyLength = key.length();
    size_t keyIndex = 0;

    while (inFile.get(ch)) {
        ch ^= key[keyIndex];
        outFile.put(ch);
        keyIndex = (keyIndex + 1) % keyLength;
    }

    inFile.close();
    outFile.close();
}

std::string getFileNameWithoutEncSuffix(const std::string& filePath) {
    if (filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == "-enc") {
        return filePath.substr(0, filePath.size() - 4);
    }
    return filePath;
}

std::string getFileExtension(const std::string& filePath) {
    size_t lastDot = filePath.find_last_of('.');
    if (lastDot == std::string::npos) {
        return ""; 
    }
    return filePath.substr(lastDot); 
}

int main() {
    int choice;
    std::string filePath, password, encryptedFilePath, decryptedFilePath;

    std::cout << "File Encryptor and Decryptor" << std::endl;
    std::cout << "1. Encrypt File" << std::endl;
    std::cout << "2. Decrypt File" << std::endl;
    std::cout << "Choose an option (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter the path to the file to encrypt: ";
        std::cin >> filePath;
        std::cout << "Enter the password (key) for encryption: ";
        std::cin >> password;

        encryptedFilePath = filePath + "-enc";
        xorEncryptDecrypt(filePath, encryptedFilePath, password);

        std::filesystem::remove(filePath);
        std::cout << "File encrypted successfully: " << encryptedFilePath << std::endl;

    }
    else if (choice == 2) {
        std::cout << "Enter the path to the encrypted file: ";
        std::cin >> filePath;
        std::cout << "Enter the password (key) for decryption: ";
        std::cin >> password;

        decryptedFilePath = getFileNameWithoutEncSuffix(filePath);
        xorEncryptDecrypt(filePath, decryptedFilePath, password);

        std::filesystem::remove(filePath);
        std::cout << "File decrypted successfully: " << decryptedFilePath << std::endl;

    }
    else {
        std::cerr << "Invalid choice!" << std::endl;
    }

    return 0;
}
