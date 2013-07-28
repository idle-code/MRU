#include "MetatagExpression.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

namespace mru
{

MetatagExpression::Tokenizer::Tokenizer(void)
  : position_in_expression(0)
{ }

MetatagExpression::Tokenizer::Tokenizer(const UnicodeString &expression_text)
  : position_in_expression(0)
{
  tokenize(expression_text);
}

void
MetatagExpression::Tokenizer::pushToken(UnicodeString &text_value, int offset)
{
  if (text_value.isEmpty())
    return;
  token_list.push_back(Token(position_in_expression - text_value.length() + offset, text_value, Token::Text));
  text_value = UnicodeString();
}

void
MetatagExpression::Tokenizer::pushToken(Token::TokenKind type, int offset)
{
  token_list.push_back(Token(position_in_expression + offset, type, type));
}

const std::list<MetatagExpression::Tokenizer::Token> &
MetatagExpression::Tokenizer::tokenize(const UnicodeString &expression_text)
{
  token_list.clear();
  position_in_expression = 0;
  UnicodeString text_value = UnicodeString();
  icu::StringCharacterIterator iter(expression_text);
  bool escape_next = false;

  for(UChar current_char = iter.first(); iter.hasNext(); ++position_in_expression, current_char = iter.next()) {
    Token::TokenKind token_kind = Token::specifyCharacterType(current_char);

    if (escape_next) {
      escape_next = false;
      if (token_kind == Token::Text) {
        text_value += UChar('\\');
      } else {
        pushToken(text_value, -1);
        pushToken(Token::EscapeSequence, -1);
      } 
      text_value += current_char;
    } else {
      if (token_kind == Token::Text) {
        text_value += current_char;
      } else if (token_kind == Token::EscapeSequence) {
        escape_next = true;
      } else {
        pushToken(text_value);
        pushToken(token_kind);
      } 
    }
  }

  pushToken(text_value);

  return token_list;
}

const std::list<MetatagExpression::Tokenizer::Token> &
MetatagExpression::Tokenizer::getTokens(void) const
{
  return token_list;
}

/* ------------------------------------------------------------------------- */

MetatagExpression::Tokenizer::Token::Token(int tok_position, const UnicodeString &tok_value, TokenKind tok_type)
  : position(tok_position), value(tok_value), type(tok_type)
{ }

MetatagExpression::Tokenizer::Token::TokenKind
MetatagExpression::Tokenizer::Token::specifyCharacterType(UChar character)
{
  switch (character) {
    case UChar('%'):
    case UChar('('):
    case UChar(')'):
    case UChar('{'):
    case UChar('}'):
    case UChar('\\'):
      return character;
    default:
      return Text;
  }
}

} /* namespace mru */

