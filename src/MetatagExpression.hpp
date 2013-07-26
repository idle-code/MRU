#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "Metatag.hpp"
#include <stdexcept>

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
      AreaOfEffectEnd
    } TokenKind;

    int position;
    UnicodeString value;
    TokenKind type;

    Token(void);
    Token(const UnicodeString &value, TokenKind type);
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
  std::list<Token> tokenize(const UnicodeString &expression_text) const;

private:
  std::list<Token> tokens;
  Entry::Pointer root_entry;
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

