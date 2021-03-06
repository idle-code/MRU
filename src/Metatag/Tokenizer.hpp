#ifndef METATAG_EXPRESSION_TOKENIZER_HPP
#define METATAG_EXPRESSION_TOKENIZER_HPP

#include "TokenizerBase.hpp"

namespace mru {
namespace Metatag {

class Tokenizer : public TokenizerBase {
public:
  Tokenizer(const ConstUnicodeStringIterator &text_iterator);

protected:
  ActionKind actionOn(UChar current_character);
  bool isControlCharacter(UChar character) const;

  bool escape_next;
};

} /* namespace Metatag */
} /* namespace mru */

#endif /* METATAG_EXPRESSION_TOKENIZER_HPP */

