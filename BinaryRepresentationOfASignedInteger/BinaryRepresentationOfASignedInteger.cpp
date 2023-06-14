
#include <iostream>
#include <string>
#include <limits>

std::string numberToBinary(int number);
void invertBinaryNumber(std::string& binaryNumber);
void binaryNumberMinusOne(std::string& binaryNumber);

std::string numberToBinary(int number)
{
    if (number == std::numeric_limits<int>::min())
    {
        return "-1" + std::string(std::numeric_limits<int>::digits, '0');
    }
    std::string buffer;
    buffer.reserve(std::numeric_limits<int>::digits + 1); 

    bool negative = (number < 0);
    if (negative)
        number = -number;
    do
    {
        buffer += char('0' + number % 2);
        number = number / 2;
    } while (number > 0);
    if (negative)
    {
        buffer += '-';
    }
    return std::string(buffer.crbegin(), buffer.crend());
}

// Преобразование целого знакового числа в число в бинарном представлении с использованием дополнительного кода для обозначения знака
std::string numToBinaryWithAddCode(int number)
{
    if (number == std::numeric_limits<int>::min())
    {
        return "-1" + std::string(std::numeric_limits<int>::digits, '0');
    }
    std::string buffer;
    buffer.reserve(std::numeric_limits<int>::digits + 1);

    bool negative = (number < 0);
    if (negative)
        number = -number;
    do
    {
        buffer += char('0' + number % 2);
        number = number / 2;
    } while (number > 0);

    std::reverse(buffer.begin(), buffer.end());
    if (negative)
    {
        invertBinaryNumber(buffer);

        binaryNumberMinusOne(buffer);

        buffer.insert(buffer.begin(), '1');
    }
    return buffer;
}

void invertBinaryNumber(std::string& binaryNumber)
{
    for (int currentChar = 0; currentChar < binaryNumber.length(); currentChar++)
    {
        binaryNumber[currentChar] = (binaryNumber[currentChar] == '0') ? '1' : '0';
    }
    int currentChar = 0;
    while (binaryNumber[currentChar] != '1')
    {
        currentChar++;
    }
    binaryNumber.erase(0, currentChar);
}

void binaryNumberMinusOne(std::string& binaryNumber)
{
    int currentChar = binaryNumber.length();
    while (binaryNumber[currentChar] != '1')  
    {
        currentChar--;
    }
    binaryNumber[currentChar] = '0';
    for (size_t i = currentChar + 1; i < binaryNumber.length(); i++)
    {
        binaryNumber[i] = '1';
    }
}