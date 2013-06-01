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

class MetatagExpression {
public:
  typedef MetatagExpression self_type;
  static UnicodeString evaluate(const UnicodeString &a_expression, const std::list<MetatagExpression*> &a_bindings);
public:
  MetatagExpression(const UnicodeString &a_expression);
  ~MetatagExpression(void);

  void bind(const std::list<MetatagExpression*> &a_bindings);
  UnicodeString evaluate(void);
  UnicodeString evaluate(const std::list<MetatagExpression*> &a_bindings);

protected:
  UnicodeString m_expression_repr;
  std::list<MetatagExpression*> m_bindings;
  struct token {
    int position;
    enum type { text, name, args } type;
    UnicodeString value;
    UnicodeString arguments;
    token(void);
    token(int a_pos, const UnicodeString &a_value, enum type a_type);
  };
  data_tree::basic_tree<token> m_parse_tree;
  void build_tree(const UnicodeString &a_expression);
  MetatagExpression* find_binding(const UnicodeString &a_tagname) const;
  UnicodeString execute(const data_tree::basic_tree<token> &a_branch, bool a_prepare =false);

  friend data_tree::basic_tree<MetatagExpression::token>* get_inserted_node(data_tree::basic_tree<MetatagExpression::token> *a_branch);
};

} /* namespace mru */

#endif /* EXPRESSION_HPP */

