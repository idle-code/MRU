#include "glue_tests.hpp"
#include <debug_l.h>

#define TEST_TEXT "C:/foo/bar//some_other_directory/Spam.txt.xml"

void
glue_tests::wxString_and_filepath(void)
{
  FO("glue_tests::wxString_and_filepath(void)");
  wxString wstr;
  FilePath fp;

  wstr = wxT(TEST_TEXT);
  fp = glue_cast<FilePath>(wstr);
  CPPUNIT_ASSERT(fp == TEST_TEXT);

  wstr = glue_cast<wxString>(fp);
  CPPUNIT_ASSERT(wstr == wxT(TEST_TEXT));
}

void
glue_tests::UnicodeString_and_filepath(void)
{
  FO("glue_tests::UnicodeString_and_filepath(void)");
  UnicodeString ustr;
  FilePath fp;

  ustr = UNICODE_STRING_SIMPLE(TEST_TEXT);
  VAL(glue_cast<std::string>(ustr));

  fp = glue_cast<FilePath>(ustr);
  VAL(glue_cast<std::string>(fp));
  CPPUNIT_ASSERT(fp == TEST_TEXT);

  VAL(glue_cast<std::string>(glue_cast<UnicodeString>(fp.generic_wstring())));
  VAL(glue_cast<std::string>(glue_cast<UnicodeString>(fp.generic_string())));

  ustr = glue_cast<UnicodeString>(fp);
  VAL(glue_cast<std::string>(ustr));
  CPPUNIT_ASSERT(ustr == UNICODE_STRING_SIMPLE(TEST_TEXT));
}

void
glue_tests::UnicodeString_and_wstring(void)
{
  FO("glue_tests::UnicodeString_and_wstring(void)");

  UnicodeString us_text = UNICODE_STRING_SIMPLE(TEST_TEXT);
  VAL(glue_cast<std::string>(us_text));
  
  std::wstring ws_text = glue_cast<std::wstring>(us_text);
  VAL(glue_cast<std::string>(ws_text));

  us_text = glue_cast<UnicodeString>(ws_text);
  VAL(glue_cast<std::string>(us_text));
  CPPUNIT_ASSERT(us_text == UNICODE_STRING_SIMPLE(TEST_TEXT));
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(glue_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

