#include "glue.hpp"
#include "Metatag/Parser.hpp"
#include "Metatag/Lexer.hpp"
#include <boost/make_shared.hpp>

namespace mru {
namespace Metatag {

Parser::TagEntry::TagEntry(void)
  : position(-1), name(""), arguments("")
{ }

Parser::TagEntry::TagEntry(int position, const UnicodeString &name, const UnicodeString &arguments)
  : position(position), name(name), arguments(arguments)
{ }

void
Parser::TagEntry::addAreaOfEffectMember(Pointer sub_tag)
{
  areaOfEffectMembers.push_back(sub_tag);
}

bool
Parser::TagEntry::haveAreaOfEffectMembers(void) const
{
  return areaOfEffectMembers.size() != 0;
}

/* ------------------------------------------------------------------------- */

Parser::Parser(void)
{
  setUpStateMachine();
}

void
Parser::setUpStateMachine(void)
{
  StateMachineType::State *start = state_machine.createState();
  StateMachineType::State *constant_text = state_machine.createState();
  StateMachineType::State *tag_start = state_machine.createState();
  StateMachineType::State *name = state_machine.createState();
  StateMachineType::State *arguments_start = state_machine.createState();
  StateMachineType::State *arguments_end = state_machine.createState();
  StateMachineType::State *arguments_text = state_machine.createState();
  StateMachineType::State *aoe_start = state_machine.createState();
  StateMachineType::State *aoe_end = state_machine.createState();

  state_machine.setStartState(start);
  state_machine.addEndState(start); //empty expression is still good
  state_machine.addEndState(constant_text);
  state_machine.addEndState(arguments_end);
  state_machine.addEndState(aoe_end);

  // connect methods
  constant_text->onEntry.connect(sigc::mem_fun(this, &Parser::createNewEntry));
  constant_text->onEntry.connect(sigc::mem_fun(this, &Parser::addToEntryArguments));
  constant_text->onRepeat.connect(sigc::mem_fun(this, &Parser::addToEntryArguments));
  constant_text->onLeave.connect(sigc::mem_fun(this, &Parser::addEntryToParent));

  name->onEntry.connect(sigc::mem_fun(this, &Parser::createNewEntry));
  name->onEntry.connect(sigc::mem_fun(this, &Parser::addToEntryName));
  name->onRepeat.connect(sigc::mem_fun(this, &Parser::addToEntryName));
  //name->onLeave.connect(sigc::mem_fun(this, &Parser::onNameLeave));
  arguments_text->onEntry.connect(sigc::mem_fun(this, &Parser::addToEntryArguments));
  arguments_text->onRepeat.connect(sigc::mem_fun(this, &Parser::addToEntryArguments));

  arguments_end->onEntry.connect(sigc::mem_fun(this, &Parser::addEntryToParent));

  aoe_start->onEntry.connect(sigc::mem_fun(this, &Parser::subExpressionStart));

  aoe_end->onEntry.connect(sigc::mem_fun(this, &Parser::subExpressionEnd));
  aoe_end->onRepeat.connect(sigc::mem_fun(this, &Parser::subExpressionEnd));

  // define transition rules
  start->addTransition(Token(Token::Text), constant_text);
  start->addTransition(Token(Token::MetatagStart), tag_start);

  constant_text->addTransition(Token(Token::Text), constant_text);
  constant_text->addTransition(Token(Token::MetatagStart), tag_start);
  constant_text->addTransition(Token(Token::AreaOfEffectEnd), aoe_end);

  tag_start->addTransition(Token(Token::Text), name);

  name->addTransition(Token(Token::Text), name);
  name->addTransition(Token(Token::ArgumentListStart), arguments_start);

  arguments_start->addTransition(Token(Token::ArgumentListEnd), arguments_end);
  arguments_start->addTransition(Token(Token::Text), arguments_text);

  arguments_text->addTransition(Token(Token::Text), arguments_text);
  arguments_text->addTransition(Token(Token::ArgumentListEnd), arguments_end);

  arguments_end->addTransition(Token(Token::Text), constant_text);
  arguments_end->addTransition(Token(Token::MetatagStart), tag_start);
  arguments_end->addTransition(Token(Token::AreaOfEffectStart), aoe_start);
  arguments_end->addTransition(Token(Token::AreaOfEffectEnd), aoe_end);

  aoe_start->addTransition(Token(Token::Text), constant_text);
  aoe_start->addTransition(Token(Token::MetatagStart), tag_start);
  aoe_start->addTransition(Token(Token::AreaOfEffectEnd), aoe_end);

  aoe_end->addTransition(Token(Token::Text), constant_text);
  aoe_end->addTransition(Token(Token::MetatagStart), tag_start);
  aoe_end->addTransition(Token(Token::AreaOfEffectEnd), aoe_end);
}

Parser::~Parser(void)
{

}

Parser::TagEntry::Pointer
Parser::parse(const UnicodeString &expression_text)
{
  //FO("Parser::parse(const UnicodeString &expression_text)");
  //VAL(expression_text);
  Tokenizer::Pointer tokenizer = boost::make_shared<Tokenizer>(expression_text);
  lexer = boost::make_shared<Lexer>(tokenizer);

  entry_stack.push(boost::make_shared<TagEntry>()); //TODO: remove

  state_machine.setIterator(lexer);
  try {
    state_machine.start();
  } catch(StateMachineException &e) {
    throw Parser::Exception(e.what());
  }

  //VAL(entry_stack.size());
  if (entry_stack.size() != 1)
    throw Parser::Exception("Unclosed area of effect");
  return getExpressionRoot(); //TODO: remove and replace return type by void
}

Parser::TagEntry::Pointer
Parser::getExpressionRoot(void)
{
  return entry_stack.top();
}

void
Parser::addEntryToParent(const Token &current_token)
{
  //FO("Parser::addEntryToParent(const Token &current_token)");
  assert(!entry_stack.empty());
  assert(tag_entry);
  entry_stack.top()->addAreaOfEffectMember(tag_entry);
  tag_entry.reset();
}

void
Parser::createNewEntry(const Token &current_token)
{
  //FO("Parser::createNewEntry(const Token &current_token)");
  assert(!tag_entry);
  tag_entry = boost::make_shared<TagEntry>();
}

void
Parser::addToEntryName(const Token &current_token)
{
  //FO("Parser::addToEntryName(const Token &current_token)");
  //VAL(current_token.value);
  assert(tag_entry);
  tag_entry->name += current_token.value;
}

void
Parser::addToEntryArguments(const Token &current_token)
{
  //FO("Parser::addToEntryArguments(const Token &current_token)");
  //VAL(current_token.value);
  assert(tag_entry);
  tag_entry->arguments += current_token.value;
}

void
Parser::subExpressionStart(const Token &current_token)
{
  //FO("Parser::subExpressionStart(const Token &current_token)");
  if (entry_stack.empty())
    entry_stack.push(boost::make_shared<TagEntry>());
  assert(entry_stack.top()->areaOfEffectMembers.size() > 0);
  entry_stack.push(entry_stack.top()->areaOfEffectMembers.back());
}

void
Parser::subExpressionEnd(const Token &current_token)
{
  //FO("Parser::subExpressionEnd(const Token &current_token)");
  assert(entry_stack.size() > 0);
  entry_stack.pop();
}

} /* namespace Metatag */
} /* namespace mru */

