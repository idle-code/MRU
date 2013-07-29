#ifndef METATAG_EXPRESSION_PARSER_HPP
#define METATAG_EXPRESSION_PARSER_HPP

#include "MetatagExpressionLexer.hpp"
#include "MetatagExpression.hpp"

namespace mru
{

class MetatagExpressionParser {
public:
  struct Entry {
    typedef boost::shared_ptr<Entry> Pointer;
  };
public:
  MetatagExpressionParser(void);
  ~MetatagExpressionParser(void);

  Entry::Pointer parse(const UnicodeString &expression_text);
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_PARSER_HPP */

