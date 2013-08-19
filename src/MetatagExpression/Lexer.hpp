#ifndef METATAG_EXPRESSION_LEXER_HPP
#define METATAG_EXPRESSION_LEXER_HPP

#include "Iterator.hpp"
#include "MetatagExpression/Tokenizer.hpp"
#include <list>

class MetatagExpressionLexer_tests;

namespace mru {
namespace MetatagExpression {

struct Token {
  int position;
  UnicodeString value;
  enum TokenKind {
    Text,
    MetatagStart,
    ArgumentListStart,
    ArgumentListEnd,
    AreaOfEffectStart,
    AreaOfEffectEnd,
    EscapeSequence
  } type;

  Token(void) { }
  Token(TokenKind kind)
    : type(kind) { }

  bool operator<(const Token &other) const
  {
    return type < other.type;
  }
};

inline bool
operator==(const MetatagExpression::Token &a, const MetatagExpression::Token &b)
{
  return 
    (a.position == b.position) &&
    (a.value == b.value) &&
    (a.type == b.type);
}

class Lexer : public ConstIterator<Token> {
public:
  friend class ::MetatagExpressionLexer_tests;

public:
  Lexer(Tokenizer::Pointer tokenizer);

  void first(void);
  bool next(void);
  bool atEnd(void) const;
  Token getCurrent(void) const;

private:
  Token::TokenKind determineTokenType(const UnicodeString &word) const;

  const Tokenizer::Pointer tokenizer;
  int in_text_position;
};

} /* namespace MetatagExpression */
} /* namespace mru */

#endif /* METATAG_EXPRESSION_LEXER_HPP */

