#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "MetatagExpression/Metatag.hpp"
#include "MetatagExpression/Parser.hpp"
#include <stdexcept>
#include <set>

class MetatagExpression_tests; //forward declaration for tests

namespace mru {
namespace MetatagExpression {

/* ------------------------------------------------------------------------- */

class Expression {
public:
  typedef boost::shared_ptr<Expression> Pointer;
  friend class ::MetatagExpression_tests;

  static Expression::Pointer parse(const UnicodeString &expression_text);
public:
  ~Expression(void);

  UnicodeString text(void) const;

  std::set<UnicodeString> getUsedMetatagNames(void) const;

private:
  struct MetatagEntry : public Parser::TagEntry {
    Metatag::Pointer metatag;
  };

  Expression(void);
  Expression(Parser::TagEntry::Pointer expression_root);
  
  Parser::TagEntry::Pointer expression_root;
};

/* ------------------------------------------------------------------------- */

} /* namespace MetatagExpression */
} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

