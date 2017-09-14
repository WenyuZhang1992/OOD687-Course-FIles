/////////////////////////////////////////////////////////////////////////
// Invocations.cpp - demonstrate several ways to invoke a function     //
//                                                                     //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2014           //
/////////////////////////////////////////////////////////////////////////

#include <functional>
#include <string>
#include <sstream>
#include <iostream>

std::string testFunction(size_t lineNumber, const std::string& msg)
{
  std::ostringstream out;
  out << "\n  testFunction invoked from line number " << lineNumber << " - " << msg;
  return out.str();
}

class testClass {
public:
  using F = std::function<std::string(size_t, const std::string&)>;
  std::string mf1(F f, size_t line, const std::string& msg) { return f(line, msg); };
  
  using G = std::function<std::string()>;
  std::string mf2(G g){ return g();  }     // note: no arguments, will use capture
};
/////////////////////////////////////////////////////////////////////////////
// Functor - a class that overloads operator()
//           If X is a functor, then X x; x(arg) ==> x.operator()(arg)

class Functor {
public:
  Functor(size_t lineNumber, const std::string& msg) : ln_(lineNumber), msg_(msg) {}
  std::string operator()() { return testFunction(ln_, msg_); }
private:
  size_t ln_;
  std::string msg_;
};
int main()
{
  std::cout << "\n  Demonstrating several ways to invoke a function";
  std::cout << "\n =================================================\n";

  //----< using direct invocation >----------------------------------------

  std::cout << testFunction(__LINE__, "direct invocation");
  
  //----< using old style function pointer >-------------------------------

  using Fptr = std::string(*)(size_t, const std::string&);
  Fptr fptr = testFunction;
  std::cout << fptr(__LINE__, "via function pointer");

  //----< using functor >--------------------------------------------------

  Functor functor(__LINE__ + 1, "via functor");
  std::cout << functor();

  //----< using std::function from library functional >--------------------

  std::function<std::string(size_t, const std::string&)> f = testFunction;
  std::cout << f(__LINE__, "via std::function<R(A...)>");
  
  //----< using lambda assigned to std::function >-------------------------

  f = [](size_t size, const std::string& msg) { return testFunction(size, msg); };
  std::cout << f(__LINE__, "via lambda");

  //----< using lamda passed to member function of class >-----------------

  testClass tc;
  std::cout << tc.mf1(f, __LINE__, "via function passed to class member function");

  //----< using lamda with variable capture passed to member function >----

  std::string msg = "via lamda closure passed to class member function";
  std::cout << tc.mf2([&]() { return testFunction(__LINE__, msg); });  // note: no argument

  //----< using lamda with variable capture >------------------------------

  int lineNo = __LINE__ + 2;
  std::string mutableMsg = "first message";
  std::cout << [&mutableMsg, lineNo]()->std::string { // capture mutableMsg by reference, lineNo by value
    return mutableMsg = testFunction(lineNo, mutableMsg) + " with some more text";
  }();
  std::cout << mutableMsg;

  //----< using lamda with variable capture >------------------------------

  lineNo = __LINE__ + 2;
  mutableMsg = "second message";
  std::cout << [mutableMsg, lineNo]()->std::string { // capture both arguments by value
    // mutableMsg += " with some more text\n";  // this is an error, mutableMsg treated as const
    return testFunction(lineNo, mutableMsg) + " with some more text";
  }();

  //----< using lamda with variable capture >------------------------------

  lineNo = __LINE__ + 2;
  mutableMsg = "third message";
  std::cout << [=]()->std::string {  // capture all variables in scope by value
    // mutableMsg += " with some more text\n";  // this is an error, mutableMsg treated as const
    return testFunction(lineNo, mutableMsg) + " with some more text";
  }();

  //----< using lamda with variable capture >------------------------------

  lineNo = __LINE__ + 2;
  mutableMsg = "third message";
  std::cout << [&]()->std::string {  // capture all variables in scope by value
    mutableMsg += " with some more text\n";  // this is not an error, mutableMsg treated as mutable
    return testFunction(lineNo, mutableMsg) + " with some more text";
  }();

  //----< using mem_fn to map member function into global function >-------

  msg = "via mem_fun taking lambda with closure";
  auto mf = mem_fn(&testClass::mf2);
  testClass::G h = [&]() { return testFunction(__LINE__ + 1, msg); };
  std::cout << mf(&tc, h);

  std::cout << "\n\n";
}