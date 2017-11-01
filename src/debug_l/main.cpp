#define DEBUG_L
#include "debug_l.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

//void foo(string _s) {
//  cout << "Foo: " << _s << endl;
//}
//
//ostringstream& soss(bool reset=false) {
//  static ostringstream oss("");
//  if(reset)
//    oss.str("");
//  return oss;
//}
//
//const string SSToStr(const ostream& out) {
//  return dynamic_cast<const ostringstream&>(out).str();
//}

//int main() {
//  foo( (ostringstream("")).str() );
//  //foo( (ostringstream("") << "Test " << 123).str() );
//  
//  foo( (soss(true) << "Test " << 123, soss().str()) );
//  
//  #define ALIAS(STR) foo( (soss(true) << STR, soss().str()) );
//  ALIAS("TEST #" << 2);
//  #define ALIAS2(STR) foo( SSToStr(ostringstream() << STR) );
//  ALIAS("TEST #" << 3);
//  
//  return 0;
//}

int
main(int argc, char const *argv[])
{
  FO("main()");

  MSG("Some text");
  int a = 23;

  VAL(a);
  O(a + 7);

  ERR("Error message");
  WARN("Warning message");

  return 0;
}


