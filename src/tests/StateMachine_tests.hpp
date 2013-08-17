#ifndef STATE_MACHINE_TESTS_HPP
#define STATE_MACHINE_TESTS_HPP

#include "StateMachine.hpp"
#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include "StdIteratorAdapter.hpp"

using namespace CppUnit;
using namespace mru;

class StateMachine_tests : public TestCase {
public:
  typedef int TokenType;
  void SetUp(void);

  void state_creation(void);
  void no_start_state(void);
  void null_start_state(void);
  void start_state_from_other_machine(void);

  void no_end_state(void);
  void null_end_state(void);
  void end_state_from_other_machine(void);

  void null_transition(void);
  void same_transition(void);
  void no_iterator(void);

  void empty_iterator(void);
  bool on_start_executed;
  bool on_end_executed;
  void onStart(void);
  void onEnd(void);

  void state_change_signal(void);
  bool on_state_change_executed;
  void onStateChange(void);
  
  void action_on_leave(void);
  bool on_leave_executed;
  void onLeave(const TokenType &current_token);

  void action_on_entry(void);
  bool on_entry_executed;
  void onEntry(const TokenType &current_token);

  void no_transition(void);

  CPPUNIT_TEST_SUITE(StateMachine_tests);
    CPPUNIT_TEST(state_creation);
    CPPUNIT_TEST_EXCEPTION(no_start_state, StateMachineException);
    CPPUNIT_TEST_EXCEPTION(null_start_state, StateMachineException);
    CPPUNIT_TEST_EXCEPTION(start_state_from_other_machine, StateMachineException);

    CPPUNIT_TEST_EXCEPTION(no_end_state, StateMachineException);
    CPPUNIT_TEST_EXCEPTION(null_end_state, StateMachineException);
    CPPUNIT_TEST_EXCEPTION(end_state_from_other_machine, StateMachineException);

    CPPUNIT_TEST_EXCEPTION(null_transition, StateMachineException);
    CPPUNIT_TEST_EXCEPTION(same_transition, StateMachineException);
    CPPUNIT_TEST_EXCEPTION(no_iterator, StateMachineException);
    CPPUNIT_TEST(empty_iterator);
    CPPUNIT_TEST(state_change_signal);
    CPPUNIT_TEST(action_on_leave);
    CPPUNIT_TEST(action_on_entry);
    CPPUNIT_TEST_EXCEPTION(no_transition, StateMachineException);
  CPPUNIT_TEST_SUITE_END();

private:
  std::list<TokenType> tokens;
  typedef ConstStdIteratorAdapter<std::list<TokenType>::const_iterator> ConstListIterator;
  typedef StateMachine<TokenType> MachineType;

  ConstListIterator::Pointer getTokensIterator(void);
};

#endif /* STATE_MACHINE_TESTS_HPP */

