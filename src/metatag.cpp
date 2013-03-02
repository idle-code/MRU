#include "metatag.hpp"
#include "glue.hpp"
#include <stack>
#include <unicode/schriter.h>
#include <unicode/uchar.h>
#include <unicode/utypes.h>

namespace mru
{

MetatagException::MetatagException(const UnicodeString &a_message, const UnicodeString &a_expression, int a_start, int a_length) throw()
  : std::runtime_error(glue_cast<std::string>(a_message).c_str()), m_message(a_message), 
    m_expression(a_expression), m_range_start(a_start), m_range_length(a_length)
{ } 

MetatagException::~MetatagException(void) throw()
{ }

std::pair<int, int>
MetatagException::range(void) const throw()
{
  return std::make_pair(m_range_start, m_range_start + m_range_length);
}

const char *
MetatagException::what(void) const throw()
{
  std::string message(glue_cast<std::string>(m_message));
  std::string expression(glue_cast<std::string>(m_expression));
  std::stringstream ss;
  if(m_range_start == -1)
    ss << message << " (in \'" << expression << "\')";
  else //if(m_range_length == 0)
    ss << message << " (at column " << m_range_start << " in \'" << expression << "\')";
  //else
  //  ss << message << ":" << m_range_start << ": \'" << expression.substr(m_range_start, m_range_length) << "\' in \'" << expression << "\'";

  return ss.str().c_str();
}

/* ------------------------------------------------------------------------- */

Metatag::Metatag(const UnicodeString &a_name)
  : m_name(a_name)
{ }

Metatag::~Metatag(void)
{ } 

const UnicodeString &
Metatag::tagName(void) const
{
  return m_name;
}


/* ------------------------------------------------------------------------- */

UnicodeString
MetatagExpression::evaluate(const UnicodeString &a_expression, const std::list<Metatag*> &a_bindings)
{
  FO("MetatagExpression::evaluate(const UnicodeString &a_expression, const std::list<Metatag*> &a_bindings)");

  MetatagExpression me(a_expression);
  me.bind(a_bindings);
  return me.evaluate();
}

MetatagExpression::MetatagExpression(const UnicodeString &a_repr)
  : m_expression_repr(a_repr)
{ }

MetatagExpression::~MetatagExpression(void)
{ }

void
MetatagExpression::bind(const std::list<Metatag*> &a_bindings)
{
  m_bindings = a_bindings;
}

/* ------------------------------------------------------------------------- */

MetatagExpression::token::token(void)
  : position(-1), type(), value(), arguments()
{ }

MetatagExpression::token::token(int a_pos, const UnicodeString &a_value, enum token::type a_type)
  : position(a_pos), type(a_type), value(a_value), arguments()
{ }

data_tree::basic_tree<MetatagExpression::token>*
get_inserted_node(data_tree::basic_tree<MetatagExpression::token> *a_branch)
{
  data_tree::basic_tree<MetatagExpression::token>::reverse_node_iterator last = a_branch->rbegin();
  return &*last;
}

void
MetatagExpression::build_tree(const UnicodeString &a_expression)
{
  //FO("MetatagExpression::build_tree(const UnicodeString &a_expression)");
  data_tree::basic_tree<token> parse_tree_root;
  parse_tree_root.value().type = token::name;
  std::stack<data_tree::basic_tree<token>*> node_stack;
  node_stack.push(&parse_tree_root);

  bool escape_sequence = false;
  enum token::type area = token::text;
  int pos = 0;
  UnicodeString value;

  for(StringCharacterIterator i(a_expression); i.hasNext(); i.next(), ++pos) {
    UChar32 c = i.current32();

    if(c == UChar32('\\')) {
      escape_sequence = true;
      if(!i.hasNext())
        throw MetatagException("Escape character ('\\') at end of expression", a_expression, pos);
      i.next();
      c = i.current32();
      ++pos;
    }

    switch(area) {
      case token::name:
        if(c == UChar32('(')) {
          if(value.length() > 0) {
            node_stack.top()->push_back(token(pos, value, area));
            value.remove();
          }
          node_stack.push(get_inserted_node(node_stack.top()));
          area = token::args;
        } else if(!u_isUWhiteSpace(c) && u_isalnum(c))
          value.append(c);
        else
          throw MetatagException(glue_cast<UnicodeString>("Invalid character in metatag name: \'") + char(c) + "\'", a_expression, pos);
        break;

      case token::args:
        if(!escape_sequence && c == UChar32(')')) {
          node_stack.top()->value().arguments = value;
          value.remove();
          
          c = i.next();
          if(c != UChar32('{')) {
            node_stack.pop();
            i.previous();
          }

          area = token::text;
        } else
          value.append(c);
        break;

      case token::text:
        if(!escape_sequence && c == UChar32('%')) {
          if(value.length() > 0) {
            node_stack.top()->push_back(token(pos, value, area));
            value.remove();
          }
          area = token::name;
        } else if(!escape_sequence && c == UChar32('}')) {
          node_stack.top()->push_back(token(pos, value, area));
          value.remove();
          node_stack.pop();
        } else
          value.append(c);
        break;
    }

    escape_sequence = false;
  }

  if(area == token::args)
    throw MetatagException(glue_cast<UnicodeString>("Unclosed arguments list for \'") + get_inserted_node(node_stack.top())->value().value + "\' tag", a_expression, pos);
  else if(area == token::name)
    throw MetatagException(glue_cast<UnicodeString>("Unfinished metatag declaration at end of expression"), a_expression, pos);

  if(node_stack.size() != 1) {
    throw MetatagException(glue_cast<UnicodeString>("Unclosed area of effect of \'") + node_stack.top()->value().value + "\' tag", a_expression, pos);
  }

  if(value.length() > 0) {
    node_stack.top()->push_back(token(pos, value, area));
    value.remove();
  }

  m_parse_tree = parse_tree_root;
}

Metatag*
MetatagExpression::find_binding(const UnicodeString &a_tagname) const
{
  std::list<Metatag*>::const_iterator tag = m_bindings.begin(), binding_end = m_bindings.end();
  for(; tag != binding_end; ++tag) {
    if((*tag)->tagName() == a_tagname)
      return *tag;
  }

  return NULL;
}

UnicodeString
MetatagExpression::execute(const data_tree::basic_tree<token> &a_branch, bool a_prepare)
{
  //FO("MetatagExpression::execute(const data_tree::basic_tree<token> &a_branch)");

  if(a_branch.value().type == token::text) {
    return a_branch.value().value;
  }
  // else assume a_branch.value().type == token::name
  
  // find callback by tag name
  Metatag *metatag = find_binding(a_branch.value().value);
  if(metatag == NULL)
    throw MetatagException(glue_cast<UnicodeString>("Unknown tagname: \'") + a_branch.value().value + "\'", "", 0); //FIXME: add proper position and expression

  // evaluate area_of_effect
  data_tree::basic_tree<token>::const_node_iterator i = a_branch.begin();
  UnicodeString area_of_effect;
  for(; i != a_branch.end(); ++i) {
    area_of_effect += execute(*i, a_prepare);
  }

  // execute tag function
  if(a_prepare) {
    metatag->initialize(a_branch.value().arguments);
  } else {
    if(a_branch.empty())
      return (*metatag)(); //no area_of_effect specified
    else
      return (*metatag)(area_of_effect); //execute over area_of_effect
  }

  return UnicodeString();
}

namespace 
{

class EchoTag : public Metatag {
public:
  EchoTag(void)
   : Metatag("")
  { } 

  bool
  initialize(const UnicodeString &a_arguments)
  {
    return true;
  }

  UnicodeString
  operator()(void)
  {
    return UnicodeString();
  }

  UnicodeString
  operator()(const UnicodeString &a_text)
  {
    return a_text;
  }
};

} /* anonymous namespace */

UnicodeString
MetatagExpression::evaluate(void)
{
  //FO("MetatagExpression::evaluate(void)");
  VAL(glue_cast<std::string>(m_expression_repr));
  
  EchoTag echo;
  if(NULL == find_binding(UnicodeString())) {
    WARN("No top ('') tag specified. Using default EchoTag");
    m_bindings.push_back(&echo);
    //throw MetatagException(glue_cast<UnicodeString>("No top ('') tag specified"), m_expression_repr);
  }

  // build parse tree (if needed)
  if(m_parse_tree.empty()) {
    build_tree(m_expression_repr);
    execute(m_parse_tree, true);
  }
  
  // execute bindings based on parse_tree
  return execute(m_parse_tree);
}

UnicodeString
MetatagExpression::evaluate(const std::list<Metatag*> &a_bindings)
{
  bind(a_bindings);
  return evaluate();
}

} /* namespace mru */

