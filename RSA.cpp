//
//Created by AlexGrandbell on 24-12-19.
//

#include "RSA.h"

void RSA::generateKeys(string p, string q, string e) {
    this->p = InfInt(p);
    this->q = InfInt(q);
    this->e = InfInt(e);
    calculateN();
    calculateM();
//    if (e == "0"){
//        findE();
//    } else {
//        this->e = e;
//    }
    calculateD();
}

void RSA::calculateN() {
    n = p*q;
}

void RSA::calculateM() {
    m = (p-1)*(q-1);
}

void RSA::findE() {
//    for (int i = 2; i < stoi(m); i++) {
//        if (gcd(i, stoi(m)) == 1) {
//            e = to_string(i);
//            break;
//        }
//    }
}

void RSA::calculateD() {
    d = modularInverse(e, m);
}

InfInt RSA::encrypt(InfInt beforeMessage) {
    return modExp(beforeMessage, e, n);;
}

InfInt RSA::decrypt(InfInt afterMessage) {
    return modExp(afterMessage, d, n);;
}

void RSA::showD() {
    cout << "p: " << p << endl;
    cout << "q: " << q << endl;
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "e: " << e << endl;
    cout << "d: " << d << endl;
}

//求模逆元素
InfInt RSA::modularInverse(InfInt e, InfInt m) {
    InfInt x, y;
    extendedGCD(e, m, x, y);
    return (x % m + m) % m;
}

//扩展欧几里得算法
InfInt RSA::extendedGCD(InfInt a, InfInt b, InfInt &x, InfInt &y) {
    if (b == InfInt("0")) {
        x = InfInt("1");
        y = InfInt("0");
        return a;
    }
    InfInt x1, y1;
    InfInt gcd = extendedGCD(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

//快速幂算法 (计算 a^b % m)
InfInt RSA::modExp(InfInt base, InfInt exp, InfInt mod) {
    InfInt result = InfInt("1"); //初始结果为1
    InfInt reminder = InfInt("0");
    base = base % mod;

    while (exp>InfInt("0")) { //当 exp > 0 时循环
        if ((exp.number.back() - '0') % 2 == 1) { //如果 exp 是奇数
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp/2;
    }
    return result;
}