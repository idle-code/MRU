#ifndef METATAG_HPP
#define METATAG_HPP

#include "types.hpp"
#include <basic_tree.hpp>
#include <map>

namespace mru
{

class MetatagException : public std::runtime_error {
public: 
  MetatagException(const UnicodeString &a_message, const UnicodeString &a_expression, int a_start =-1, int a_length =0) throw();
  ~MetatagException(void) throw();
  std::pair<int, int> range(void) const throw();
  const char *what(void) const throw();
protected:
  UnicodeString m_message;
  UnicodeString m_expression;
  int m_range_start, m_range_length;
};

/* ------------------------------------------------------------------------- */

class Metatag {
public:
  typedef Metatag self_type;
public:
  Metatag(const UnicodeString &a_name);
  virtual ~Metatag(void);

  virtual bool Initialize(const UnicodeString &a_arguments) = 0;

  virtual UnicodeString operator()(void) = 0;
  virtual UnicodeString operator()(const UnicodeString &a_text) = 0;

  const UnicodeString& name(void) const;
protected:
  UnicodeString m_name;
};

/* ------------------------------------------------------------------------- */

class MetatagExpression {
public:
  typedef MetatagExpression self_type;
  static UnicodeString evaluate(const UnicodeString &a_expression, const std::map<UnicodeString, Metatag*> &a_bindings);
public:
  MetatagExpression(const UnicodeString &a_expression);
  ~MetatagExpression(void);

  void bind(const std::map<UnicodeString, Metatag*> &a_bindings);
  UnicodeString evaluate(void);
  UnicodeString evaluate(const std::map<UnicodeString, Metatag*> &a_bindings);

protected:
  UnicodeString m_expression_repr;
  std::map<UnicodeString, Metatag*> m_bindings;
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
  UnicodeString execute(const data_tree::basic_tree<token> &a_branch, bool a_prepare =false);

  friend data_tree::basic_tree<MetatagExpression::token>* get_inserted_node(data_tree::basic_tree<MetatagExpression::token> *a_branch);
};

} /* namespace mru */

#endif /* METATAG_HPP */

