#include "MetatagExpression.hpp"

namespace mru
{

MetatagExpression::MetatagExpression(void)
{ }

MetatagExpression::MetatagExpression(const UnicodeString &expression_text)
{
  parse(expression_text);
}

MetatagExpression::~MetatagExpression(void)
{ }

void
MetatagExpression::parse(const UnicodeString &expression_text)
{

}

UnicodeString
MetatagExpression::text(void) const
{
  return UnicodeString(); 
}

std::list<MetatagEntry>
MetatagExpression::tokenize(const UnicodeString &expression_text) const
{

}

} /* namespace mru */

