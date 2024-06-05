#include "minimax.hpp"

#define inf 2147480000

Move minimax::get_move(State* state, int depth){
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto moves = state->legal_actions;
    Move best_move = moves[0];
    
    if (state->player == 0){
        int max = -inf;
        for (auto mv : moves){
            State* next = state->next_state(mv);
            int val = make_node(next, depth, false);
            if (val > max){
                best_move = mv;
                max = val;
            }
        }
    }
    else{
        int max = inf;
        for (auto mv : moves){
            State* next = state->next_state(mv);
            int val = make_node(next, depth, false);
            if (val < max){
                best_move = mv;
                max = val;
            }
        }
    }
    return best_move;
}

int minimax::make_node(State* state, int depth, bool maximize){
    if (state->game_state == WIN){
        if (state->player == 0) return inf;
        else return -inf;
    }
    if (depth == 0 || state->game_state == DRAW) return state->evaluate();

    if (!state->legal_actions.size()){
        state->get_legal_actions();
    }
    if (!state->legal_actions.size()){
        return state->evaluate();
    }

    if (state->player == 0){
        int max = -inf;
        for (auto move : state->legal_actions){
            State* next = state->next_state(move);
            int val = make_node(next, depth - 1, true);
            max = std::max(max, val);
        }
        return max;
    }
    else{
        int min = inf;
        for (auto move : state->legal_actions){
            State* next = state->next_state(move);
            int val = make_node(next, depth - 1, true);
            min = std::min(min, val);
        }
        return min;
    }
}