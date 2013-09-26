#include "Expression.hpp"
#include <unicode/schriter.h>
#include <unicode/uchar.h>

#include "glue.hpp"

namespace mru {
namespace Metatag {

Expression::Pointer
Expression::parse(const UnicodeString &expression_text)
{
  Parser parser;
  try {
    parser.parse(expression_text);
    Parser::TagEntry::Pointer expression_root = parser.getExpressionRoot();
    return boost::shared_ptr<Expression>(new Expression(expression_root, expression_text)); // cannot use make_shared due to private constructor
  } catch (Metatag::Parser::Exception pe) {
    throw Exception(pe.getMessage());
  }
}

UnicodeString
Expression::text(void) const
{
  return expression_text;
}

Expression::Expression(void)
{ }

Expression::Expression(Parser::TagEntry::Pointer tag_entry_root, const UnicodeString &expression_text)
  : entry_tree_root(tag_entry_root), expression_text(expression_text)
{
  assert(tag_entry_root);
}

Expression::~Expression(void)
{ }

Expression::Node::Pointer
Expression::createExpressionTree(Parser::TagEntry::Pointer expression_node, const FactoryMap &factory_map)
{
  Node::Pointer new_node = boost::make_shared<Node>();
  FactoryMap::const_iterator metatag_factory = factory_map.find(expression_node->name);
  if (metatag_factory == factory_map.end())
    throw MetatagBase::Exception(expression_node->name, glue_cast<UnicodeString>("No binding found for '") + expression_node->name + "' metatag");

  new_node->metatag = (*metatag_factory).second->create();
  assert(new_node->metatag);
  new_node->metatag->initialize(core, expression_node->arguments);

  for(Parser::TagEntry::MemberList::const_iterator i = expression_node->areaOfEffectMembers.begin();
      i != expression_node->areaOfEffectMembers.end();
      ++i)
  {
    new_node->areaOfEffectMembers.push_back(createExpressionTree(*i, factory_map));
  }

  return new_node;
}

namespace
{

class EchoMetatag : public MetatagBase {
public:
  typedef boost::shared_ptr<EchoMetatag> Pointer;
  class Factory;
  friend class Factory;

  class Factory : public MetatagBase::Factory {
  public:
    MetatagBase::Pointer
    create(void)
    {
      return boost::make_shared<EchoMetatag>();
    }
  };
public:
  EchoMetatag(void)
  { }

  void
  initialize(MruCore *, const UnicodeString &arguments)
  {
    text = arguments;
  }

  UnicodeString
  execute(const FilePath &, const UnicodeString &area_of_effect)
  {
    return text + area_of_effect;
  }
private:
  UnicodeString text;
};

} /* anonymous namespace */

void
Expression::bindFactoryMap(const FactoryMap &factory_map, MruCore *core)
{
  this->core = core;
  assert(this->core);
  metatag_factory_map = factory_map;
  if (metatag_factory_map.find(UnicodeString()) == metatag_factory_map.end())
    metatag_factory_map.insert(std::make_pair(UnicodeString(), boost::make_shared<EchoMetatag::Factory>()));
  assert(entry_tree_root);
  expression_root = createExpressionTree(entry_tree_root, metatag_factory_map);
}

const Expression::FactoryMap &
Expression::getFactoryMap(void) const
{
  return metatag_factory_map;
}

void
Expression::reset(void)
{
  if (expression_root)
    reset(expression_root);
}

void
Expression::reset(Expression::Node::Pointer node_to_reset)
{
  assert(node_to_reset);
  if (node_to_reset->metatag)
    node_to_reset->metatag->reset();

  for (Node::MemberList::const_iterator i = node_to_reset->areaOfEffectMembers.begin();
       i != node_to_reset->areaOfEffectMembers.end();
       ++i)
  {
    reset(*i);
  }
}

UnicodeString
Expression::evaluate(const FilePath &file_path)
{
  assert(entry_tree_root);

  if (metatag_factory_map.find(UnicodeString()) == metatag_factory_map.end())
    metatag_factory_map.insert(std::make_pair(UnicodeString(), boost::make_shared<EchoMetatag::Factory>()));

  if (!expression_root)
    expression_root = createExpressionTree(entry_tree_root, metatag_factory_map);
  assert(expression_root);

  return evaluate(file_path, expression_root);
}

UnicodeString
Expression::evaluate(const FilePath &file_path, Node::Pointer node)
{
  UnicodeString area_of_effect_text;
  for (Node::MemberList::const_iterator i = node->areaOfEffectMembers.begin();
       i != node->areaOfEffectMembers.end();
       ++i)
  {
    area_of_effect_text += evaluate(file_path, *i);
  } 

  return node->metatag->execute(file_path, area_of_effect_text);
}

} /* namespace Metatag */
} /* namespace mru */

