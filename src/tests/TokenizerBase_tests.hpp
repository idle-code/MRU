#ifndef TOKENIZER_TESTS_HPP
#define TOKENIZER_TESTS_HPP

#include "glue.hpp"
using namespace mru;
#include "TokenizerBase.hpp"
#include "ConstIterator_tests.hpp"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

class TokenizerBase_tests : public ConstIterator_tests<UnicodeString> {
public:
  typedef ConstIterator_tests<UnicodeString> Parent;
  typedef Parent::ValueList ValueList;
public:
  void setUp(void);

  void no_split(void);
  void simple_split_left(void);
  void split_left(void);
  void simple_split_right(void);
  void split_right(void);
  void simple_split_both(void);
  void split_both(void);
  void mixed_split(void);

  void space_strip(void);
  void space_merge(void);
  void space_trimming(void);

  void escape_sequence(void);
  void constant_size(void);

  ValueList getSampleValues(void);
  mru::ConstIterator<UnicodeString>::Pointer getConstIterator(const ValueList &values_in_container);

  CPPUNIT_TEST_SUB_SUITE(TokenizerBase_tests, Parent);
    CPPUNIT_TEST(no_split);
    CPPUNIT_TEST(simple_split_left);
    CPPUNIT_TEST(split_left);
    CPPUNIT_TEST(simple_split_right);
    CPPUNIT_TEST(split_right);
    CPPUNIT_TEST(simple_split_both);
    CPPUNIT_TEST(split_both);
    CPPUNIT_TEST(mixed_split);

    CPPUNIT_TEST(space_strip);
    CPPUNIT_TEST(space_merge);
    CPPUNIT_TEST(space_trimming);

    CPPUNIT_TEST(escape_sequence);
    CPPUNIT_TEST(constant_size);
  CPPUNIT_TEST_SUITE_END();

private:
  UnicodeString expr_str;
  std::list<UnicodeString> expected_words;
  void compare_to_expected(TokenizerBase &tokenizer);
};

#define WORD(VAL) \
  expected_words.push_back(glue_cast<UnicodeString>(VAL));

#endif /* TOKENIZER_TESTS_HPP */

