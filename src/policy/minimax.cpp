#include "minimax.hpp"

#define inf 2147483646

Move minimax::get_move(State* state, int depth){
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto moves = state->legal_actions;
    int max = -1 * inf;
    Move best_move = moves[0];
    
    if (state->player == 0){
        int max = -1 * inf;
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
        else return -1 * inf;
    }
    if (depth == 0 || state->game_state == DRAW) return state->evaluate();

    if (!state->legal_actions.size()){
        state->get_legal_actions();
    }
    if (!state->legal_actions.size()){
        return state->evaluate();
    }

    if (state->player == 0){
        int max = -1 * inf;
        for (auto move : state->legal_actions){
            State* next = state->next_state(move);
            max = std::max(max, make_node(next, depth - 1, true));
        }
        return max;
    }
    else{
        int min = inf;
        for (auto move : state->legal_actions){
            State* next = state->next_state(move);
            min = std::min(min, make_node(next, depth - 1, true));
        }
        return min;
    }
}