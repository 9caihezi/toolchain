#include "tokenizer.h"

#include <cassert>
#include <cctype>
#include <deque>
#include <memory>
#include <string>
#include <vector>

using std::deque;
using std::istream;
using std::string;
using std::unique_ptr;
using std::vector;

class Dfa {
public:
    // Append a charactor. return if still valid.
    virtual bool AddChar(char c) = 0;
    virtual std::unique_ptr<Token> Finalize() = 0;
    virtual bool Finalizable() { return true; }
    virtual void Reset() {
        data_.clear();
    }
protected:
    string data_;
};

deque<Dfa*> GetAllDfa();

void AddChar(deque<Dfa*>& valid_dfa, char c) {
    for (auto p = valid_dfa.begin(); p != valid_dfa.end();) {
        if (!(*p)->AddChar(c)) {
            p = valid_dfa.erase(p);
        } else {
            ++p;
        }
    }
}

std::unique_ptr<Token> MakeToken(
        TokenType type, string data) {
    std::unique_ptr<Token> t = unique_ptr<Token>(new Token);
    t->type = type;
    t->string_value = std::move(data);
    return t;
}

Dfa* find_valid_dfa(deque<Dfa*> valid_dfa) {
    assert(valid_dfa.size() > 0);
    for (auto dfa : valid_dfa) {
        if (dfa->Finalizable()) {
            return dfa;
        }
    }
    return valid_dfa[0];
}

vector<std::unique_ptr<Token>> Tokenize(istream& input) {
    char c;
    bool init = true;
    bool finalize = false;
    size_t row = 0;
    size_t col = 0;
    deque<Dfa*> valid_dfa = GetAllDfa();
    vector<std::unique_ptr<Token>> result;

    while(input.get(c) || !finalize) {
        if (!input) {
            // the last run
            finalize = true;
            c = ' ';
        }
        assert(valid_dfa.size() > 0);
        Dfa* last_valid = find_valid_dfa(valid_dfa);
        AddChar(valid_dfa, c);

        if (init) {
            if (valid_dfa.empty()) {
                result.push_back(MakeToken(TokenType::Error, string(1, c)));
                valid_dfa = GetAllDfa();
            } else {
                init = false;
            }
        } else {
            if (valid_dfa.empty()) {
                result.push_back(last_valid->Finalize());
                if (!result.back()) {
                    result.pop_back();
                }
                valid_dfa = GetAllDfa();
                input.putback(c);
                init = true;
            }
        }
    }

	return result;
}

class WhiteSpaceDfa : public Dfa {
public:
    bool AddChar(char c) override {
        if (!std::isspace(c)) {
            return false;
        }
        data_ += c;
        return true;
    }
    std::unique_ptr<Token> Finalize() override {
        return nullptr;
    }
    void Reset() override {
        data_.clear();
    }
};

class IdentifierDfa : public Dfa {
public:
    bool AddChar(char c) override {
        if (init_) {
            if (std::isalpha(c) || c == '_') {
                data_ += c;
                init_ = false;
                return true;
            }
        } else {
            if (std::isalnum(c) || c == '_') {
                data_ += c;
                return true;
            }
        }
        return false;
    }
    std::unique_ptr<Token> Finalize() override {
        return MakeToken(TokenType::Identifier, std::move(data_));
    }
    void Reset() override {
        init_ = true;
        data_.clear();
    }
private:
    bool init_ = true;
};

class IntegerDfa : public Dfa {
public:
    bool AddChar(char c) override {
        if ('0' <= c && c <= '9') {
            value_ *= 10;
            value_ += c - '0';
            return true;
        }
        return false;
    }
    std::unique_ptr<Token> Finalize() override {
        std::unique_ptr<Token> t = unique_ptr<Token>(new Token);
        t->type = TokenType::Integer;
        t->int_value = value_;
        return t;
    }
    void Reset() override {
        value_ = 0;
    }
private:
    int value_;
};

class FloatDfa : public Dfa {
public:
    bool AddChar(char c) override {
        data_ += c;
        if (!after_dot_) {
            if ('0' <= c && c <= '9') {
                value_ *= 10;
                value_ += c - '0';
                return true;
            } else if (c == '.') {
                after_dot_ = true;
                return true;
            }
        } else {
            if ('0' <= c && c <= '9') {
                decimal_part_ /= 10;
                value_ += decimal_part_ * (c - '0');
                return true;
            }
        }
        return false;
    }
    std::unique_ptr<Token> Finalize() override {
        if (Finalizable()) {
            std::unique_ptr<Token> t = unique_ptr<Token>(new Token);
            t->type = TokenType::Float;
            t->double_value = value_;
            return t;
        } else {
			return MakeToken(TokenType::Error, std::move(data_));
        }
    }
    bool Finalizable() override {
        return after_dot_;
    }
    void Reset() override {
        after_dot_ = false;
        decimal_part_ = 1;
        value_ = 0;
        data_.clear();
    }
private:
    bool after_dot_;
    double decimal_part_;
    double value_;
};

/*
class ExactMatchDfa : public Dfa {
}
*/


deque<Dfa*> GetAllDfa() {
	static vector<std::unique_ptr<Dfa>> dfa_list;
	if (dfa_list.empty()) {
		dfa_list.emplace_back(new WhiteSpaceDfa());
		dfa_list.emplace_back(new IdentifierDfa());
		dfa_list.emplace_back(new IntegerDfa());
		dfa_list.emplace_back(new FloatDfa());
	}
    deque<Dfa*> result;
    for (const auto& uptr : dfa_list) {
        Dfa* p = uptr.get();
        result.push_back(p);
        p->Reset();
    }
    return result;
}
