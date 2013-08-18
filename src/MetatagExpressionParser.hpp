#ifndef METATAG_EXPRESSION_PARSER_HPP
#define METATAG_EXPRESSION_PARSER_HPP

#include "MetatagExpressionLexer.hpp"
#include "StateMachine.hpp"
#include <stdexcept>
#include <map>

class MetatagExpressionParser_tests; //forward declaration for tests

namespace mru {
namespace MetatagExpression {

class ParserException;

class Parser {
public:
  struct TagEntry {
    typedef boost::shared_ptr<TagEntry> Pointer;
    typedef std::list<Pointer> MemberList;

    int position;
    UnicodeString name;
    UnicodeString arguments;
    MemberList areaOfEffectMembers;

    TagEntry(void);
    TagEntry(int position, const UnicodeString &name, const UnicodeString &arguments);
    void addAreaOfEffectMember(Pointer sub_tag);
    bool haveAreaOfEffectMembers(void) const;
  };

  friend class ParserException;
  friend class ::MetatagExpressionParser_tests;
public:
  Parser(void);
  ~Parser(void);

  TagEntry::Pointer parse(const UnicodeString &expression_text);

private: 
  Parser(const Parser &other); //disabled
  void setUpStateMachine(void);
  typedef StateMachine<Token> StateMachineType;
  StateMachineType state_machine;

  TagEntry::Pointer tag_entry;
  std::stack<TagEntry::Pointer> entry_stack;
  Lexer::Pointer lexer;

  void addEntryToParent(const Token &current_token);
  void createNewEntry(const Token &current_token);
  void addToEntryName(const Token &current_token);
  void addToEntryArguments(const Token &current_token);
  void subExpressionStart(const Token &current_token); 
  void subExpressionEnd(const Token &current_token); 
};

/* ------------------------------------------------------------------------- */

class ParserException : public std::runtime_error {
public: 
  typedef Parser::TagEntry TagEntry;
public:
  ParserException(const TagEntry::Pointer entry, const UnicodeString &message) throw();
  ParserException(const UnicodeString &message) throw();
  virtual ~ParserException(void) throw();

  const TagEntry::Pointer getEntry(void) const throw();
  const UnicodeString& getMessage(void) const throw();
private:
  TagEntry::Pointer entry;
  UnicodeString message;
};

} /* namespace MetatagExpression */
} /* namespace mru */

#endif /* METATAG_EXPRESSION_PARSER_HPP */

