#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "types.hpp"

namespace mru
{

class Tokenizer {
public:
  typedef std::list<UnicodeString> TokenList;
public:
  Tokenizer(void);
  virtual ~Tokenizer(void);

  const TokenList& tokenize(const UnicodeString &text);

protected:
  typedef enum {
    Continue,
    SplitLeft,
    SplitRight,
    SplitBoth,
    Ignore
  } ActionKind;

  virtual ActionKind actionOn(UChar current_character) = 0;
  virtual void addToken(const UnicodeString &token_text);
  const UnicodeString& currentToken(void) const;

  TokenList tokens;
  UnicodeString token;
};

} /* namespace mru */

#endif /* TOKENIZER_HPP */

