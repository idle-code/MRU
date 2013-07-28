#ifndef METATAG_EXPRESSION_LEXER_HPP
#define METATAG_EXPRESSION_LEXER_HPP

#include "MetatagExpressionTokenizer.hpp"
#include <list>

class MetatagExpressionLexer_tests;

namespace mru
{

class MetatagExpressionLexer {
public:
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
  };

  typedef std::list<Token> TokenList;

  friend class ::MetatagExpressionLexer_tests;

  static UnicodeString joinTokens(const TokenList &token_list);
public:
  MetatagExpressionLexer(void);
  ~MetatagExpressionLexer(void);

  const TokenList& analyze(const UnicodeString &text);
  UnicodeString joinTokens(void) const;

private:
  typedef MetatagExpressionTokenizer::WordList WordList;

  void addToken(const UnicodeString &value);
  Token::TokenKind determineTokenType(const UnicodeString &word) const;
private:
  TokenList tokens;
  MetatagExpressionTokenizer tokenizer;
  int in_text_position;
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_LEXER_HPP */

