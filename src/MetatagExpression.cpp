#include "MetatagExpression.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

#include "glue.hpp"

namespace mru
{

MetatagExpression::MetatagExpression(void)
{ }

MetatagExpression::MetatagExpression(const UnicodeString &expression_text)
{

}

MetatagExpression::~MetatagExpression(void)
{ }


UnicodeString
MetatagExpression::text(void) const
{
  return UnicodeString();
}

} /* namespace mru */

