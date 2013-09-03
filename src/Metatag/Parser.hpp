#ifndef METATAG_EXPRESSION_PARSER_HPP
#define METATAG_EXPRESSION_PARSER_HPP

#include "MruException.hpp"
#include "Metatag/Lexer.hpp"
#include "StateMachine.hpp"
#include <stdexcept>
#include <map>

class MetatagExpressionParser_tests; //forward declaration for tests

namespace mru {
namespace Metatag {

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

  class Exception;
  friend class Exception;
  friend class ::MetatagExpressionParser_tests;
public:
  Parser(void);
  ~Parser(void);

  TagEntry::Pointer parse(const UnicodeString &expression_text);

  TagEntry::Pointer getExpressionRoot(void);

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

class Parser::Exception : public MruException {
public: 
  typedef Parser::TagEntry TagEntry;
public:
  Exception(const TagEntry::Pointer entry, const UnicodeString &message) throw()
    : MruException(message), entry(entry)
  { }

  Exception(const UnicodeString &message) throw()
    : MruException(message)
  { }

  virtual ~Exception(void) throw()
  { }

  const TagEntry::Pointer
  getEntry(void) const throw()
  {
    return entry;
  }

private:
  TagEntry::Pointer entry;
};

} /* namespace Metatag */
} /* namespace mru */

#endif /* METATAG_EXPRESSION_PARSER_HPP */

