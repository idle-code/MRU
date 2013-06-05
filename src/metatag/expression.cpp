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

Metatag::Metatag(const UnicodeString &a_name)
{

}

Metatag::Metatag(const self_type &a_other)
{

}

Metatag::~Metatag(void)
{

}

/* ------------------------------------------------------------------------- */

template<> inline
std::string
glue_cast<std::string, MetatagExpression::token::token_kind_type>(const MetatagExpression::token::token_kind_type &a_value)
{
  switch(a_value) {
    case MetatagExpression::token::whitespace:
      return "whitespace";
    case MetatagExpression::token::text:
      return "text";
    case MetatagExpression::token::metatag_start:
      return "metatag_start";
    case MetatagExpression::token::argument_list_start:
      return "argument_list_start";
    case MetatagExpression::token::argument_list_end:
      return "argument_list_end";
    case MetatagExpression::token::operation_area_start:
      return "operation_area_start";
    case MetatagExpression::token::operation_area_end:
      return "operation_area_end";
    default:
      return "";
  }
}


MetatagExpression::token::token(const UnicodeString &a_value, token_kind_type a_type)
  : value(a_value), type(a_type)
{ }

/* ------------------------------------------------------------------------- */

MetatagExpression::MetatagExpression(void)
{

}

MetatagExpression::MetatagExpression(const UnicodeString &a_expression)
{

}

MetatagExpression::MetatagExpression(const MetatagExpression &a_other)
{
  
}

MetatagExpression::~MetatagExpression(void)
{

}

std::list<MetatagExpression::token>
MetatagExpression::tokenize(const UnicodeString &a_expression)
{
  FO("MetatagExpression::tokenize(const UnicodeString &a_expression)");
  std::list<token> token_list;

  icu::StringCharacterIterator iter(a_expression);
  UnicodeString value;
  token::token_kind_type last_token_type = token::text;

  bool escape_next = false;
  for(UChar c = iter.first(); iter.hasNext(); c = iter.next()) {
    //VAL((char)c);

    token::token_kind_type current_token_type = token::text;
    if(escape_next) {
      escape_next = false;
      current_token_type = token::text;
    } else {
      if(c == glue_cast<UChar>('\\')) {
        escape_next = true;
        continue;
      } else if(c == glue_cast<UChar>('(')) {
        current_token_type = token::argument_list_start;
      } else if(c == glue_cast<UChar>(')')) {
        current_token_type = token::argument_list_end;
      } else if(c == glue_cast<UChar>('%')) {
        current_token_type = token::metatag_start;
      } else if(c == glue_cast<UChar>('{')) {
        current_token_type = token::operation_area_start;
      } else if(c == glue_cast<UChar>('}')) {
        current_token_type = token::operation_area_end;
      } else if(u_isWhitespace(c)) {
        current_token_type = token::whitespace;
      } else {
        current_token_type = token::text;
      }
    }
    //VAL(glue_cast<std::string>(last_token_type));
    //VAL(glue_cast<std::string>(current_token_type));
    
    if(current_token_type == last_token_type) {
      if(current_token_type == token::whitespace || current_token_type == token::text)
        value += c;
      else {
        token_list.push_back(token(c, current_token_type));
        //VAL(glue_cast<std::string>(token_list.back().type));
      }
    } else {
      if(!value.isEmpty()) {
        token_list.push_back(token(value, last_token_type));
        //VAL(glue_cast<std::string>(token_list.back().type));
        value.remove();
      }

      if(current_token_type == token::whitespace || current_token_type == token::text)
        value += c;
      else {
        token_list.push_back(token(c, current_token_type));
        //VAL(glue_cast<std::string>(token_list.back().type));
      }
    }
    //VAL(glue_cast<std::string>(value));
    
    last_token_type = current_token_type;

    //MSG("---");
  }
  
  if(!value.isEmpty()) {
    token_list.push_back(token(value, last_token_type));
  }
  
  return token_list;
}

MetatagExpression
MetatagExpression::parse(const UnicodeString &a_expression)
{
  FO("MetatagExpression::parse(const UnicodeString &a_expression)");
  std::list<token> tokens = tokenize(a_expression);

  VAL(glue_cast<std::string>(a_expression));
  std::list<token>::iterator i;
  for(i = tokens.begin(); i != tokens.end(); ++i) {
    VAL(glue_cast<std::string>((*i).type));
    VAL(glue_cast<std::string>((*i).value));
    MSG("-----");
  }
  
  
  return MetatagExpression();
}

UnicodeString
MetatagExpression::evaluate(const std::list<Metatag*> &a_bindings)
{
  FO("MetatagExpression::evaluate(const std::list<Metatag*> &a_bindings)");
  return UnicodeString();
}

} /* namespace mru */

