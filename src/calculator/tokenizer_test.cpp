#include "tokenizer.h"

#include <sstream>

#include "gtest/gtest.h"

namespace {

using namespace std;

TEST(Tokenizer, Simple) {
	istringstream iss("abc  _de0f ge_00zh 09+ 1abc 111.555");
	auto tokens = Tokenize(iss);
	EXPECT_EQ(tokens.size(), 8);
	EXPECT_EQ(tokens[0]->type, TokenType::Identifier);
	EXPECT_EQ(tokens[0]->string_value, "abc");
	EXPECT_EQ(tokens[1]->type, TokenType::Identifier);
	EXPECT_EQ(tokens[1]->string_value, "_de0f");
	EXPECT_EQ(tokens[2]->type, TokenType::Identifier);
	EXPECT_EQ(tokens[2]->string_value, "ge_00zh");
	EXPECT_EQ(tokens[3]->type, TokenType::Integer);
	EXPECT_EQ(tokens[3]->int_value, 9);
	EXPECT_EQ(tokens[4]->type, TokenType::Error);
	EXPECT_EQ(tokens[4]->string_value, "+");
	EXPECT_EQ(tokens[5]->type, TokenType::Integer);
	EXPECT_EQ(tokens[5]->int_value, 1);
	EXPECT_EQ(tokens[6]->type, TokenType::Identifier);
	EXPECT_EQ(tokens[6]->string_value, "abc");
	EXPECT_EQ(tokens[7]->type, TokenType::Float);
	EXPECT_DOUBLE_EQ(tokens[7]->double_value, 111.555);
}

} // namespace
