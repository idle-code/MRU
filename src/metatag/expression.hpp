#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "types.hpp"
#include <list>

namespace mru
{

class MetatagExpressionException : public std::runtime_error {
public: 
  MetatagExpressionException(const UnicodeString &a_message, const UnicodeString &a_expression, int a_start, int a_length =0) throw();
  MetatagExpressionException(const UnicodeString &a_message, const UnicodeString &a_expression) throw();
  ~MetatagExpressionException(void) throw();
  std::pair<int, int> range(void) const throw();
  const char* what(void) const throw();
protected:
  UnicodeString m_message;
  UnicodeString m_expression;
  std::pair<int, int> m_range; // (start, length) pair
};

/* ------------------------------------------------------------------------- */


class Metatag {
public:
  typedef Metatag self_type;
public:
  Metatag(const UnicodeString &a_name);
  Metatag(const self_type &a_other);
  virtual ~Metatag(void);

  UnicodeString evaluate(void);
protected:
  /* data */
};

class MetatagExpression {
public:
  typedef MetatagExpression self_type;
public:
  MetatagExpression(const UnicodeString &a_expression);
  ~MetatagExpression(void);
  
  struct token {
    enum token_kind_type {
      whitespace,
      text, // all other characters
      argument_list_start, // '(' character
      argument_list_end, // ')' character
      operation_area_start, // '{' character
      operation_area_end // '}' character
    } type;
    UnicodeString value;
    token(const UnicodeString &a_value, token::token_kind_type a_type);
  };
  static std::list<token> tokenize(const UnicodeString &a_expression);

  UnicodeString evaluate(void);

protected:
  MetatagExpression(const self_type &a_other);
};

} /* namespace mru */

#endif /* EXPRESSION_HPP */

