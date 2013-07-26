#include "MetatagExpression.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

namespace mru
{

MetatagExpression::MetatagExpression(void)
{ }

MetatagExpression::MetatagExpression(const UnicodeString &expression_text)
{
  parse(expression_text);
}

MetatagExpression::~MetatagExpression(void)
{ }

void
MetatagExpression::parse(const UnicodeString &expression_text)
{
  tokens = tokenize(expression_text);
  

}

UnicodeString
MetatagExpression::text(void) const
{
  UnicodeString expression_text;
  for(std::list<Token>::const_iterator i = tokens.begin(); i != tokens.end(); ++i) {
    expression_text += (*i).value;
  }
  return expression_text;
}

bool
MetatagExpression::isValid(void) const
{
  return root_entry;
}

/* ------------------------------------------------------------------------- */

MetatagExpression::Token::Token(void)
{ }

MetatagExpression::Token::Token(const UnicodeString &tok_value, TokenKind tok_type)
  : value(tok_value), type(tok_type)
{ }

std::list<MetatagExpression::Token>
MetatagExpression::tokenize(const UnicodeString &expression_text) const
{
  std::list<Token> token_list;
  UnicodeString text_value = UnicodeString();
  icu::StringCharacterIterator iter(expression_text);
  int position = 0;
  bool escape_next = false;

  for(UChar current_char = iter.first(); iter.hasNext(); ++position, current_char = iter.next()) {
    if (escape_next) {
      escape_next = false;
      text_value += current_char;
      continue; 
    }

    switch (current_char) {
      case UChar('\\'):
        escape_next = true;
        break;
      case UChar('('):
        if (current_token.value.length() > 0) {
          token_list.push_back(current_token);
        }
        current_token.type = Token::ArgumentListStart;
        current_token.value = current_char;
        current_token.position = position;
        break;
      default:
    }
  }

  token_list.push_back(Token(expression_text, Token::Text));
  return token_list;
}

} /* namespace mru */

