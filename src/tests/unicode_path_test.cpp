#include "unicode_path_test.hpp"
#include <cppunit/ui/text/TestRunner.h>
using namespace std;

unicode_path_tests::unicode_path_tests() 
  : TestCase("unicode_path class tests") { }
unicode_path_tests::~unicode_path_tests() { }

void unicode_path_tests::construction_and_assignment(void)
{
  unicode_path::const_iterator i;
  unicode_path::base_type bp(true);
  bp /= L"dir1";
  bp /= L"dir2";
  bp /= L"field";
  
  unicode_path path1; // default constructor
  const unicode_path path2(true, '/');
  const unicode_path path3(bp, ':'); //from base_type constructor
  unicode_path path4(path3); // copy constructor
  unicode_path path5(L":dir1:dir2:field:", ':'); // from const char* path constructor
  unicode_path path6(value_type(L":dir1:dir2:field"), ':');  // from string(class) path constructor
  

  CPPUNIT_ASSERT(path1.direct() == false);
  CPPUNIT_ASSERT(path1.separator() == '.');
  CPPUNIT_ASSERT(path1.empty() == true);
  CPPUNIT_ASSERT_EQUAL(value_type(L""), value_type(path1));
  
  CPPUNIT_ASSERT(path2.direct() == true);
  CPPUNIT_ASSERT(path2.separator() == '/');
  CPPUNIT_ASSERT_EQUAL(value_type(L"/"), value_type(path2));
  
  CPPUNIT_ASSERT(path3.direct() == true);
  CPPUNIT_ASSERT(path3.separator() == ':');
  CPPUNIT_ASSERT_EQUAL(value_type(L":dir1:dir2:field"), value_type(path3));
  i = path3.begin();
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir1"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir2"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"field"), (*i)); ++i;
  CPPUNIT_ASSERT(i == path3.end());
  
  CPPUNIT_ASSERT(path3 == path4);
  CPPUNIT_ASSERT(path4 == path5);
  CPPUNIT_ASSERT(path5 == path6);
  
  path4.direct(false);
  CPPUNIT_ASSERT(path4.direct() == false);
  CPPUNIT_ASSERT(path4.separator() == ':');
  CPPUNIT_ASSERT(value_type(path4) == value_type(L"dir1:dir2:field"));
  i = path4.begin();
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir1"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir2"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"field"), (*i)); ++i;
  CPPUNIT_ASSERT(i == path4.end());
  
  path5.separator('.');
  CPPUNIT_ASSERT(path5.direct() == true);
  CPPUNIT_ASSERT(path5.separator() == '.');
  CPPUNIT_ASSERT(value_type(path5) == value_type(L".dir1.dir2.field"));
  i = path5.begin();
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir1"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir2"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"field"), (*i)); ++i;
  CPPUNIT_ASSERT(i == path5.end());
  
  path6.separator('.');
  path6.direct(false);
  CPPUNIT_ASSERT(path6.direct() == false);
  CPPUNIT_ASSERT(path6.separator() == '.');
  CPPUNIT_ASSERT(value_type(path6) == value_type(L"dir1.dir2.field"));
  i = path6.begin();
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir1"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"dir2"), (*i)); ++i;
  CPPUNIT_ASSERT_EQUAL(value_type(L"field"), (*i)); ++i;
  CPPUNIT_ASSERT(i == path6.end());
}

void unicode_path_tests::concatenation(void)
{
  unicode_path path1(L".. dir1");
  const unicode_path path2(L"   dir2. .dir3"), e1(L" element_1 "), e2(L"element_2");
  unicode_path r1(path1 + path2), r2(false, '/');
  
  CPPUNIT_ASSERT(r1 == (path1+path2));
  r1 /= e1;
  CPPUNIT_ASSERT(r1 == (path1/path2/e1));
  
  r2 += e2 + e1 + path2;
  CPPUNIT_ASSERT(value_type(r2) == value_type(L"element_2/element_1/dir2/dir3"));
  r2 /= L"element_3/";
  CPPUNIT_ASSERT(value_type(r2) == value_type(L"element_2/element_1/dir2/dir3/element_3"));
  r2 /= L"dir4  /// element_5  ";
  r2.separator('.');
  CPPUNIT_ASSERT(value_type(r2) == value_type(L"element_2.element_1.dir2.dir3.element_3.dir4.element_5"));
  
  r2.separator('+');
  path1 += r2;
  CPPUNIT_ASSERT(value_type(path1) == value_type(L".dir1.element_2.element_1.dir2.dir3.element_3.dir4.element_5"));
  path1.pop_back();
  CPPUNIT_ASSERT(value_type(path1) == value_type(L".dir1.element_2.element_1.dir2.dir3.element_3.dir4"));
  
  r1.clear();
  CPPUNIT_ASSERT(value_type(r1) == value_type(L"."));
  r1 += L"";
  CPPUNIT_ASSERT(value_type(r1) == value_type(L"."));
  r1 = L"  . ";
  CPPUNIT_ASSERT(value_type(r1) == value_type(L"."));
  r1 = L" . . . ";
  CPPUNIT_ASSERT(value_type(r1) == value_type(L"."));
  r1 = L" .element with . spaces . . and multiple.. .dots..";
  CPPUNIT_ASSERT(value_type(r1) == value_type(L".element with.spaces.and multiple.dots"));
  
  CPPUNIT_ASSERT((L"dir1" + path2) == unicode_path(L"dir1.dir2.dir3"));
  CPPUNIT_ASSERT((value_type(L".dir1") + e1) == unicode_path(L".dir1.element_1"));
  CPPUNIT_ASSERT((r1 / L"dir2") == unicode_path(L".element with.spaces.and multiple.dots.dir2."));
  CPPUNIT_ASSERT((e2 / value_type(L"element_3")) == unicode_path(L"element_2.element_3"));
}

void unicode_path_tests::base_constructor__separator_in_element__exception(void)
{
  unicode_path::base_type bp(true);
  bp /= L"dir1";
  bp /= L"dir2";
  bp /= L"field/";
  unicode_path path1(bp, '/'); ///exception
}

void unicode_path_tests::separator_change__separator_in_element__exception(void)
{
  unicode_path path1(L"/dir.1/dir2/field/", '/');
  path1.separator('.'); ///exception
}


void unicode_path_tests::direct_path_concatenation__exception(void)
{
  unicode_path path1(L"dir1"), path2(L".dir2");
  path1 /= path2; ///exception
}

void unicode_path_tests::direct_path_concatenation_custom_separator__exception(void)
{
  unicode_path path1(L"/dir1", '/'), path2(L"/dir2/", '/');
  path1 /= path2; ///exception
}

#ifdef SINGLE_TEST_MODE

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(unicode_path_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

