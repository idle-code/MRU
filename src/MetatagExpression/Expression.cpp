#include "Expression.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

#include "glue.hpp"

namespace mru {
namespace MetatagExpression {

Expression::Pointer
Expression::parse(const UnicodeString &expression_text)
{
  FO("Expression::parse(const UnicodeString &expression_text)");
  Parser parser;
  parser.parse(expression_text);
  Parser::TagEntry::Pointer expression_root = parser.getExpressionRoot();
  return boost::shared_ptr<Expression>(new Expression(expression_root)); // cannot use make_shared due to private constructor
}

UnicodeString
Expression::text(void) const
{
  return UnicodeString();
}

void
collectTagNames(const Parser::TagEntry::Pointer node, std::set<UnicodeString> &names_set)
{
  assert(node);
  names_set.insert(node->name);
  Parser::TagEntry::MemberList::const_iterator ei = node->areaOfEffectMembers.begin(); 
  Parser::TagEntry::MemberList::const_iterator ei_end = node->areaOfEffectMembers.end(); 
  for(; ei != ei_end; ++ei) {
    collectTagNames(*ei, names_set);
  }
}

std::set<UnicodeString>
Expression::getUsedMetatagNames(void) const
{
  std::set<UnicodeString> used_metatag_names;

  

  return used_metatag_names;
}

Expression::Expression(void)
{ }

Expression::Expression(Parser::TagEntry::Pointer expression_root)
  : expression_root(expression_root)
{
  assert(expression_root);
}

Expression::~Expression(void)
{ }

} /* namespace MetatagExpression */
} /* namespace mru */

