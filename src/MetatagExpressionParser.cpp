#include "tests/UnicodeStringStreamOperator.hpp" //temporary
#include "MetatagExpressionParser.hpp"
#include "MetatagExpressionLexer.hpp"
#include <boost/make_shared.hpp>

namespace mru {
namespace MetatagExpression {

Parser::TagEntry::TagEntry(int position, const UnicodeString &name, const UnicodeString &arguments)
  : position(position), name(name), arguments(arguments)
{ }

void
Parser::TagEntry::addAreaOfEffectMember(int position, const UnicodeString &name, const UnicodeString &arguments)
{
  areaOfEffectMembers.push_back(Pointer(new TagEntry(position, name, arguments)));
}

bool
Parser::TagEntry::haveAreaOfEffectMembers(void) const
{
  return areaOfEffectMembers.size() != 0;
}

/* ------------------------------------------------------------------------- */


Parser::Parser(void)
{
  start_point = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer metatag_start = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer text = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer name = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer args_start = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer args = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer args_end = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer aoe_start = boost::make_shared<ParsePoint>();
  ParsePoint::Pointer aoe_end = boost::make_shared<ParsePoint>();
  
  /* ------------------------------------------------------------------------- */
  
  start_point->exitPoints[Token::Text] = text.get();
  start_point->exitPoints[Token::MetatagStart] = metatag_start.get();

  metatag_start->exitPoints[Token::Text] = name.get();

  //name->exitPoints[Token::Text] = name.get();
  name->exitPoints[Token::ArgumentListStart] = args_start.get();
  args_start->exitPoints[Token::ArgumentListEnd] = args_end.get();
  
  /* ------------------------------------------------------------------------- */

  start_point->onEntry = &Parser::OnMetatagStartEntry;
  start_point->onExit = &Parser::OnMetatagStartExit;
  
  name->onExit = &Parser::OnNameEnd;
  args_end->onExit = &Parser::OnArgumentListEnd;
  /* ------------------------------------------------------------------------- */
  
  //possible_parse_points.push_back(start_point);
  possible_parse_points.push_back(metatag_start);
  possible_parse_points.push_back(name);
  possible_parse_points.push_back(args_start);
  possible_parse_points.push_back(args);
  possible_parse_points.push_back(args_end);
  possible_parse_points.push_back(aoe_start);
  possible_parse_points.push_back(aoe_end);
}

Parser::~Parser(void)
{

}

Parser::TagEntry::Pointer
Parser::parse(const UnicodeString &expression_text)
{
  FO("Parser::parse(const UnicodeString &expression_text)");
  Tokenizer::Pointer tokenizer = boost::make_shared<Tokenizer>(expression_text);
  lexer = boost::make_shared<Lexer>(tokenizer);
  TagEntry::Pointer root = boost::make_shared<TagEntry>(-1, "", "");
  current_state = start_point.get();

  parse(root);

  return root;
}

Parser::ParsePoint *
Parser::ParsePoint::getNextExitPoint(Token::TokenKind type)
{
  if (exitPoints.count(type) > 0)
    return exitPoints[type];
  return NULL;
}

void
Parser::parse(TagEntry::Pointer parent)
{
  FO("Parser::parse(TagEntry::Pointer parent, Lexer::Pointer lexer)");
  assert(parent);
  ParsePoint *next_state = NULL;
  while (!lexer->atEnd()) {
    VAL(lexer->getCurrent().value);
    next_state = current_state->getNextExitPoint(lexer->getCurrent().type);
    if (next_state == NULL)
      break; //error?
    if (current_state->onExit)
      (this->*current_state->onExit)();
    if (next_state->onEntry)
      (this->*next_state->onEntry)();
    current_state = next_state;
    lexer->next();
  }

  if (!lexer->atEnd()) {
    ERR("Unexpected end of expression");
    return;
  }

  if (current_state->onExit)
    (this->*current_state->onExit)();

}

void
Parser::OnMetatagStartEntry(void)
{
  MSG("Parser::OnMetatagStartEntry(const ParsePoint::Pointer)");
}

void
Parser::OnMetatagStartExit(void)
{
  MSG("Parser::OnMetatagStartExit(const ParsePoint::Pointer)");
}

void
Parser::OnNameEnd(void)
{
  FO("Parser::OnNameEnd(const ParsePoint *)");
}

void
Parser::OnArgumentListEnd(void)
{
  FO("Parser::OnArgumentListEnd(const ParsePoint *)");
}

/* ------------------------------------------------------------------------- */

ParserException::ParserException(const TagEntry::Pointer entry, const UnicodeString &message) throw()
  : std::runtime_error(glue_cast<std::string>(message).c_str()),
    entry(entry), message(message)
{ }

ParserException::ParserException(const UnicodeString &message) throw()
  : std::runtime_error(glue_cast<std::string>(message).c_str()),
    message(message)
{ }

ParserException::~ParserException(void) throw()
{ }

const ParserException::TagEntry::Pointer
ParserException::getEntry(void) const throw()
{
  return entry;
}

const UnicodeString &
ParserException::getMessage(void) const throw()
{
  return message;
}

} /* namespace MetatagExpression */
} /* namespace mru */

