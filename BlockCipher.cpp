//
// Created by AlexGrandbell on 24-12-19.
//

#include "BlockCipher.h"

void BlockCipher::encrypt() {
    cout << "正在读取原文: "<<endl;
    //从文件读取原文
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        original += line + '\n';
    }
    file.close();
    cout << "原文: " << original << endl;
    string originalDigital = wordToDigital(original);
    cout << "原文转换成数字后为: " << originalDigital << endl;
    vector<InfInt> blocks = splitDigital(originalDigital);
    for (InfInt block : blocks) {
        encrypted += rsa.encrypt(block).number + "&";
    }
    cout << "加密后的字符串: " << encrypted << endl;
    //写入文件
    ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }
    outFile << encrypted;
    outFile.close();
    cout << "加密后的数字已写入output.txt" << endl;
}

void BlockCipher::decrypt() {
    cout << "正在解密... "<<endl;
    string decrypted;
    vector<InfInt> blocks = splitEncrypted();
    for (InfInt block : blocks) {
        decrypted += rsa.decrypt(block).number;
    }
    cout << "解密后的数字: " << decrypted << endl;
    //分三位还原字符串，如果开头是2则删去2
    string decryptedWord;
    for (int i = 0; i < decrypted.length(); i += 3) {
        string word = decrypted.substr(i, 3);
        if (word[0] == '2') {
            word.erase(0, 1);
        }
        decryptedWord += static_cast<char>(stoi(word));
    }
    cout << "解密后的字符串: " << decryptedWord << endl;
    //写入文件
    ofstream outFile("decrypt.txt");
    if (!outFile.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }
    outFile << decryptedWord;
    outFile.close();
    cout << "解密后的字符串已写入decrypt.txt" << endl;
}

string BlockCipher::wordToDigital(string word) {
    string digital;
    cout << "字符串大小为: "<<word.size()<<endl;
    for (char ch : word) {
        string sm1 = to_string(static_cast<int>(static_cast<unsigned char>(ch)));
        while (sm1.size()<3){
            sm1="2"+sm1;
        }
        digital+=sm1;
    }
    return digital;
}

vector<InfInt> BlockCipher::splitDigital(string digital,int size) {
    vector<InfInt> blocks;
    int length = digital.length();
    for (int i = 0; i < length; i += size) {
        blocks.push_back(InfInt(digital.substr(i, size)));
    }
    return blocks;
}

vector<InfInt> BlockCipher::splitEncrypted() {
    vector<InfInt> blocks;
    size_t pos = 0;
    while ((pos = encrypted.find("&")) != string::npos) {
        string block = encrypted.substr(0, pos);
        blocks.push_back(InfInt(block));
        encrypted.erase(0, pos + 1);
    }
    return blocks;
}