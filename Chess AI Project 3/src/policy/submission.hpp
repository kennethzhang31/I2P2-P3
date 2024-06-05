#pragma once
#include "../state/state.hpp"
/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class submission {
public:
  static int make_node(State* state, int depth,int alpha, int beta);
  static Move get_move(State* state, int depth);
};
