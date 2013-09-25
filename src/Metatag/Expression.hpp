#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "MruException.hpp"
#include "types.hpp"
#include "MetatagBase.hpp"
#include "Metatag/Parser.hpp"
#include <set>

class MetatagExpression_tests; //forward declaration for tests

namespace mru {
namespace Metatag {

/* ------------------------------------------------------------------------- */

class Expression {
public:
  typedef boost::shared_ptr<Expression> Pointer;
  typedef std::map<UnicodeString, MetatagBase::Factory::Pointer> FactoryMap;
  friend class ::MetatagExpression_tests;
  class Exception;
  //friend class Exception;

  static Expression::Pointer parse(const UnicodeString &expression_text);
public:
  ~Expression(void);

  UnicodeString text(void) const;

  void bindFactoryMap(const FactoryMap &factory_map);
  const FactoryMap& getFactoryMap(void) const;

  UnicodeString evaluate(const FileIterator::Pointer file_iterator);

private:
  struct Node {
    typedef boost::shared_ptr<Node> Pointer;
    typedef std::list<Pointer> MemberList;

    MetatagBase::Pointer metatag;
    MemberList areaOfEffectMembers;
  };

  Node::Pointer expression_root;
  Parser::TagEntry::Pointer entry_tree_root;
  FactoryMap metatag_factory_map;
  UnicodeString expression_text;

  Expression(void);
  Expression(Parser::TagEntry::Pointer expression_root, const UnicodeString &expression_text);

  Node::Pointer createExpressionTree(Parser::TagEntry::Pointer expression_node, const FactoryMap &factory_map);
  UnicodeString evaluate(const FileIterator::Pointer file_iterator, Node::Pointer node);
};

/* ------------------------------------------------------------------------- */

class Expression::Exception : public MruException {
public:
  Exception(const Expression::Node::Pointer node, const UnicodeString &message) throw()
    : MruException(message), node(node)
  { }

  Exception(const UnicodeString &message) throw()
    : MruException(message)
  { }

  ~Exception(void) throw()
  { }

  const Expression::Node::Pointer
  getEntry(void) const throw()
  {
    return node;
  }
private:
  Expression::Node::Pointer node;
};

} /* namespace Metatag */
} /* namespace mru */

#endif /* EXPRESSION_HPP */

