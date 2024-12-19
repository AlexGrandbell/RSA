//
//Created by AlexGrandbell on 24-12-19.
//

#include "InfInt.h"

InfInt InfInt::operator+(const InfInt &num) const {
    if (negative == num.negative) {
        return InfInt((negative ? "-" : "") + addAbsolute(number, num.number));
    }
    int cmp = compareAbsolute(number, num.number);
    if (cmp >= 0) {
        return InfInt((negative ? "-" : "") + subtractAbsolute(number, num.number));
    } else {
        return InfInt((num.negative ? "-" : "") + subtractAbsolute(num.number, number));
    }
}

InfInt InfInt::operator-(const InfInt &num) const {
    if (negative != num.negative) {
        return InfInt((negative ? "-" : "") + addAbsolute(number, num.number));
    }
    int cmp = compareAbsolute(number, num.number);
    if (cmp >= 0) {
        return InfInt((negative ? "-" : "") + subtractAbsolute(number, num.number));
    } else {
        return InfInt((negative ? "" : "-") + subtractAbsolute(num.number, number));
    }
}

InfInt InfInt::operator*(const InfInt &num) const {
    vector<int> result(number.size() + num.number.size(), 0);
    for (int i = number.size() - 1; i >= 0; --i) {
        for (int j = num.number.size() - 1; j >= 0; --j) {
            int mul = (number[i] - '0') * (num.number[j] - '0') + result[i + j + 1];
            result[i + j + 1] = mul % 10;
            result[i + j] += mul / 10;
        }
    }
    string resultStr;
    for (int num : result) if (!(resultStr.empty() && num == 0)) resultStr.push_back(num + '0');
    if (resultStr.empty()) resultStr = "0";
    if (negative != num.negative) resultStr = "-" + resultStr;
    return InfInt(resultStr);
}

InfInt InfInt::operator/(const InfInt &num) const {
    if (num.number == "0") throw invalid_argument("除0错误");
    string dividend = number, divisor = num.number, result;
    if (compareAbsolute(dividend, divisor) < 0) return InfInt("0");
    string current;
    for (char digit : dividend) {
        current += digit;
        int count = 0;
        while (compareAbsolute(current, divisor) >= 0) {
            current = subtractAbsolute(current, divisor);
            count++;
        }
        result.push_back(count + '0');
    }
    while (result.size() > 1 && result[0] == '0') result.erase(0, 1);
    if (negative != num.negative) result = "-" + result;
    return InfInt(result);
}

InfInt InfInt::operator%(const InfInt &num) const {
    if (num.number == "0") throw invalid_argument("Modulo by zero");
    string dividend = number, divisor = num.number;
    if (compareAbsolute(dividend, divisor) < 0) return *this;
    string current;
    for (char digit : dividend) {
        current += digit;
        while (compareAbsolute(current, divisor) >= 0) {
            current = subtractAbsolute(current, divisor);
        }
    }
    if (negative) current = "-" + current;
    return InfInt(current.empty() ? "0" : current);
}

bool InfInt::operator<(const InfInt &num) const {
    if (negative != num.negative) {
        return negative;  //负数总是小于正数
    }
    int cmp = compareAbsolute(number, num.number);
    return negative ? (cmp > 0) : (cmp < 0);  //负数时绝对值大的更小
}

bool InfInt::operator>(const InfInt &num) const {
    return num < *this;  //利用已实现的 <
}

bool InfInt::operator<=(const InfInt &num) const {
    return !(num < *this);  //利用已实现的 <
}

bool InfInt::operator>=(const InfInt &num) const {
    return !(*this < num);  //利用已实现的 <
}

bool InfInt::operator==(const InfInt &num) const {
    return negative == num.negative && number == num.number;
}

bool InfInt::operator!=(const InfInt &num) const {
    return !(*this == num);  //利用已实现的 ==
}

//重载与 int 的加法
InfInt InfInt::operator+(int num) const {
    return *this + InfInt(to_string(num));
}

//重载与 int 的减法
InfInt InfInt::operator-(int num) const {
    return *this - InfInt(to_string(num));
}

//重载与 int 的乘法
InfInt InfInt::operator*(int num) const {
    return *this * InfInt(to_string(num));
}

//重载与 int 的除法
InfInt InfInt::operator/(int num) const {
    if (num == 0) throw invalid_argument("Division by zero");
    return *this / InfInt(to_string(num));
}

//重载与 int 的取模
InfInt InfInt::operator%(int num) const {
    if (num == 0) throw invalid_argument("Modulo by zero");
    return *this % InfInt(to_string(num));
}