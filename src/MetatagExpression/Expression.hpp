#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "Metatag.hpp"
#include <stdexcept>

class MetatagExpression_tests; //forward declaration for tests

namespace mru {
namespace MetatagExpression {

/* ------------------------------------------------------------------------- */

class Expression {
public:
  friend class ::MetatagExpression_tests;
public:
  Expression(void);
  Expression(const UnicodeString &expression_text);
  ~Expression(void);

  UnicodeString text(void) const;

private:

};

/* ------------------------------------------------------------------------- */

} /* namespace MetatagExpression */
} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

