#include "StdIteratorAdapter_tests.hpp"

StdIteratorAdapter_tests::StdIteratorAdapter_tests(void)
  : container(), const_container(container)
{ }

void
StdIteratorAdapter_tests::SetUp(void)
{
  val1 = "1";
  val2 = "2";
  val3 = "3";
}
 
void
StdIteratorAdapter_tests::TearDown(void)
{
  container.clear();
}
 

/* ------------------------------------------------------------------------- */

void
StdIteratorAdapter_tests::iterator_end(void)
{
  Iterator end_iter(container.begin(), container.end());

  CPPUNIT_ASSERT(end_iter.atEnd());
}

void
StdIteratorAdapter_tests::iterator_progress(void)
{
  container.push_back(val1);
  container.push_back(val2);
  container.push_back(val3);

  Iterator iter(container.begin(), container.end());

  CPPUNIT_ASSERT(!iter.atEnd());

  CPPUNIT_ASSERT_EQUAL(val1, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val2, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val3, iter.getCurrent());
  CPPUNIT_ASSERT(!iter.next());

  CPPUNIT_ASSERT(iter.atEnd());
}

void
StdIteratorAdapter_tests::iterator_reset(void)
{
  container.push_back(val1);
  container.push_back(val2);
  container.push_back(val3);

  Iterator iter(container.begin(), container.end());

  CPPUNIT_ASSERT(!iter.atEnd());

  CPPUNIT_ASSERT_EQUAL(val1, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val2, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val3, iter.getCurrent());
  CPPUNIT_ASSERT(!iter.next());

  CPPUNIT_ASSERT(iter.atEnd());

  iter.first();

  CPPUNIT_ASSERT(!iter.atEnd());

  CPPUNIT_ASSERT_EQUAL(val1, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val2, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val3, iter.getCurrent());
  CPPUNIT_ASSERT(!iter.next());

  CPPUNIT_ASSERT(iter.atEnd());
}

/* ------------------------------------------------------------------------- */

void
StdIteratorAdapter_tests::const_iterator_end(void)
{
  ConstIterator end_iter(const_container.begin(), const_container.end());

  CPPUNIT_ASSERT(end_iter.atEnd());
}

void
StdIteratorAdapter_tests::const_iterator_progress(void)
{
  container.push_back(val1);
  container.push_back(val2);
  container.push_back(val3);

  ConstIterator iter(const_container.begin(), const_container.end());

  CPPUNIT_ASSERT(!iter.atEnd());

  CPPUNIT_ASSERT_EQUAL(val1, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val2, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val3, iter.getCurrent());
  CPPUNIT_ASSERT(!iter.next());

  CPPUNIT_ASSERT(iter.atEnd());
}

void
StdIteratorAdapter_tests::const_iterator_reset(void)
{
  container.push_back(val1);
  container.push_back(val2);
  container.push_back(val3);

  ConstIterator iter(const_container.begin(), const_container.end());

  CPPUNIT_ASSERT(!iter.atEnd());

  CPPUNIT_ASSERT_EQUAL(val1, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val2, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val3, iter.getCurrent());
  CPPUNIT_ASSERT(!iter.next());

  CPPUNIT_ASSERT(iter.atEnd());

  iter.first();

  CPPUNIT_ASSERT(!iter.atEnd());

  CPPUNIT_ASSERT_EQUAL(val1, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val2, iter.getCurrent());
  CPPUNIT_ASSERT(iter.next());
  CPPUNIT_ASSERT_EQUAL(val3, iter.getCurrent());
  CPPUNIT_ASSERT(!iter.next());

  CPPUNIT_ASSERT(iter.atEnd());
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(StdIteratorAdapter_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */



