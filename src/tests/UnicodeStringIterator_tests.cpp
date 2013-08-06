#include "UnicodeStringIterator.hpp"
#include "ConstIterator_tests.hpp"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;
using namespace mru;

class UnicodeStringIterator_tests : public ConstIterator_tests<UChar> {
public:
  typedef ConstIterator_tests<UChar> Parent;
  typedef Parent::ValueList ValueList;
public:
  ValueList
  getSampleValues(void)
  {
    ValueList values;
    values.push_back(UChar('a'));
    values.push_back(UChar('b'));
    values.push_back(UChar('c'));
    return values;
  }

  ConstIterator::Pointer
  getConstIterator(const ValueList &values_in_container)
  {
    sample_string.remove();
    for(ValueList::const_iterator i = values_in_container.begin(); i != values_in_container.end(); ++i) {
      sample_string += (*i); 
    }
    return ConstIterator::Pointer(new ConstUnicodeStringIterator(sample_string));
  }

  CPPUNIT_TEST_SUB_SUITE(UnicodeStringIterator_tests, Parent);
  CPPUNIT_TEST_SUITE_END();
private:
  UnicodeString sample_string;
};

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(UnicodeStringIterator_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

