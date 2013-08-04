#include "tests/UnicodeStringStreamOperator.hpp" //temporary
#include "MetatagExpressionParser.hpp"
#define MSG(M) std::cout << M << std::endl;

namespace mru
{

MetatagExpressionParser::Entry::Entry(int position)
  : position(position)
{ }

MetatagExpressionParser::Entry::Entry(int position, const UnicodeString &name, const UnicodeString &arguments)
  : position(position), name(name), arguments(arguments)
{ }

void
MetatagExpressionParser::Entry::addAreaOfEffectMember(int position, const UnicodeString &name, const UnicodeString &arguments)
{
  areaOfEffectMembers.push_back(Pointer(new Entry(position, name, arguments)));
}

bool
MetatagExpressionParser::Entry::isAreaOfEffectMembersPresent(void) const
{
  return areaOfEffectMembers.size() != 0;
}

/* ------------------------------------------------------------------------- */


MetatagExpressionParser::MetatagExpressionParser(void)
{
  // expression start
  ParsePoint::Pointer point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::Text;
  parser_states.insert(std::make_pair("start", point));
  // text
  point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::Text;
  parser_states.insert(std::make_pair("text", point));
  // metatag start
  point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::MetatagStart;
  point->onEntry = &MetatagExpressionParser::OnMetatagStartEntry;
  point->onExit = &MetatagExpressionParser::OnMetatagStartExit;
  parser_states.insert(std::make_pair("%", point));
  // metatag name
  point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::Text;
  parser_states.insert(std::make_pair("metatag name", point));
  // metatg arg start
  point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::ArgumentListStart;
  parser_states.insert(std::make_pair("(", point));
  // metatag args
  point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::Text;
  parser_states.insert(std::make_pair("metatag arguments", point));
  // metatag arg end
  point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::ArgumentListEnd;
  parser_states.insert(std::make_pair(")", point));
  
  // expression end
  point = ParsePoint::Pointer(new ParsePoint());
  point->type = Token::Text;
  parser_states.insert(std::make_pair("end", point));

  /* ------------------------------------------------------------------------- */
  
  parser_states["start"]->exitPoints.push_back(parser_states["text"]);
  parser_states["start"]->exitPoints.push_back(parser_states["%"]);
  parser_states["start"]->exitPoints.push_back(parser_states["end"]);

  parser_states["text"]->exitPoints.push_back(parser_states["text"]);
  parser_states["text"]->exitPoints.push_back(parser_states["%"]);
  parser_states["text"]->exitPoints.push_back(parser_states["end"]);

  parser_states["%"]->exitPoints.push_back(parser_states["metatag name"]);

  parser_states["metatag name"]->exitPoints.push_back(parser_states["("]);

  parser_states["("]->exitPoints.push_back(parser_states["metatag arguments"]);
  parser_states["("]->exitPoints.push_back(parser_states[")"]);

  parser_states["metatag arguments"]->exitPoints.push_back(parser_states["metatag arguments"]);
  parser_states["metatag arguments"]->exitPoints.push_back(parser_states[")"]);

  parser_states[")"]->exitPoints.push_back(parser_states["text"]);
  parser_states[")"]->exitPoints.push_back(parser_states["end"]);
  //parser_states[")"]->exitPoints.push_back(parser_states["{"]);
}

MetatagExpressionParser::~MetatagExpressionParser(void)
{
  clearParserStatesMap();
}

void
MetatagExpressionParser::clearParserStatesMap(void)
{
  for(std::map<std::string, ParsePoint::Pointer>::iterator state_iter = parser_states.begin();
      state_iter != parser_states.end();
      ++state_iter)
  {
    (*state_iter).second->exitPoints.clear();
  }

  parser_states.clear();
}

MetatagExpressionParser::Entry::Pointer
MetatagExpressionParser::parse(const UnicodeString &expression_text)
{
  root.reset();
  root = Entry::Pointer(new Entry(-1, "", ""));

  if (expression_text.isEmpty())
    return root;
  VAL(expression_text);

  const TokenList &tokens = lexer.analyze(expression_text);
  tok_iter = tokens.begin();
  tok_iter_end = tokens.end();

  parse(root);

  return root;
}

MetatagExpressionParser::ParsePoint::Pointer
MetatagExpressionParser::ParsePoint::getNextExitPoint(Token::TokenKind type)
{
  VAL(exitPoints.size()); 
  for(std::list<Pointer>::iterator iter = exitPoints.begin(); iter != exitPoints.end(); ++iter) {
    VAL((*iter)->type);
    if ((*iter)->type == type)
      return *iter;
  }
  return Pointer();
}

void
MetatagExpressionParser::parse(Entry::Pointer parent)
{
  MSG("MetatagExpressionParser::parse(Entry::Pointer parent)");
  VAL(this);
  assert(parent);

  VAL(parent->position);
  VAL(parent->name);
  VAL(parent->arguments);

  Entry::Pointer new_entry;
  ParsePoint::Pointer current_point = parser_states["start"];
  ParsePoint::Pointer new_point;

  for(; tok_iter != tok_iter_end; ++tok_iter) {
    std::cout << "----------------------" << std::endl;
    const Token &token = *tok_iter;

    VAL(token.position);
    VAL(token.value);
    VAL(token.type);

    VAL(current_point);
    VAL(current_point->type);  
    new_point = current_point->getNextExitPoint(token.type);
    if (new_point) {
      if (current_point->onExit)
        (this->*(current_point->onExit))(new_point);
      if (new_point->onEntry)
        (this->*(new_point->onEntry))(current_point);
      VAL(new_point->type);
      current_point = new_point;
    } else {
      std::cout << "Error cannot move to next parse point" << std::endl;
    }
  }
}

void
MetatagExpressionParser::OnMetatagStartEntry(const ParsePoint::Pointer)
{
  MSG("MetatagExpressionParser::OnMetatagStartEntry(const ParsePoint::Pointer)");
}

void
MetatagExpressionParser::OnMetatagStartExit(const ParsePoint::Pointer)
{
  MSG("MetatagExpressionParser::OnMetatagStartExit(const ParsePoint::Pointer)");
}

/* ------------------------------------------------------------------------- */

MetatagExpressionParserException::MetatagExpressionParserException(const Entry::Pointer entry, const UnicodeString &message) throw()
  : std::runtime_error(glue_cast<std::string>(message).c_str()),
    entry(entry), message(message)
{

}

MetatagExpressionParserException::MetatagExpressionParserException(const UnicodeString &message) throw()
  : std::runtime_error(glue_cast<std::string>(message).c_str()),
    message(message)
{ }

MetatagExpressionParserException::~MetatagExpressionParserException(void) throw()
{ }

const MetatagExpressionParserException::Entry::Pointer
MetatagExpressionParserException::getEntry(void) const throw()
{
  return entry;
}

const UnicodeString &
MetatagExpressionParserException::getMessage(void) const throw()
{
  return message;
}

} /* namespace mru */

