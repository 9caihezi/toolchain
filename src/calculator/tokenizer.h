#ifndef CALCULATOR_TOKENIZER_H
#define CALCULATOR_TOKENIZER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum TokenType {
    Identifier,
    Integer,
    Float,
    OpPlus,
    OpMinus,
    OpMultiply,
    OpDivide,
    OpEqual,
    OpOpenParen,
    OpCloseParen,
    //WhiteSpace,
    Error,
};

struct Token {
    TokenType type;
    std::string string_value;
    int int_value;
    double double_value;
    size_t row;
    size_t col;
};

std::vector<std::unique_ptr<Token>> Tokenize(std::istream& input);

#endif // CALCULATOR_TOKENIZER_H
