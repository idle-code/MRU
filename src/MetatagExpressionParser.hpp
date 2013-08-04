#ifndef METATAG_EXPRESSION_PARSER_HPP
#define METATAG_EXPRESSION_PARSER_HPP

#include "MetatagExpressionLexer.hpp"
#include "MetatagExpression.hpp"
#include <stdexcept>
#include <map>

class MetatagExpressionParser_tests; //forward declaration for tests

namespace mru
{

class MetatagExpressionParserException;

class MetatagExpressionParser {
public:
  struct Entry {
    typedef boost::shared_ptr<Entry> Pointer;
    typedef std::list<Pointer> MemberList;

    int position;
    UnicodeString name;
    UnicodeString arguments;
    MemberList areaOfEffectMembers;

    Entry(int position);
    Entry(int position, const UnicodeString &name, const UnicodeString &arguments);
    void addAreaOfEffectMember(int position, const UnicodeString &name, const UnicodeString &arguments);
    bool isAreaOfEffectMembersPresent(void) const;
  };

  friend class MetatagExpressionParserException;
  friend class ::MetatagExpressionParser_tests;
public:
  MetatagExpressionParser(void);
  ~MetatagExpressionParser(void);

  Entry::Pointer parse(const UnicodeString &expression_text);

private: 
  MetatagExpressionParser(const MetatagExpressionParser &other); //disabled
  typedef MetatagExpressionLexer::TokenList TokenList;
  typedef MetatagExpressionLexer::Token Token;

  struct ParsePoint {
    typedef boost::shared_ptr<ParsePoint> Pointer;

    typedef void (MetatagExpressionParser::* ActionCallback)(const Pointer);
    ActionCallback onEntry;
    ActionCallback onExit;

    Token::TokenKind type;
    std::list<ParsePoint::Pointer> exitPoints;
    ParsePoint::Pointer getNextExitPoint(Token::TokenKind type);
  };
  friend struct ParsePoint;


  TokenList::const_iterator tok_iter;
  TokenList::const_iterator tok_iter_end;
  void parse(Entry::Pointer parent);
  std::map<std::string, ParsePoint::Pointer> parser_states;
  void clearParserStatesMap(void);

  void OnMetatagStartEntry(const ParsePoint::Pointer);
  void OnMetatagStartExit(const ParsePoint::Pointer);

  MetatagExpressionLexer lexer;
  Entry::Pointer root;
};

class MetatagExpressionParserException : public std::runtime_error {
public: 
  typedef MetatagExpressionParser::Entry Entry;
public:
  MetatagExpressionParserException(const Entry::Pointer entry, const UnicodeString &message) throw();
  MetatagExpressionParserException(const UnicodeString &message) throw();
  virtual ~MetatagExpressionParserException(void) throw();

  const Entry::Pointer getEntry(void) const throw();
  const UnicodeString& getMessage(void) const throw();
private:
  Entry::Pointer entry;
  UnicodeString message;
};

} /* namespace mru */

#endif /* METATAG_EXPRESSION_PARSER_HPP */

