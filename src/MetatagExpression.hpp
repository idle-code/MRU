#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "Metatag.hpp"
#include <stdexcept>

class MetatagExpression_tests; //forward declaration for tests
class MetatagExpressionTokenizer_tests; //forward declaration for tests

namespace mru
{

class MetatagExpressionException : public std::runtime_error {
public:
  MetatagExpressionException(void) throw();
  ~MetatagExpressionException(void) throw();

};

/* ------------------------------------------------------------------------- */

class MetatagExpression {
public:

  friend class ::MetatagExpression_tests;
public:
  MetatagExpression(void);
  MetatagExpression(const UnicodeString &expression_text);
  ~MetatagExpression(void);

  UnicodeString text(void) const;

private:

};

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

