#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "Metatag.hpp"
#include <stdexcept>

namespace mru
{

class MetatagExpressionException : public std::runtime_error {
public:
  MetatagExpressionException(void) throw();
  ~MetatagExpressionException(void) throw();

};

/* ------------------------------------------------------------------------- */

struct MetatagEntry {
  UnicodeString name;
  UnicodeString arguments;
  //Pointer to Metatag object
};

class MetatagExpression {
public:
  MetatagExpression(void);
  MetatagExpression(const UnicodeString &expression_text);
  ~MetatagExpression(void);

  void parse(const UnicodeString &expression_text);
  UnicodeString text(void) const;
private:
  std::list<MetatagEntry> tokenize(const UnicodeString &expression_text) const;
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

