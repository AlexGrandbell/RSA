//
// Created by AlexGrandbell on 24-12-19.
//

#ifndef RSA_INFINT_H
#define RSA_INFINT_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

//大数类
class InfInt {
public:
    bool negative; //是否为负数
    string number; //存储大数的字符串
    //构造函数
    InfInt(string num = "0") {
        negative = (num[0] == '-');
        number = negative ? num.substr(1) : num;
        while (number.size() > 1 && number[0] == '0') {
            number.erase(0, 1);
        }
    }

    //重载运算符
    InfInt operator+(const InfInt& num) const;
    InfInt operator-(const InfInt& num) const;
    InfInt operator*(const InfInt& num) const;
    InfInt operator/(const InfInt& num) const;
    InfInt operator%(const InfInt& num) const;

    //重载比较运算符
    bool operator<(const InfInt& num) const;
    bool operator>(const InfInt& num) const;
    bool operator<=(const InfInt& num) const;
    bool operator>=(const InfInt& num) const;
    bool operator==(const InfInt& num) const;
    bool operator!=(const InfInt& num) const;

    //兼容与int的运算
    InfInt operator+(int num) const;
    InfInt operator-(int num) const;
    InfInt operator*(int num) const;
    InfInt operator/(int num) const;
    InfInt operator%(int num) const;

    //重载输入输出运算符
    friend istream& operator>>(istream& in, InfInt& num) {
        string str;
        in >> str;
        num = InfInt(str);
        return in;
    }
    friend ostream& operator<<(ostream& out, const InfInt& num) {
        if (num.negative) out << '-';
        out << num.number;
        return out;
    }
private:
    //辅助函数：比较两个正整数字符串
    static int compareAbsolute(const string& num1, const string& num2) {
        //去除前导零
        string n1 = num1, n2 = num2;
        while (n1.size() > 1 && n1[0] == '0') {
            n1.erase(0, 1);
        }
        while (n2.size() > 1 && n2[0] == '0') {
            n2.erase(0, 1);
        }

        //先比较长度
        if (n1.size() > n2.size()) return 1;
        if (n1.size() < n2.size()) return -1;

        //长度相同，逐位比较
        for (size_t i = 0; i < num1.size(); ++i) {
            if (n1[i] > n2[i]) return 1;
            if (n1[i] < n2[i]) return -1;
        }

        //完全相等
        return 0;
    }
    //辅助函数：加法
    static string addAbsolute(const string& num1, const string& num2) {
        string result;
        int carry = 0;
        int i = num1.size() - 1, j = num2.size() - 1;
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) sum += num1[i--] - '0';
            if (j >= 0) sum += num2[j--] - '0';
            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        reverse(result.begin(), result.end());
        return result;
    }

    //辅助函数：减法（num1 >= num2）
    static string subtractAbsolute(const string& num1, const string& num2) {
        string result;
        int borrow = 0;
        int i = num1.size() - 1, j = num2.size() - 1;
        while (i >= 0 || j >= 0) {
            int diff = (num1[i--] - '0') - (j >= 0 ? num2[j--] - '0' : 0) - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push_back(diff + '0');
        }
        while (result.size() > 1 && result.back() == '0') result.pop_back();
        reverse(result.begin(), result.end());
        return result;
    }
};


#endif //RSA_INFINT_H
