#include "expression.hpp"
#include "glue.hpp"
#include <stack>
#include <unicode/schriter.h>
#include <unicode/uchar.h>
#include <unicode/utypes.h>
#include <debug_l.h>

namespace mru
{

MetatagExpressionException::MetatagExpressionException(const UnicodeString &a_message, const UnicodeString &a_expression, int a_start, int a_length) throw()
  : std::runtime_error(glue_cast<std::string>(a_message).c_str()), m_message(a_message), 
    m_expression(a_expression), m_range(std::make_pair(a_start, a_length)) 
{ } 

MetatagExpressionException::~MetatagExpressionException(void) throw()
{ }

std::pair<int, int>
MetatagExpressionException::range(void) const throw()
{
  return m_range;
}

const char *
MetatagExpressionException::what(void) const throw()
{
  std::string message(glue_cast<std::string>(m_message));
  std::string expression(glue_cast<std::string>(m_expression));
  std::stringstream ss;
  if(m_range.first == -1)

    ss << message << " (in \'" << expression << "\')";
  else //if(m_range_length == 0)
    ss << message << " (at column " << m_range.first << " in \'" << expression << "\')";
  //else
  //  ss << message << ":" << m_range_start << ": \'" << expression.substr(m_range_start, m_range_length) << "\' in \'" << expression << "\'";

  return ss.str().c_str();
}

/* ------------------------------------------------------------------------- */

MetatagExpression::MetatagExpression(const UnicodeString &a_expression)
{

}

MetatagExpression::~MetatagExpression(void)
{

}

std::list<MetatagExpression::token>
MetatagExpression::tokenize(const UnicodeString &a_expression)
{
  FO("MetatagExpression::tokenize(const UnicodeString &a_expression)");
  std::list<MetatagExpression::token> token_list;
  
  return token_list;
}

UnicodeString
MetatagExpression::evaluate(void)
{
  FO("MetatagExpression::evaluate(void)");
  
  return UnicodeString();
}

} /* namespace mru */

