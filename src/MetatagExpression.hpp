#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "Metatag.hpp"
#include <stdexcept>

class MetatagExpression_tests; //forward declaration for tests

namespace mru
{

class MetatagExpressionException : public std::runtime_error {
public:
  MetatagExpressionException(void) throw();
  ~MetatagExpressionException(void) throw();

};

/* ------------------------------------------------------------------------- */

class MetatagExpression {
public:
  friend class Iterator;
  class Iterator;
  friend class DeclarationIterator;
  class DeclarationIterator;

  friend class MetatagExpression_tests;
public:
  MetatagExpression(void);
  MetatagExpression(const UnicodeString &expression_text);
  ~MetatagExpression(void);

  void parse(const UnicodeString &expression_text);
  UnicodeString text(void) const;
  bool isValid(void) const;

private:
  struct Token {
    typedef enum {
      Text,
      MetatagStart,
      ArgumentListStart,
      ArgumentListEnd,
      AreaOfEffectStart,
      AreaOfEffectEnd,
      EscapeSequence
    } TokenKind;

    int position;
    UnicodeString value;
    TokenKind type;

    Token(void);
    Token(int position, const UnicodeString &value, TokenKind type);
  };

  struct Entry {
    typedef boost::shared_ptr<Entry> Pointer;

    UnicodeString name;
    UnicodeString arguments;
    Metatag::Pointer metatag;
    int position;
    std::list<Pointer> childrens;
  };

private:
  void pushTextTokenIfNotEmpty(std::list<MetatagExpression::Token> &token_list, int position, UnicodeString &text_value) const;
  std::list<Token> tokenize(const UnicodeString &expression_text) const;

private:
  std::list<Token> tokens;
  Entry::Pointer root_entry;
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

