#include "StateMachine_tests.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "unicode/uchar.h"

void
StateMachine_tests::SetUp(void)
{
  on_start_executed = on_end_executed = on_state_change_executed = false;
  on_leave_executed = on_entry_executed = false;
  tokens.clear();
}

StateMachine_tests::ConstListIterator::Pointer
StateMachine_tests::getTokensIterator(void)
{
  return boost::make_shared<ConstListIterator>(tokens.begin(), tokens.end());
}

/* ------------------------------------------------------------------------- */

void
StateMachine_tests::state_creation(void)
{
  MachineType machine;
  
  MachineType::State* start = machine.createState();

  CPPUNIT_ASSERT(start);
}

void
StateMachine_tests::no_start_state(void)
{
  MachineType machine(getTokensIterator());
  
  machine.start(); //throw
}

void
StateMachine_tests::null_start_state(void)
{
  MachineType machine(getTokensIterator());

  machine.setStartState(NULL); //throw
}

void
StateMachine_tests::start_state_from_other_machine(void)
{
  MachineType machine_A(getTokensIterator());
  MachineType machine_B(getTokensIterator());

  machine_A.setStartState(machine_B.createState()); //throw
}

/* ------------------------------------------------------------------------- */

void
StateMachine_tests::no_end_state(void)
{
  MachineType machine(getTokensIterator());
  machine.setStartState(machine.createState());
  
  machine.start(); //throw
}

void
StateMachine_tests::null_end_state(void)
{
  MachineType machine(getTokensIterator());
  machine.setStartState(machine.createState());

  machine.setEndState(NULL); //throw
}

void
StateMachine_tests::end_state_from_other_machine(void)
{
  MachineType machine_A(getTokensIterator());
  MachineType machine_B(getTokensIterator());

  machine_A.setEndState(machine_B.createState()); //throw
}

/* ------------------------------------------------------------------------- */

void
StateMachine_tests::null_transition(void)
{
  MachineType machine;

  MachineType::State *a_state = machine.createState();
  a_state->addTransition(123, NULL);
}


void
StateMachine_tests::same_transition(void)
{
  MachineType machine;

  MachineType::State *a_state = machine.createState();
  MachineType::State *b_state = machine.createState();
  a_state->addTransition(123, b_state);
  a_state->addTransition(123, a_state); //throw
}

void
StateMachine_tests::no_iterator(void)
{
  MachineType machine;
  machine.setStartState(machine.createState());

  machine.start(); //throw
}

void
StateMachine_tests::empty_iterator(void)
{
  MachineType machine(getTokensIterator());

  MachineType::State *only_state = machine.createState();
  machine.setStartState(only_state);
  machine.setEndState(only_state);

  machine.onStart.connect(sigc::mem_fun(this, &StateMachine_tests::onStart));
  machine.onEnd.connect(sigc::mem_fun(this, &StateMachine_tests::onEnd));
  
  machine.start();

  CPPUNIT_ASSERT(on_start_executed);
  CPPUNIT_ASSERT(on_end_executed);
}

void
StateMachine_tests::onStart(void)
{
  CPPUNIT_ASSERT(!on_end_executed);
  on_start_executed = true;
}

void
StateMachine_tests::onEnd(void)
{
  CPPUNIT_ASSERT(on_start_executed);
  on_end_executed = true;
}

void
StateMachine_tests::state_change_signal(void)
{
  tokens.push_back(123);

  MachineType machine(getTokensIterator());

  MachineType::State *start_state = machine.createState();
  MachineType::State *end_state = machine.createState();
  start_state->addTransition(123, end_state);

  machine.setStartState(start_state);
  machine.setEndState(end_state);

  machine.onStateChange.connect(sigc::mem_fun(this, &StateMachine_tests::onStateChange));
  
  machine.start();

  CPPUNIT_ASSERT(on_state_change_executed);
}

void
StateMachine_tests::onStateChange(void)
{
  on_state_change_executed = true;
}

void
StateMachine_tests::action_on_leave(void)
{
  tokens.push_back(123);

  MachineType machine(getTokensIterator());

  MachineType::State *start_state = machine.createState();
  MachineType::State *end_state = machine.createState();
  start_state->addTransition(123, end_state);

  start_state->onLeave.connect(sigc::mem_fun(this, &StateMachine_tests::onLeave));

  machine.setStartState(start_state);
  machine.setEndState(end_state);
  
  machine.start();

  CPPUNIT_ASSERT(on_leave_executed);
}

void
StateMachine_tests::onLeave(const TokenType &current_token)
{
  CPPUNIT_ASSERT_EQUAL(123, current_token);
  on_leave_executed = true;
}

void
StateMachine_tests::action_on_entry(void)
{
  tokens.push_back(123);

  MachineType machine(getTokensIterator());

  MachineType::State *start_state = machine.createState();
  MachineType::State *end_state = machine.createState();
  start_state->addTransition(123, end_state);

  start_state->onLeave.connect(sigc::mem_fun(this, &StateMachine_tests::onEntry));

  machine.setStartState(start_state);
  machine.setEndState(end_state);
  
  machine.start();

  CPPUNIT_ASSERT(on_entry_executed);
}

void
StateMachine_tests::onEntry(const TokenType &current_token)
{
  CPPUNIT_ASSERT_EQUAL(123, current_token);
  on_entry_executed = true;
}

void
StateMachine_tests::no_transition(void)
{
  tokens.push_back(123);

  MachineType machine(getTokensIterator());

  MachineType::State *start_state = machine.createState();
  MachineType::State *end_state = machine.createState();

  machine.setStartState(start_state);
  machine.setEndState(end_state);
  
  machine.start(); //throw
}

#ifdef SINGLE_TEST_MODE

#include <cppunit/ui/text/TestRunner.h>

int main(int, char *[])
{
  CppUnit::TextUi::TestRunner runner;
  runner.addTest(StateMachine_tests::suite());
  
	return !runner.run();
}

#endif /* SINGLE_TEST_MODE */

