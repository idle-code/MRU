#include "MetatagExpression/Lexer.hpp"

namespace mru {
namespace MetatagExpression {

Lexer::Lexer(Tokenizer::Pointer tokenizer)
  : tokenizer(tokenizer), in_text_position(0)
{
  assert(tokenizer);
}

void
Lexer::first(void)
{
  tokenizer->first();
  in_text_position = 0;
}

bool
Lexer::next(void)
{
  assert(!atEnd());
  in_text_position += tokenizer->getCurrent().length();
  return tokenizer->next();
}

bool
Lexer::atEnd(void) const
{
  return tokenizer->atEnd();
}

Token
Lexer::getCurrent(void) const
{
  assert(!atEnd());
  Token token;
  token.position = in_text_position;
  token.value = tokenizer->getCurrent();
  token.type = determineTokenType(token.value);

  return token;
}

Token::TokenKind
Lexer::determineTokenType(const UnicodeString &word) const
{
  if (word.length() > 1)
    return Token::Text;

  switch(word[0]) {
    case UChar('%'):
      return Token::MetatagStart;
    case UChar('('):
      return Token::ArgumentListStart;
    case UChar(')'):
      return Token::ArgumentListEnd;
    case UChar('{'):
      return Token::AreaOfEffectStart;
    case UChar('}'):
      return Token::AreaOfEffectEnd;
    case UChar('\\'):
      return Token::EscapeSequence;
    default:
      return Token::Text;
  }
}

} /* namespace MetatagExpression  */
} /* namespace mru */

