//
// Created by AlexGrandbell on 24-12-19.
//

#ifndef RSA_BLOCKCIPHER_H
#define RSA_BLOCKCIPHER_H

#include "RSA.h"
#include <fstream>


//对原文进行Unicode数字转换后分割RSA加密
class BlockCipher {
public:
    RSA rsa;
    string original;
    string encrypted;

    void encrypt();//输入字符串，转数字后最多size字符一组
    void decrypt();
private:
    string wordToDigital(string);//将原文转为数字
    vector<InfInt> splitDigital(string,int size=45);//将数字分割成45位一组
    vector<InfInt> splitEncrypted();
};


#endif //RSA_BLOCKCIPHER_H
