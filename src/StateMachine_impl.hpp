#ifndef STATE_MACHINE_IMPL_HPP
#error "This is implementation file. Use StateMachine.hpp instead"
#else

#include <boost/make_shared.hpp>

namespace mru
{

template<typename TokenType, typename Predicate>
void
StateMachine<TokenType, Predicate>::State::addTransition(const TokenType &token, State *target)
{
  if (target == NULL)
    throw StateMachineException("Cannot define transition to NULL target");
  if (transitions.count(token) > 0)
    throw StateMachineException("Transition to specified token already exists");
  transitions.insert(std::make_pair(token, target));
}

template<typename TokenType, typename Predicate>
StateMachine<TokenType, Predicate>::StateMachine(void)
  : start_state(NULL)
{ }

template<typename TokenType, typename Predicate>
StateMachine<TokenType, Predicate>::StateMachine(typename ConstIterator<TokenType>::Pointer token_iterator)
  : start_state(NULL), token_iterator(token_iterator)
{

}

template<typename TokenType, typename Predicate>
StateMachine<TokenType, Predicate>::~StateMachine(void)
{ }

template<typename TokenType, typename Predicate>
void
StateMachine<TokenType, Predicate>::setIterator(typename ConstIterator<TokenType>::Pointer token_iterator)
{
  this->token_iterator = token_iterator;
}

template<typename TokenType, typename Predicate>
typename ConstIterator<TokenType>::Pointer
StateMachine<TokenType, Predicate>::getIterator(void)
{
  return token_iterator;
}

template<typename TokenType, typename Predicate>
void
StateMachine<TokenType, Predicate>::start(void)
{
  if (!token_iterator)
    throw StateMachineException("No token iterator provided");
  if (start_state == NULL)
    throw StateMachineException("No start state specified");
  if (final_states.size() < 1)
    throw StateMachineException("No final states specified");

  State *current_state = start_state;

  current_state->onEntry(TokenType());

  while(!token_iterator->atEnd()) {
    //MSG("-------------");
    //VAL(token_iterator->getCurrent().value);
    if (current_state->transitions.count(token_iterator->getCurrent()) == 0)
      throw StateMachineException("No transition found");

    State *next_state = current_state->transitions[token_iterator->getCurrent()];
    if (next_state == current_state)
      current_state->onRepeat(token_iterator->getCurrent());
    else {
      current_state->onLeave(token_iterator->getCurrent());
      current_state = next_state;
      current_state->onEntry(token_iterator->getCurrent());
    }

    token_iterator->next();
  }

  if (final_states.count(current_state) != 1)
    throw StateMachineException("Token stream exhausted but current state is not final");

  current_state->onLeave(TokenType());
}

template<typename TokenType, typename Predicate>
typename StateMachine<TokenType, Predicate>::State *
StateMachine<TokenType, Predicate>::createState(void)
{
  boost::shared_ptr<State> new_state = boost::make_shared<State>();
  states.push_back(new_state);
  return new_state.get();
}

template<typename TokenType, typename Predicate>
void
StateMachine<TokenType, Predicate>::setStartState(const State *start_state)
{
  typename State::Pointer start_state_pointer = getOwnState(start_state);

  if (!start_state_pointer)
    throw StateMachineException("Start state not created by current state machine");

  this->start_state = start_state_pointer.get();
}

template<typename TokenType, typename Predicate>
void
StateMachine<TokenType, Predicate>::addEndState(const State *end_state)
{
  typename State::Pointer end_state_pointer = getOwnState(end_state);

  if (!end_state_pointer)
    throw StateMachineException("End state not created by current state machine");

  final_states.insert(end_state_pointer.get());
}

template<typename TokenType, typename Predicate>
typename StateMachine<TokenType, Predicate>::State::Pointer
StateMachine<TokenType, Predicate>::getOwnState(const State *state)
{
  if (state == NULL)
    throw StateMachineException("State may not be NULL");

  typename std::vector<typename State::Pointer>::iterator found_state = states.begin();
  while (found_state != states.end() && found_state->get() != state)
    ++found_state;
  if (found_state == states.end())
    return typename State::Pointer();
  return *found_state;
}

} /* namespace mru */

#endif

