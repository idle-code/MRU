#include "expression.hpp"
#include "glue.hpp"
#include <stack>
#include <unicode/schriter.h>
#include <unicode/uchar.h>
#include <unicode/utypes.h>
#include <debug_l.h>

namespace mru
{

MetatagExpressionException::MetatagExpressionException(const UnicodeString &a_message, int a_start, int a_length) throw()
  : std::runtime_error(glue_cast<std::string>(a_message).c_str()), m_message(a_message), 
    m_expression(UnicodeString()), m_range(std::make_pair(a_start, a_length)) 
{ } 

MetatagExpressionException::~MetatagExpressionException(void) throw()
{ }

std::pair<int, int>
MetatagExpressionException::range(void) const throw()
{
  return m_range;
}

const char *
MetatagExpressionException::what(void) const throw()
{
  std::string message(glue_cast<std::string>(m_message));
  std::string expression(glue_cast<std::string>(m_expression));
  std::stringstream ss;
  if(m_range.first == -1)

    ss << message << " (in \'" << expression << "\')";
  else //if(m_range_length == 0)
    ss << message << " (at column " << m_range.first << " in \'" << expression << "\')";
  //else
  //  ss << message << ":" << m_range_start << ": \'" << expression.substr(m_range_start, m_range_length) << "\' in \'" << expression << "\'";

  return ss.str().c_str();
}

const UnicodeString &
MetatagExpressionException::message(void) const throw()
{
  return m_message;
}

const UnicodeString &
MetatagExpressionException::expression(void) const
{
  return m_expression;
}

void
MetatagExpressionException::expression(const UnicodeString &a_expression)
{
  m_expression = a_expression;
}

/* ------------------------------------------------------------------------- */

MetatagEntry::MetatagEntry(void)
  : name(UnicodeString()), arguments(UnicodeString()), metatag(NULL), childrens()
{
  //FO("MetatagEntry::MetatagEntry(void)");
} 

MetatagEntry::MetatagEntry(const MetatagEntry &a_other)
  : name(a_other.name), arguments(a_other.arguments), metatag(a_other.metatag), childrens()
{
  for(std::list<MetatagEntry*>::const_iterator i = a_other.childrens.begin(); i != a_other.childrens.end(); ++i) {
    childrens.push_back(new MetatagEntry(**i));
  }
}

MetatagEntry::MetatagEntry(const UnicodeString &a_name)
  : name(a_name), arguments(UnicodeString()), metatag(NULL), childrens()
{
  //FO("MetatagEntry::MetatagEntry(const UnicodeString &a_name)");
} 

MetatagEntry::~MetatagEntry(void)
{
  if(metatag != NULL)
    delete metatag;
  for(std::list<MetatagEntry*>::iterator i = childrens.begin(); i != childrens.end(); ++i) {
    delete (*i);
  }
}

/* ------------------------------------------------------------------------- */

template<> inline
std::string
glue_cast<std::string, MetatagExpression::token::token_kind_type>(const MetatagExpression::token::token_kind_type &a_value)
{
  switch(a_value) {
    case MetatagExpression::token::whitespace:
      return "whitespace";
    case MetatagExpression::token::text:
      return "text";
    case MetatagExpression::token::metatag_start:
      return "metatag_start";
    case MetatagExpression::token::argument_list_start:
      return "argument_list_start";
    case MetatagExpression::token::argument_list_end:
      return "argument_list_end";
    case MetatagExpression::token::operation_area_start:
      return "operation_area_start";
    case MetatagExpression::token::operation_area_end:
      return "operation_area_end";
    default:
      return "";
  }
}


MetatagExpression::token::token(int a_index, const UnicodeString &a_value, token_kind_type a_type)
  : index(a_index), value(a_value), type(a_type)
{ }

/* ------------------------------------------------------------------------- */

MetatagExpression::MetatagExpression(void)
  : m_root(new MetatagEntry())
{
  //FO("MetatagExpression::MetatagExpression(void)");

}

MetatagExpression::MetatagExpression(const self_type &a_other)
  : m_bindings(a_other.m_bindings), m_root(new MetatagEntry(*a_other.m_root)), m_expression(a_other.m_expression)
{
  //FO("MetatagExpression::MetatagExpression(const self_type &a_other)");
}

MetatagExpression::self_type &
MetatagExpression::operator=(const self_type &a_other)
{
  //FO("MetatagExpression::operator=(const self_type &a_other)");
  m_bindings = a_other.m_bindings;
  delete m_root;
  m_root = new MetatagEntry(*a_other.m_root);
  m_expression = a_other.m_expression;
  return *this;
}

MetatagExpression::~MetatagExpression(void)
{
  //FO("MetatagExpression::~MetatagExpression(void)");
  delete m_root;
}

std::list<MetatagExpression::token>
MetatagExpression::tokenize(const UnicodeString &a_expression)
{
  //FO("MetatagExpression::tokenize(const UnicodeString &a_expression)");
  std::list<token> token_list;

  icu::StringCharacterIterator iter(a_expression);
  UnicodeString value;
  token::token_kind_type last_token_type = token::text;

  bool escape_next = false;
  int i = 0;
  for(UChar c = iter.first(); iter.hasNext(); ++i, c = iter.next()) {
    //VAL((char)c);

    token::token_kind_type current_token_type = token::text;
    if(escape_next) {
      escape_next = false;
      current_token_type = token::text;
    } else {
      if(c == glue_cast<UChar>('\\')) {
        escape_next = true;
        continue;
      } else if(c == glue_cast<UChar>('(')) {
        current_token_type = token::argument_list_start;
      } else if(c == glue_cast<UChar>(')')) {
        current_token_type = token::argument_list_end;
      } else if(c == glue_cast<UChar>('%')) {
        current_token_type = token::metatag_start;
      } else if(c == glue_cast<UChar>('{')) {
        current_token_type = token::operation_area_start;
      } else if(c == glue_cast<UChar>('}')) {
        current_token_type = token::operation_area_end;
      } else if(u_isWhitespace(c)) {
        current_token_type = token::whitespace;
      } else {
        current_token_type = token::text;
      }
    }
    //VAL(glue_cast<std::string>(last_token_type));
    //VAL(glue_cast<std::string>(current_token_type));
    
    if(current_token_type == last_token_type) {
      if(current_token_type == token::whitespace || current_token_type == token::text)
        value += c;
      else {
        token_list.push_back(token(i, c, current_token_type));
        //VAL(glue_cast<std::string>(token_list.back().type));
      }
    } else {
      if(!value.isEmpty()) {
        token_list.push_back(token(i-value.length(), value, last_token_type));
        //VAL(glue_cast<std::string>(token_list.back().type));
        value.remove();
      }

      if(current_token_type == token::whitespace || current_token_type == token::text)
        value += c;
      else {
        token_list.push_back(token(i, c, current_token_type));
        //VAL(glue_cast<std::string>(token_list.back().type));
      }
    }
    //VAL(glue_cast<std::string>(value));
    
    last_token_type = current_token_type;

    //MSG("---");
  }
  
  if(!value.isEmpty()) {
    token_list.push_back(token(i-value.length(), value, last_token_type));
  }
  
  return token_list;
}

namespace
{

class EchoTag : public Metatag {
public:
  typedef Metatag parent_type;
  EchoTag(void)
   : Metatag(glue_cast<UnicodeString>(""))
  { } 

  void initialize(const UnicodeString &a_arguments)
  {
    m_value = a_arguments; 
  }

  UnicodeString execute(const UnicodeString &a_file_path, const UnicodeString &a_area_of_effect)
  {
    return m_value + a_area_of_effect;
  }
private:
  UnicodeString m_value;
};

} /* anonymous namespace  */

void
MetatagExpression::parse(MetatagEntry *a_parent, std::list<token>::iterator &iter, const std::list<token>::iterator &a_end)
{
  //FO("MetatagExpression::parse(MetatagEntry *a_parent, std::list<token>::iterator &iter, const std::list<token>::iterator &a_end)");

  MetatagEntry *current_entry = NULL;
  while(iter != a_end) {
    token tok = (*iter);

    //VAL(glue_cast<std::string>(tok.type));
    //VAL(glue_cast<std::string>(tok.value));
    //VAL(tok.value.length());
    //VAL(tok.index);
    
    switch(iter->type) {
      case token::metatag_start:
        ++iter;
        if(iter->type != token::text)
          throw MetatagExpressionException("Metatag name expected", iter->index);
        assert(current_entry == NULL);
        current_entry = new MetatagEntry();
        current_entry->name = iter->value; 
        ++iter;
        if(iter->type != token::argument_list_start)
          throw MetatagExpressionException(glue_cast<UnicodeString>("Argument list for metatag '") + current_entry->name + glue_cast<UnicodeString>("' expected"), iter->index);
        break;

      case token::argument_list_start:
        if(current_entry == NULL) {
          //issue a warning?
          iter->type = token::text; //treat as normal text
          break;
        }
        ++iter;
        current_entry->arguments = UnicodeString();
        while(iter != a_end && iter->type != token::argument_list_end) {
          current_entry->arguments += iter->value;
          ++iter;
        }
        if(iter == a_end)
          throw MetatagExpressionException(glue_cast<UnicodeString>("Unclosed argument list for metatag '") + current_entry->name + glue_cast<UnicodeString>("'"), -1);
        ++iter;
        if(iter->type != token::operation_area_start) {
          m_bindings[current_entry->name] = NULL;
          a_parent->add_child(current_entry);
        }
        break;

      case token::operation_area_start:
        if(current_entry == NULL) {
          //issue a warning?
          iter->type = token::text; //treat as normal text
          break;
        }
        ++iter;
        parse(current_entry, iter, a_end);
        if(iter == a_end)
          throw MetatagExpressionException(glue_cast<UnicodeString>("Unclosed area of effect for metatag '") + current_entry->name + glue_cast<UnicodeString>("'"), -1);
        ++iter;
        m_bindings[current_entry->name] = NULL;
        a_parent->add_child(current_entry);
        break;

      case token::operation_area_end:
        return;

      case token::argument_list_end: //FIXME?
      case token::whitespace:
      case token::text:
        assert(current_entry == NULL);
        current_entry = new MetatagEntry();
        current_entry->name = "";
        do {
          current_entry->arguments += iter->value;
          ++iter;
        } while(iter->type == token::whitespace || iter->type == token::text);
        m_bindings[current_entry->name] = NULL;
        a_parent->add_child(current_entry);
        break;
    }
  }
}

void
print_tree(const MetatagEntry *a_entry, int level=0)
{
  UnicodeString indent;
  for(int i = 0; i < level; ++i)
    indent += ">>"; 
  
  for(std::list<MetatagEntry*>::const_iterator i=a_entry->childrens.begin(); i!=a_entry->childrens.end(); ++i) {
    MSG(glue_cast<std::string>(indent + (*i)->name));
    MSG(glue_cast<std::string>(indent + (*i)->arguments));
    MSG(glue_cast<std::string>(indent + "--------------"));
    print_tree(*i, level+1);
  }
}

MetatagExpression
MetatagExpression::parse(const UnicodeString &a_expression)
{
  //FO("MetatagExpression::parse(const UnicodeString &a_expression)");
  MetatagExpression expression;
  //VAL(glue_cast<std::string>(a_expression));

  std::list<token> tokens = tokenize(a_expression);
  std::list<token>::iterator start = tokens.begin();
  try {
    expression.parse(expression.m_root, start, tokens.end());
    if(start != tokens.end())
      throw MetatagExpressionException("Unexpected area of effect end", start->index);
    //print_tree(expression.m_root);
  } catch(MetatagExpressionException &mee) {
    mee.expression(a_expression);
    throw mee;
  }
  
  expression.m_expression = a_expression;
  return expression;
}

std::map<UnicodeString, abstract_factory<Metatag>*>
MetatagExpression::bindings(void) const
{
  return m_bindings;
}

void
apply_bindings(MetatagEntry *a_entry, const std::map<UnicodeString, abstract_factory<Metatag>*> a_bindings)
{
  //FO("apply_bindings(MetatagEntry *a_entry, const std::map<UnicodeString, abstract_factory<Metatag>*> a_bindings)");
  //VAL(a_bindings.size());
  std::map<UnicodeString, abstract_factory<Metatag>*>::const_iterator binding = a_bindings.find(a_entry->name);
  //VAL(a_entry);
  //VAL(a_entry->metatag);
  //VAL(glue_cast<std::string>(a_entry->metatag->name()));
  //VAL(a_entry->childrens.size());
  //VAL(glue_cast<std::string>(a_entry->name));
  //VAL(glue_cast<std::string>(a_entry->arguments));
  if(binding == a_bindings.end() || (*binding).second == NULL)
      throw MetatagExpressionException(glue_cast<UnicodeString>("No '") + a_entry->name + glue_cast<UnicodeString>("' metatag handler defined"), -1);
  a_entry->metatag = (*binding).second->create();

  for(std::list<MetatagEntry*>::iterator i = a_entry->childrens.begin(); i != a_entry->childrens.end(); ++i)
    apply_bindings(*i, a_bindings);
}

void
MetatagExpression::bindings(const std::map<UnicodeString, abstract_factory<Metatag>*> &a_bindings)
{
  //FO("MetatagExpression::bindings(const std::map<UnicodeString, abstract_factory<Metatag>*> &a_bindings)");
  m_bindings = a_bindings;

  if(m_bindings[UnicodeString()] == NULL)
    m_bindings[UnicodeString()] = new factory<EchoTag>();

  //VAL(m_root);
  //VAL(m_root->metatag);
  apply_bindings(m_root, m_bindings);
}

UnicodeString
MetatagExpression::evaluate(const UnicodeString &a_file_path)
{
  initialize(m_root);
  return evaluate(a_file_path, m_root);
}

void
MetatagExpression::initialize(MetatagEntry *a_entry)
{
  //FO("MetatagExpression::initialize(MetatagEntry *a_entry)");
  assert(a_entry != NULL);
  assert(a_entry->metatag != NULL);
  a_entry->metatag->initialize(a_entry->arguments);
  for(std::list<MetatagEntry*>::iterator i = a_entry->childrens.begin(); i != a_entry->childrens.end(); ++i)
    initialize(*i);
}

UnicodeString
MetatagExpression::evaluate(const UnicodeString &a_file_path, MetatagEntry *a_entry)
{
  assert(a_entry != NULL);
  assert(a_entry->metatag != NULL);
  UnicodeString area_of_effect;
  for(std::list<MetatagEntry*>::iterator i = a_entry->childrens.begin(); i != a_entry->childrens.end(); ++i)
    area_of_effect += evaluate(a_file_path, *i);
  //MSG("Executing " << glue_cast<std::string>(a_entry->name));
  return a_entry->metatag->execute(a_file_path, area_of_effect);
}

UnicodeString
MetatagExpression::evaluate(const UnicodeString &a_file_path, const std::map<UnicodeString, abstract_factory<Metatag>*> &a_bindings)
{
  bindings(a_bindings);
  return evaluate(a_file_path);
}

void
MetatagExpression::reset(MetatagEntry *a_entry)
{
  if(a_entry->metatag != NULL)
    a_entry->metatag->reset();
  for(std::list<MetatagEntry*>::iterator i = a_entry->childrens.begin(); i != a_entry->childrens.end(); ++i)
    reset(*i);
}

void
MetatagExpression::reset(void)
{
  reset(m_root);
}

UnicodeString
MetatagExpression::str(void) const
{
  return m_expression;
}

} /* namespace mru */

