#ifndef TOKENIZER_TESTS_HPP
#define TOKENIZER_TESTS_HPP

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Tokenizer.hpp"
#include <list>

using namespace CppUnit;
using namespace mru;

class Tokenizer_tests : public TestCase {
public:
  void setUp(void);

  void no_split(void);
  void split_left(void);
  void split_right(void);
  void split_both(void);

  void space_strip(void);
  void space_merge(void);
  void space_trimming(void);

  void escape_sequence(void);
  void constant_size(void);

  void static_join(void);
  void join(void);
  void get_words(void);

  CPPUNIT_TEST_SUITE(Tokenizer_tests);
    CPPUNIT_TEST(no_split);
    CPPUNIT_TEST(split_left);
    CPPUNIT_TEST(split_right);
    CPPUNIT_TEST(split_both);

    CPPUNIT_TEST(space_strip);
    CPPUNIT_TEST(space_merge);
    CPPUNIT_TEST(space_trimming);

    CPPUNIT_TEST(escape_sequence);
    CPPUNIT_TEST(constant_size);

    CPPUNIT_TEST(static_join);
    CPPUNIT_TEST(join);
    CPPUNIT_TEST(get_words);
  CPPUNIT_TEST_SUITE_END();

private:
  UnicodeString expr_str;
  Tokenizer::WordList expected_words;
  void compare_word_lists(const Tokenizer::WordList &provided_words);
};

#define WORD(VAL) \
  expected_words.push_back(glue_cast<UnicodeString>(VAL));

#endif /* TOKENIZER_TESTS_HPP */

