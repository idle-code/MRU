#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include "types.hpp"

namespace mru
{

class Tokenizer {
public:
  typedef std::list<UnicodeString> WordList;
  
  static UnicodeString joinWords(const WordList &word_list);
public:
  Tokenizer(void);
  virtual ~Tokenizer(void);

  const WordList& tokenize(const UnicodeString &text);
  const WordList& getWords(void) const;
  UnicodeString joinWords(void) const;

protected:
  typedef enum {
    Continue,
    SplitLeft,
    SplitRight,
    SplitBoth,
    Ignore
  } ActionKind;

  virtual ActionKind actionOn(UChar current_character) = 0;
  virtual void addWord(const UnicodeString &word_text);
  const UnicodeString& currentWord(void) const;

  WordList words;
  UnicodeString word;
};

} /* namespace mru */

#endif /* TOKENIZER_HPP */

