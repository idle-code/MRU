#ifndef METATAG_EXPRESSION_HPP
#define METATAG_EXPRESSION_HPP

#include "types.hpp"
#include "MetatagExpression/Metatag.hpp"
#include "MetatagExpression/Parser.hpp"
#include <stdexcept>
#include <set>

class MetatagExpression_tests; //forward declaration for tests

namespace mru {
namespace MetatagExpression {

/* ------------------------------------------------------------------------- */

class Expression {
public:
  typedef boost::shared_ptr<Expression> Pointer;
  typedef std::map<UnicodeString, Metatag::Factory::Pointer> FactoryMap;
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

    Metatag::Pointer metatag;
    MemberList areaOfEffectMembers;
  };

  Node::Pointer expression_root;
  Parser::TagEntry::Pointer entry_tree_root;
  FactoryMap metatag_factory_map;

  Expression(void);
  Expression(Parser::TagEntry::Pointer expression_root);

  Node::Pointer createExpressionTree(Parser::TagEntry::Pointer expression_node, const FactoryMap &factory_map);
  UnicodeString evaluate(const FileIterator::Pointer file_iterator, Node::Pointer node);
};

/* ------------------------------------------------------------------------- */

class Expression::Exception : public std::runtime_error {
public:
  
};

} /* namespace MetatagExpression */
} /* namespace mru */

#endif /* METATAG_EXPRESSION_HPP */

