#include "MetatagExpression.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

#include "glue.hpp"

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
  return true;
}

/* ------------------------------------------------------------------------- */

MetatagExpression::Token::Token(void)
{ } //TODO: remove?

MetatagExpression::Token::Token(int tok_position, const UnicodeString &tok_value, TokenKind tok_type)
  : position(tok_position), value(tok_value), type(tok_type)
{ }

void
MetatagExpression::pushTextTokenIfNotEmpty(std::list<MetatagExpression::Token> &token_list, int position, UnicodeString &text_value) const
{
  if (text_value.isEmpty())
    return;

  token_list.push_back(Token(position - text_value.length(), text_value, Token::Text));
  text_value = UnicodeString();
}

std::list<MetatagExpression::Token>
MetatagExpression::tokenize(const UnicodeString &expression_text) const
{
  std::list<Token> token_list;
  UnicodeString text_value = UnicodeString();
  icu::StringCharacterIterator iter(expression_text);
  int position = 0;
  bool escape_next = false;

  for(UChar current_char = iter.first(); iter.hasNext(); ++position, current_char = iter.next()) {
    
    switch (current_char) {
      case UChar('\\'):
        if (escape_next) {
          pushTextTokenIfNotEmpty(token_list, position-1, text_value);
          token_list.push_back(Token(position-1, UChar('\\'), Token::EscapeSequence));
          escape_next = false;
          text_value += current_char;
        } else {
          escape_next = true;
        }
        break;
      case UChar('%'):
        if (escape_next) {
          pushTextTokenIfNotEmpty(token_list, position-1, text_value);
          token_list.push_back(Token(position-1, UChar('\\'), Token::EscapeSequence));
          escape_next = false;
          text_value += current_char;
        } else {
          pushTextTokenIfNotEmpty(token_list, position, text_value);
          token_list.push_back(Token(position, UChar('%'), Token::MetatagStart));
        }
        break;
      case UChar('('):
        if (escape_next) {
          pushTextTokenIfNotEmpty(token_list, position-1, text_value);
          token_list.push_back(Token(position-1, UChar('\\'), Token::EscapeSequence));
          escape_next = false;
          text_value += current_char;
        } else {
          pushTextTokenIfNotEmpty(token_list, position, text_value);
          token_list.push_back(Token(position, UChar('('), Token::ArgumentListStart));
        }
        break;
      case UChar(')'):
        if (escape_next) {
          pushTextTokenIfNotEmpty(token_list, position-1, text_value);
          token_list.push_back(Token(position-1, UChar('\\'), Token::EscapeSequence));
          escape_next = false;
          text_value += current_char;
        } else {
          pushTextTokenIfNotEmpty(token_list, position, text_value);
          token_list.push_back(Token(position, UChar(')'), Token::ArgumentListEnd));
        }
        break;
      case UChar('{'):
        if (escape_next) {
          pushTextTokenIfNotEmpty(token_list, position-1, text_value);
          token_list.push_back(Token(position-1, UChar('\\'), Token::EscapeSequence));
          escape_next = false;
          text_value += current_char;
        } else {
          pushTextTokenIfNotEmpty(token_list, position, text_value);
          token_list.push_back(Token(position, UChar('{'), Token::AreaOfEffectStart));
        }
        break;
      case UChar('}'):
        if (escape_next) {
          pushTextTokenIfNotEmpty(token_list, position-1, text_value);
          token_list.push_back(Token(position-1, UChar('\\'), Token::EscapeSequence));
          escape_next = false;
          text_value += current_char;
        } else {
          pushTextTokenIfNotEmpty(token_list, position, text_value);
          token_list.push_back(Token(position, UChar('}'), Token::AreaOfEffectEnd));
        }
        break;
      default:
        if (escape_next) {
          escape_next = false;
          text_value += UChar('\\');
        }
        text_value += current_char;
    }
  }

  pushTextTokenIfNotEmpty(token_list, position, text_value);

  return token_list;
}

} /* namespace mru */

