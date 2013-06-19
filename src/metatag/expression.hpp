#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "types.hpp"
#include <map>

namespace mru
{

class MetatagExpressionException : public std::runtime_error {
public: 
  MetatagExpressionException(const UnicodeString &a_message, int a_start, int a_length =0) throw();
  ~MetatagExpressionException(void) throw();
  std::pair<int, int> range(void) const throw();
  const char* what(void) const throw();
  const UnicodeString &expression(void) const;
  void expression(const UnicodeString &a_expression);
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
  virtual ~Metatag(void);

  virtual void initialize(const UnicodeString &a_arguments) = 0;
  virtual UnicodeString execute(const UnicodeString &a_area_of_effect) = 0;
protected:
  Metatag(const self_type &a_other); // = delete;
  UnicodeString m_name;
};

struct MetatagEntry {
  UnicodeString name;
  UnicodeString arguments;
  Metatag *metatag;
  std::list<MetatagEntry*> childrens;

  MetatagEntry(void);
  MetatagEntry(const UnicodeString &a_name);
  ~MetatagEntry(void);
  void add_child(MetatagEntry *&a_child)
  {
    assert(a_child != NULL);
    childrens.push_back(a_child);
    a_child = NULL;
  }
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
    int index;
    UnicodeString value;
    token(int a_index, const UnicodeString &a_value, token_kind_type a_type);
  };
  static std::list<token> tokenize(const UnicodeString &a_expression);
  static MetatagExpression parse(const UnicodeString &a_expression);
  void parse(MetatagEntry *a_parent, std::list<token>::iterator &a_begin, const std::list<token>::iterator &a_end);

public:
  MetatagExpression(void);
  MetatagExpression(const UnicodeString &a_function_name);
  MetatagExpression(const self_type &a_other);
  ~MetatagExpression(void);
  
  std::map<UnicodeString, abstract_factory<Metatag>*> bindings(void) const; 
  void bindings(const std::map<UnicodeString, abstract_factory<Metatag>*> &a_bindings);
  
  UnicodeString evaluate(void);
  UnicodeString evaluate(const std::map<UnicodeString, abstract_factory<Metatag>*> &a_bindings);

protected:
  std::map<UnicodeString, abstract_factory<Metatag>*> m_bindings;
  void initialize(MetatagEntry *a_entry);
  UnicodeString evaluate(MetatagEntry *a_entry);
  MetatagEntry *m_root;
};

} /* namespace mru */

#endif /* EXPRESSION_HPP */

