#ifndef METATAG_EXPRESSION_TOKENIZER_HPP
#define METATAG_EXPRESSION_TOKENIZER_HPP

#include "Tokenizer.hpp"

namespace mru
{

class MetatagExpressionTokenizer : public Tokenizer {
public:
  MetatagExpressionTokenizer(void);

protected:
  ActionKind actionOn(UChar current_character);
  bool isControlCharacter(UChar character) const;

  bool escape_next;
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_TOKENIZER_HPP */

