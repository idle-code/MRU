#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "UnicodeStringIterator.hpp"
#include "Iterator.hpp"
#include "types.hpp"

namespace mru
{

class TokenizerBase : public ConstIterator<UnicodeString> {
public:
  TokenizerBase(const ConstUnicodeStringIterator &text_iterator);

  void first(void);
  bool next(void);
  bool atEnd(void) const;
  UnicodeString getCurrent(void) const;

protected:
  typedef enum {
    Continue,
    SplitLeft,
    SplitRight,
    SplitBoth,
    Ignore
  } ActionKind;

  virtual ActionKind actionOn(UChar current_character) = 0;
  virtual UnicodeString yieldWord(const UnicodeString &word);
  
private:
  UnicodeString tokenizeNext(void);
  UChar readNext(void);
  bool splitOn(UChar character);
  bool finishUpWord(void);

  ConstUnicodeStringIterator text_iterator; 
  UnicodeString current_word;
  UnicodeString word;
  UChar next_character;
  bool next_character_is_word;
};

} /* namespace mru */

#endif /* TOKENIZER_HPP */

