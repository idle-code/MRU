#include "MetatagExpressionLexer.hpp"

namespace mru
{

UnicodeString
MetatagExpressionLexer::joinTokens(const TokenList &token_list)
{
  UnicodeString joined_string;
  TokenList::const_iterator ti_end = token_list.end();
  for(TokenList::const_iterator ti = token_list.begin(); ti != ti_end; ++ti)
    joined_string += (*ti).value;
  return joined_string;
}

UnicodeString
MetatagExpressionLexer::joinTokens(void) const
{
  return joinTokens(tokens);
}

MetatagExpressionLexer::MetatagExpressionLexer(void)
  : in_text_position(0)
{ }

MetatagExpressionLexer::~MetatagExpressionLexer(void)
{ }

const MetatagExpressionLexer::TokenList &
MetatagExpressionLexer::analyze(const UnicodeString &text)
{
  tokens.clear();
  in_text_position = 0;

  const WordList &words = tokenizer.tokenize(text);

  WordList::const_iterator wi_end = words.end();
  for(WordList::const_iterator wi = words.begin(); wi != wi_end; ++wi) {
    addToken(*wi);
  }

  return tokens;
}

void
MetatagExpressionLexer::addToken(const UnicodeString &value)
{
  Token token;
  token.position = in_text_position;
  token.value = value;
  token.type = determineTokenType(value);

  tokens.push_back(token);

  in_text_position += value.length(); 
}

MetatagExpressionLexer::Token::TokenKind
MetatagExpressionLexer::determineTokenType(const UnicodeString &word) const
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

} /* namespace mru */

