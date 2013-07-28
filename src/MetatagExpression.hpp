#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "Metatag.hpp"
#include <stdexcept>

class MetatagExpression_tests; //forward declaration for tests
class MetatagExpressionTokenizer_tests; //forward declaration for tests

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

  friend class ::MetatagExpression_tests;
  friend class ::MetatagExpressionTokenizer_tests;
public:
  MetatagExpression(void);
  MetatagExpression(const UnicodeString &expression_text);
  ~MetatagExpression(void);

  void parse(const UnicodeString &expression_text);
  UnicodeString text(void) const;
  bool isValid(void) const;

private:
  class Tokenizer {
  public:
    class Token {
    public:
      typedef UChar TokenKind;
      static const TokenKind Text = UChar('\0');
      static const TokenKind MetatagStart = UChar('%');
      static const TokenKind ArgumentListStart = UChar('(');
      static const TokenKind ArgumentListEnd = UChar(')');
      static const TokenKind AreaOfEffectStart = UChar('{');
      static const TokenKind AreaOfEffectEnd = UChar('}');
      static const TokenKind EscapeSequence = UChar('\\'); 

    public:
      static TokenKind specifyCharacterType(UChar character);
      Token(int position, const UnicodeString &value, TokenKind type);

    public:
      int position;
      UnicodeString value;
      TokenKind type;
    };

    friend class ::MetatagExpressionTokenizer_tests;

  public:
    Tokenizer(void);
    Tokenizer(const UnicodeString &expression_text);
    const std::list<Token>& tokenize(const UnicodeString &expression_text);
    const std::list<Token>& getTokens(void) const;

  private:
    void pushToken(UnicodeString &text_value, int offset = 0);
    void pushToken(Token::TokenKind type, int offset = 0);

    std::list<Token> token_list;
    int position_in_expression;
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
  Tokenizer tokenizer;
  Entry::Pointer root_entry;
};

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

