#include "alphabeta.hpp"
#define inf 2147480000


//get best move by comparing return values;
Move alphabeta::get_move(State* state, int depth){
    if (!state->legal_actions.size()) state->get_legal_actions();
    auto moves = state->legal_actions;
    Move best_move = moves[0];
    
    if (state->player == 0){
        int max = -inf;
        for (auto mv : moves){
            State* next = state->next_state(mv);
            int val = make_node(next, depth - 1, -inf, inf);
            if (val > max){
                best_move = mv;
                max = val;
            }
        }
    }
    else{
        int min = inf;
        for (auto mv : moves){
            State* next = state->next_state(mv);
            int val = make_node(next, depth - 1, -inf, inf);
            if (val < min){
                best_move = mv;
                min = val;
            }
        }
    }
    return best_move;
}
//get values from each state;
int alphabeta::make_node(State* state, int depth, int alpha, int beta){
    if (state->game_state == WIN){
        if (state->player == 0) return inf;
        else return -inf;
    }
    if (depth == 0 || state->game_state == DRAW){
        return state->evaluate();
    }
    
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
            int val = make_node(next, depth - 1, alpha, beta);
            max = std::max(max, val);
            alpha = std::max(alpha, max);
            if (beta <= alpha) break;
        }
        return max;
    }
    else{
        int min = inf;
        for (auto move : state->legal_actions){
            State* next = state->next_state(move);
            int val = make_node(next, depth - 1, alpha, beta);
            min = std::min(min, val);
            beta = std::min(beta, min);
            if (beta <= alpha) break;
        }
        return min;
    }
}