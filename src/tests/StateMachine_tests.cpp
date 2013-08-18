#include "StateMachine_tests.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "unicode/uchar.h"

void
StateMachine_tests::SetUp(void)
{
  on_start_executed = on_end_executed = false;
  on_leave_executed = on_entry_executed = on_repeat_executed = false;
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

  machine.addEndState(NULL); //throw
}

void
StateMachine_tests::end_state_from_other_machine(void)
{
  MachineType machine_A(getTokensIterator());
  MachineType machine_B(getTokensIterator());

  machine_A.addEndState(machine_B.createState()); //throw
}

void
StateMachine_tests::multiple_end_states(void)
{
  tokens.push_back(123);
  tokens.push_back(321);
  tokens.push_back(999);

  MachineType machine;
  MachineType::State *start_state = machine.createState();
  machine.setStartState(start_state);

  MachineType::State *state_123 = machine.createState();
  MachineType::State *state_321 = machine.createState();
  MachineType::State *state_999 = machine.createState();

  start_state->addTransition(123, state_123);
  state_123->addTransition(321, state_321);
  state_321->addTransition(999, state_999);
  machine.addEndState(state_123);
  machine.addEndState(state_321);
  machine.addEndState(state_999);

  machine.setIterator(getTokensIterator());
  machine.start();

  tokens.pop_back();
  machine.setIterator(getTokensIterator());
  machine.start();

  tokens.pop_back();
  machine.setIterator(getTokensIterator());
  machine.start();
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
StateMachine_tests::transition_from_other_machine(void)
{
  MachineType machine_A(getTokensIterator());
  MachineType machine_B(getTokensIterator());

  machine_A.createState()->addTransition(321, machine_B.createState()); //throw
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
  machine.addEndState(only_state);

  only_state->onEntry.connect(sigc::mem_fun(this, &StateMachine_tests::onStartEntry));
  only_state->onLeave.connect(sigc::mem_fun(this, &StateMachine_tests::onEndLeave));
  
  machine.start();

  CPPUNIT_ASSERT(on_start_executed);
  CPPUNIT_ASSERT(on_end_executed);
}

void
StateMachine_tests::onStartEntry(const TokenType &current_token)
{
  CPPUNIT_ASSERT(!on_end_executed);
  on_start_executed = true;
}

void
StateMachine_tests::onEndLeave(const TokenType &current_token)
{
  CPPUNIT_ASSERT(on_start_executed);
  on_end_executed = true;
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
  machine.addEndState(end_state);
  
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
  machine.addEndState(end_state);
  
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
StateMachine_tests::action_on_repetition(void)
{
  tokens.push_back(123);
  tokens.push_back(123);

  MachineType machine(getTokensIterator());

  MachineType::State *start_state = machine.createState();
  MachineType::State *end_state = machine.createState();
  start_state->addTransition(123, end_state);
  end_state->addTransition(123, end_state);

  end_state->onRepeat.connect(sigc::mem_fun(this, &StateMachine_tests::onRepeat));

  machine.setStartState(start_state);
  machine.addEndState(end_state);
  
  machine.start();

  CPPUNIT_ASSERT(on_repeat_executed);
}

void
StateMachine_tests::onRepeat(const TokenType &token)
{
  on_repeat_executed = true;
}

void
StateMachine_tests::no_transition(void)
{
  tokens.push_back(123);

  MachineType machine(getTokensIterator());

  MachineType::State *start_state = machine.createState();
  MachineType::State *end_state = machine.createState();

  machine.setStartState(start_state);
  machine.addEndState(end_state);
  
  machine.start(); //throw
}

struct CustomTokenType {
  int position;
  std::string real_value;
  bool operator<(const CustomTokenType &other) const
  {
    return this->real_value < other.real_value;
  }
};

void
StateMachine_tests::custom_token_type(void)
{
  std::list<CustomTokenType> custom_tokens;

  CustomTokenType a1;
  a1.position = 1;
  a1.real_value = "aaa";
  custom_tokens.push_back(a1);
  
  CustomTokenType a2;
  a2.position = 2;
  a2.real_value = "aaa";
  custom_tokens.push_back(a2);

  CustomTokenType b;
  b.position = 3;
  b.real_value = "BBB";
  custom_tokens.push_back(b);

  StateMachine<CustomTokenType> custom_machine(
      boost::make_shared< ConstStdIteratorAdapter<std::list<CustomTokenType>::const_iterator> >(
        custom_tokens.begin(), custom_tokens.end()
        )
      );

  StateMachine<CustomTokenType>::State *start_state = custom_machine.createState();
  StateMachine<CustomTokenType>::State *a_state = custom_machine.createState();
  StateMachine<CustomTokenType>::State *b_state = custom_machine.createState();

  start_state->addTransition(a1, a_state);
  a_state->addTransition(a1, a_state);
  a_state->addTransition(b, b_state);

  custom_machine.setStartState(start_state);
  custom_machine.addEndState(b_state);
  
  custom_machine.start(); //throw
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

