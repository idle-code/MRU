#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include <stdexcept>

namespace mru
{

class MetatagExpressionException : public std::runtime_error {
public:
  typedef MetatagExpressionException self_type;
public:
  MetatagExpressionException(void) throw();
  ~MetatagExpressionException(void) throw();

protected:
  /* data */
};

class MetatagExpression {
public:
  typedef MetatagExpression self_type;
public:
  MetatagExpression(void);
  ~MetatagExpression(void);

protected:
  /* data */
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

