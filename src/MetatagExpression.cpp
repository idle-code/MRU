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
  parse(expression_text);
}

MetatagExpression::~MetatagExpression(void)
{ }

void
MetatagExpression::parse(const UnicodeString &expression_text)
{
  tokenizer.tokenize(expression_text);
}

UnicodeString
MetatagExpression::text(void) const
{
  const std::list<Tokenizer::Token> &tokens = tokenizer.getTokens();
  UnicodeString expression_text;
  for(std::list<Tokenizer::Token>::const_iterator i = tokens.begin(); i != tokens.end(); ++i) {
    expression_text += (*i).value;
  }
  return expression_text;
}

bool
MetatagExpression::isValid(void) const
{
  return true;
}

} /* namespace mru */

