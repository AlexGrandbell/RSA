//
// Created by AlexGrandbell on 24-12-19.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include "InfInt.h"

class RSA {
public:
    //公钥
    InfInt n;
    InfInt e;
    //生成公钥密钥
    void generateKeys(string p, string q,string e="0");
    //加密
    InfInt encrypt(InfInt beforeMessage);
    //解密
    InfInt decrypt(InfInt afterMessage);
    RSA():p("259276829213363391578010383"), q("162259276829213363391578010288127"), m("42070070806731805043869269472474395682032271704705639324132"), n("42070070806731805043869269634733931788074848459675227622641"), e("65537"), d("33192841010032320295533701357747624272190132372658486018161"){}
//private:
    //全部私有确保安全
    InfInt p;
    InfInt q;
    InfInt m;
    //私钥
    InfInt d;

    void calculateN();
    void calculateM();
    void findE();
    void calculateD();

    InfInt extendedGCD(InfInt a, InfInt b,InfInt &x, InfInt &y);
    InfInt modularInverse(InfInt e, InfInt m);
//    int extendedGCD(int a, int b, int &x, int &y);//扩展欧几里得算法
//    int modularInverse(int e, int m);//求模反元素

    InfInt modExp(InfInt base, InfInt exp, InfInt mod);//快速幂算法 (计算 a^b % m)
//    InfInt divideByTwo(const string& num);//除2
};


#endif //RSA_RSA_H
