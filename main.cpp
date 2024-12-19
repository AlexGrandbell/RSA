#include "BlockCipher.h"

int main() {
//    RSA rsa;
//    rsa.generateKeys("259276829213363391578010383", "162259276829213363391578010288127", "65537");
//    //显示所有元素
//    cout << "p: " << rsa.p << endl;
//    cout << "q: " << rsa.q << endl;
//    cout << "n: " << rsa.n << endl;
//    cout << "m: " << rsa.m << endl;
//    cout << "e: " << rsa.e << endl;
//    cout << "d: " << rsa.d << endl;
//
////    string message = "Hello, World!";
////    cout << "原文: " << message << endl;
////    cout << "原文: " << "123" << endl;
//    cout << "公钥: (n=" << rsa.n << ", e=" << rsa.e << ")" << endl;
//    InfInt encrypted = rsa.encrypt(InfInt("2341545345253141542534123543645"));
////    string encrypted = rsa.encrypt(message);
//    cout << "加密后: " << encrypted << endl;
//    cout << "私钥: (n=" << rsa.n << ", e=" << rsa.d << ")" << endl;
//    InfInt decrypted = rsa.decrypt(encrypted);
//    cout << "解密后: " << decrypted << endl;

    BlockCipher blockCipher;
    blockCipher.encrypt();
    blockCipher.decrypt();
    return 0;
}
