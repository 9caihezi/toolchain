#include "tokenizer.h"

#include <sstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace {

using namespace std;
using testing::DoubleEq;
using testing::Field;
using testing::SizeIs;

TEST(Tokenizer, Simple) {
	istringstream iss("abc  _de0f ge_00zh 09+ 1abc 111.555");
	auto tokens = Tokenize(iss);
	EXPECT_THAT(tokens, ElementsAre(
		Pointee(AllOf(
			Field(&Token::type, TokenType::Identifier),
			Field(&Token::string_value, string("abc")))),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Identifier),
			Field(&Token::string_value, string("_de0f")))),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Identifier),
			Field(&Token::string_value, "ge_00zh"))),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Integer),
			Field(&Token::int_value, 9))),
		Pointee(Field(&Token::type, TokenType::OpPlus)),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Integer),
			Field(&Token::int_value, 1))),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Identifier),
			Field(&Token::string_value, "abc"))),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Float),
			Field(&Token::double_value, DoubleEq(111.555))))));
}

TEST(Tokenizer, NumberAndOperator) {
	istringstream iss("(1+2*3)/4 == 1");
	auto tokens = Tokenize(iss);
	EXPECT_THAT(tokens, ElementsAre(
		Pointee(Field(&Token::type, TokenType::OpOpenParen)),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Integer),
			Field(&Token::int_value, 1))),
		Pointee(Field(&Token::type, TokenType::OpPlus)),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Integer),
			Field(&Token::int_value, 2))),
		Pointee(Field(&Token::type, TokenType::OpMultiply)),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Integer),
			Field(&Token::int_value, 3))),
		Pointee(Field(&Token::type, TokenType::OpCloseParen)),
		Pointee(Field(&Token::type, TokenType::OpDivide)),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Integer),
			Field(&Token::int_value, 4))),
		Pointee(Field(&Token::type, TokenType::OpEqual)),
		Pointee(AllOf(
			Field(&Token::type, TokenType::Integer),
			Field(&Token::int_value, 1)))));
}

} // namespace
