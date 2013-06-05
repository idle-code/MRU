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

  virtual void initialize(const UnicodeString &a_arguments) = 0;
  virtual UnicodeString execute(void) = 0;
  virtual UnicodeString execute(const UnicodeString &a_area_of_effect) = 0;
protected:
  /* data */
};

class MetatagExpression {
public:
  typedef MetatagExpression self_type;
  struct token {
    enum token_kind_type {
      whitespace,
      text, // all other characters
      metatag_start,        // '%' character
      argument_list_start,  // '(' character
      argument_list_end,    // ')' character
      operation_area_start, // '{' character
      operation_area_end    // '}' character
    } type;
    UnicodeString value;
    token(const UnicodeString &a_value, token_kind_type a_type);
  };
  static std::list<token> tokenize(const UnicodeString &a_expression);
  static MetatagExpression parse(const UnicodeString &a_expression);

public:
  MetatagExpression(void);
  MetatagExpression(const UnicodeString &a_function_name);
  MetatagExpression(const self_type &a_other);
  ~MetatagExpression(void);
  
  UnicodeString evaluate(const std::list<Metatag*> &a_bindings);

protected:
};

} /* namespace mru */

#endif /* EXPRESSION_HPP */

