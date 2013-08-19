#include "Expression.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

#include "glue.hpp"

namespace mru {
namespace MetatagExpression {

Expression::Expression(void)
{ }

Expression::Expression(const UnicodeString &expression_text)
{

}

Expression::~Expression(void)
{ }


UnicodeString
Expression::text(void) const
{
  return UnicodeString();
}

} /* namespace MetatagExpression */
} /* namespace mru */

