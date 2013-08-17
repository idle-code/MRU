#ifndef STATE_MACHINE_IMPL_HPP
#error "This is implementation file. Use StateMachine.hpp instead"
#else

#include <boost/make_shared.hpp>

namespace mru
{

template<typename TokenType>
void
StateMachine<TokenType>::State::addTransition(const TokenType &token, State *target)
{
  if (target == NULL)
    throw StateMachineException("Cannot define transition to NULL target");
  if (transitions.count(token) > 0)
    throw StateMachineException("Transition to specified token already exists");
  transitions.insert(std::make_pair(token, target));
}

template<typename TokenType>
StateMachine<TokenType>::StateMachine(void)
  : start_state(NULL), end_state(NULL)
{ }

template<typename TokenType>
StateMachine<TokenType>::StateMachine(typename ConstIterator<TokenType>::Pointer token_iterator)
  : start_state(NULL), end_state(NULL), token_iterator(token_iterator)
{

}

template<typename TokenType>
StateMachine<TokenType>::~StateMachine(void)
{ }


template<typename TokenType>
void
StateMachine<TokenType>::start(void)
{
  if (!token_iterator)
    throw StateMachineException("No token iterator provided");
  if (start_state == NULL)
    throw StateMachineException("No start state specified");
  if (end_state == NULL)
    throw StateMachineException("No end state specified");

  onStart();

  State *current_state = start_state;
  
  while(!token_iterator->atEnd()) {

    if (current_state->transitions.count(token_iterator->getCurrent()) == 0)
      throw StateMachineException("No transition found");

    current_state->onLeave(token_iterator->getCurrent());
    current_state = current_state->transitions[token_iterator->getCurrent()];
    current_state->onEntry(token_iterator->getCurrent());

    onStateChange();

    token_iterator->next();
  }

  if (current_state != end_state)
    throw StateMachineException("Token stream exhausted but current state is not final");

  onEnd();
}

template<typename TokenType>
typename StateMachine<TokenType>::State *
StateMachine<TokenType>::createState(void)
{
  boost::shared_ptr<State> new_state = boost::make_shared<State>();
  states.push_back(new_state);
  return new_state.get();
}

template<typename TokenType>
void
StateMachine<TokenType>::setStartState(const State *start_state)
{
  typename State::Pointer start_state_pointer = getOwnState(start_state);

  if (!start_state_pointer)
    throw StateMachineException("Start state not created by current state machine");

  this->start_state = start_state_pointer.get();
}

template<typename TokenType>
void
StateMachine<TokenType>::setEndState(const State *end_state)
{
  typename State::Pointer end_state_pointer = getOwnState(end_state);

  if (!end_state_pointer)
    throw StateMachineException("End state not created by current state machine");

  this->end_state = end_state_pointer.get();
}

template<typename TokenType>
typename StateMachine<TokenType>::State::Pointer
StateMachine<TokenType>::getOwnState(const State *state)
{
  if (state == NULL)
    throw StateMachineException("State may not be NULL");

  typename std::list<typename State::Pointer>::iterator found_state = states.begin();
  while (found_state != states.end() && found_state->get() != state)
    ++found_state;
  if (found_state == states.end())
    return typename State::Pointer();
  return *found_state;
}

} /* namespace mru */

#endif

