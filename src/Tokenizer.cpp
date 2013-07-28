#include "Tokenizer.hpp"
#include <unicode/uchar.h>
#include <unicode/schriter.h>

namespace mru
{

Tokenizer::Tokenizer(void)
{ }

Tokenizer::~Tokenizer(void)
{ }

const Tokenizer::TokenList &
Tokenizer::tokenize(const UnicodeString &text)
{
  tokens.clear();

  icu::StringCharacterIterator iter(text);
  for (UChar current_char = iter.first(); iter.hasNext(); current_char = iter.next()) {
    switch(actionOn(current_char)) {
      case Continue:
        token += current_char;
        break;
      case SplitLeft:
        addToken(token);
        token = current_char;
        break;
      case SplitRight:
        token += current_char;
        addToken(token);
        token = UnicodeString();
        break;
      case SplitBoth:
        addToken(token);
        addToken(current_char);
        token = UnicodeString();
        break;
      case Ignore:
        break;
    }
  }

  addToken(token);

  return tokens;
}

void
Tokenizer::addToken(const UnicodeString &token_text)
{
  if (!token_text.isEmpty())
    tokens.push_back(token_text);
}

const UnicodeString &
Tokenizer::currentToken(void) const
{
  return token;
}

} /* namespace mru */

