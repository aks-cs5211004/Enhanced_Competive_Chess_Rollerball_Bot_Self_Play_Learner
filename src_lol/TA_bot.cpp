#include <algorithm>
#include <random>
#include <iostream>
#include <cassert>

#include "board.hpp"
#include "engine.hpp"

int maxD = 0;

double per_piece_advantage(U8 piecetype, U8 piece) {
    if (piecetype & PAWN) {
        return 1.0;
    } else if (piecetype & BISHOP) {
        return 5.0;
    } else if (piecetype & ROOK) {
        return 3.0;
    } else if (piecetype & KING) {
        // This should be infinity. But if this is too high, then ratio of scores becomes 1.
        return 0.000001;
    }
    return -1;
}

double piece_advantage(Board *b) {
    PlayerColor pcolor = b->data.player_to_play;

    U8 *pieces = (U8*)b;
    double player_score = 0.0;
    double opponent_score = 0.0;
    double tmp = 0.0;
    U8 piecetype;
    double white_score = 0;
    double black_score = 0;

    for (int i = 0; i < 6; i++) {
        if (pieces[i] == DEAD) {
            continue;
        }
        piecetype = b->data.board_0[pieces[i]];
        tmp = per_piece_advantage(piecetype, pieces[i]);
        assert(tmp > 0);
        black_score += tmp;
    }

    for (int i = 6; i < 12; i++) {
        if (pieces[i] == DEAD) {
            continue;
        }
        piecetype = b->data.board_0[pieces[i]];
        tmp = per_piece_advantage(piecetype, pieces[i]);
        assert(tmp > 0);
        white_score += tmp;
    }

    if (pcolor == WHITE) {
        player_score = white_score;
        opponent_score = black_score;
    } else {
        player_score = black_score;
        opponent_score = white_score;
    }

    if (b->in_check()) {
        opponent_score += 100.0;
    }

    double score = player_score - opponent_score;
    return score;
}

// utility, x, distance, y, piece.
std::pair<U16, double> minimax_node(Board* b, int depth, std::atomic<bool>& search, int ismax){
    std::pair<U16, double> best_pair = {0xffff, -ismax * 1e9}; // move, utility
    std::pair<int, int> best_coord = {0xffff, -1}; // x, y
    U8 best_piece = 0xff; // piece
    int manhat_dist = 100;

    int kingx, kingy;
    if (b->data.player_to_play == WHITE){
        kingx = getx(b->data.b_king);
        kingy = gety(b->data.b_king);
    }
    else{
        kingx = getx(b->data.w_king);
        kingy = gety(b->data.w_king);
    }
    
    if (!search) return {0xfffe, 0}; // search tracker

    auto moveset = b->get_legal_moves();
    if (!moveset.size()){
        if (b->in_check()) return {0xffff, -ismax * 1e9}; // checkmate
        else return {0xffff, 0}; // stalemate
    }
    if (depth == maxD) return {0xffff, 1.0 * ismax * piece_advantage(b)};
    // if (depth == 0) std::cout << moveset.size() << std::endl;

    for (auto curr : moveset){
        if (!search) return {0xfffe, 0}; // search tracker
        int start = getp0(curr), end = getp1(curr);
        int sx = getx(start), sy = gety(start), ex = getx(end), ey = gety(end);
        if (b->data.player_to_play == BLACK){
            sx = 6 - sx;
            sy = 6 - sy;
            ex = 6 - ex;
            ey = 6 - ey;
        }
        Board *_b = b->copy();
        _b->do_move(curr);
        auto adversary = minimax_node(_b, depth+1, search, -ismax);
        if (adversary.first != 0xfffe){
            if (ismax * adversary.second > ismax * best_pair.second){
                best_pair = {curr, adversary.second};
                best_coord = {ex, ey};
                best_piece = (b->data.board_0[start] & 0x1f);
                manhat_dist = abs(ex - kingx) + abs(ey - kingy);
            }
            else if(abs(ismax * adversary.second - ismax * best_pair.second) < 1e-5){ // minimise the manhattan dist from the opponent king for game progression.
                if (abs(3-ex) > abs(3 - best_coord.first)){
                    best_pair = {curr, adversary.second};
                    best_coord = {ex, ey};
                    best_piece = (b->data.board_0[start] & 0x1f);
                    manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                }
                else if(abs(3-ex) == abs(3 - best_coord.first)){
                    if(abs(ex - kingx) + abs(ey - kingy) < manhat_dist){
                        best_pair = {curr, adversary.second};
                        best_coord = {ex, ey};
                        best_piece = (b->data.board_0[start] & 0x1f);
                        manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                    }
                    else if (abs(ex - kingx) + abs(ey - kingy) == manhat_dist){
                        if (ey > best_coord.second){
                            best_pair = {curr, adversary.second};
                            best_coord = {ex, ey};
                            best_piece = (b->data.board_0[start] & 0x1f);
                            manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                        }
                        else if(ey == best_coord.second){
                            if ((b->data.board_0[start] & 0x1f) < best_piece){
                                best_pair = {curr, adversary.second};
                                best_coord = {ex, ey};
                                best_piece = (b->data.board_0[start] & 0x1f);
                                manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                            }
                        }
                    }
                }
            }
        }
        // if (depth == 0) std::cout << curr << " " << best_pair.first << " " << adversary.second << " " << best_pair.second << " " << (b->data.board_0[start] & 0x1f) << " " << best_piece << std::endl;
    }
    return best_pair;
}   
void Engine::find_best_move(const Board& b) {

    maxD = 0;
    Board *_b = b.copy();
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        this->best_move = 0;
    }
    else {
        while(search){
            maxD += 1;
            // maxD = 2;
            auto best_pair = minimax_node(_b, 0, search, 1);
            if (best_pair.first != 0xfffe and best_pair.first != 0xffff) this->best_move = best_pair.first;
            std::cout << this->best_move << " " << maxD << std::endl;
        }
    }
}














































#include <algorithm>
#include <random>
#include <iostream>
#include <cassert>

#include "board.hpp"
#include "engine.hpp"

int maxD = 0;

double per_piece_advantage(U8 piecetype, U8 piece) {
    if (piecetype & PAWN) {
        return 1.0;
    } else if (piecetype & BISHOP) {
        return 5.0;
    } else if (piecetype & ROOK) {
        return 3.0;
    } else if (piecetype & KING) {
        // This should be infinity. But if this is too high, then ratio of scores becomes 1.
        return 0.000001;
    }
    return -1;
}

double piece_advantage(Board *b) {
    PlayerColor pcolor = b->data.player_to_play;

    U8 *pieces = (U8*)b;
    double player_score = 0.0;
    double opponent_score = 0.0;
    double tmp = 0.0;
    U8 piecetype;
    double white_score = 0;
    double black_score = 0;

    for (int i = 0; i < 6; i++) {
        if (pieces[i] == DEAD) {
            continue;
        }
        piecetype = b->data.board_0[pieces[i]];
        tmp = per_piece_advantage(piecetype, pieces[i]);
        assert(tmp > 0);
        black_score += tmp;
    }

    for (int i = 6; i < 12; i++) {
        if (pieces[i] == DEAD) {
            continue;
        }
        piecetype = b->data.board_0[pieces[i]];
        tmp = per_piece_advantage(piecetype, pieces[i]);
        assert(tmp > 0);
        white_score += tmp;
    }

    if (pcolor == WHITE) {
        player_score = white_score;
        opponent_score = black_score;
    } else {
        player_score = black_score;
        opponent_score = white_score;
    }

    if (b->in_check()) {
        opponent_score += 100.0;
    }

    double score = -opponent_score;
    return score;
}

std::pair<U16, double> minimax_node(Board* b, int depth, std::atomic<bool>& search, int ismax){
    std::pair<U16, double> best_pair = {0xffff, -ismax * 1e9}; // move, utility
    std::pair<int, int> best_coord = {0xffff, -1}; // x, y
    U8 best_piece = 0xff; // piece
    int manhat_dist = 100;

    int kingx, kingy;
    if (b->data.player_to_play == WHITE){
        kingx = getx(b->data.b_king);
        kingy = gety(b->data.b_king);
    }
    else{
        kingx = getx(b->data.w_king);
        kingy = gety(b->data.w_king);
    }
    
    if (!search) return {0xfffe, 0}; // search tracker

    auto moveset = b->get_legal_moves();
    if (!moveset.size()){
        if (b->in_check()) return {0xffff, -ismax * 1e9}; // checkmate
        else return {-1, 0}; // stalemate
    }
    if (depth == maxD) return {0xffff, 1.0 * ismax * piece_advantage(b)};

    for (auto curr : moveset){
        if (!search) return {0xfffe, 0}; // search tracker
        int start = getp0(curr), end = getp1(curr);
        int sx = getx(start), sy = gety(start), ex = getx(end), ey = gety(end);
        if (b->data.player_to_play == BLACK){
            sx = 6 - sx;
            sy = 6 - sy;
            ex = 6 - ex;
            ey = 6 - ey;
        }
        Board *_b = b->copy();
        _b->do_move(curr);
        auto adversary = minimax_node(_b, depth+1, search, -ismax);
        if (adversary.first != 0xfffe){
            if (ismax * adversary.second > ismax * best_pair.second){
                best_pair = {curr, adversary.second};
                best_coord = {ex, ey};
                best_piece = (b->data.board_0[start] & 0x1f);
                manhat_dist = abs(ex - kingx) + abs(ey - kingy);
            }
            else if(abs(ismax * adversary.second - ismax * best_pair.second) < 1e-5){ // minimise the manhattan dist from the opponent king for game progression.
                if (abs(3-ex) > abs(3 - best_coord.first)){
                    best_pair = {curr, adversary.second};
                    best_coord = {ex, ey};
                    best_piece = (b->data.board_0[start] & 0x1f);
                    manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                }
                else if(abs(3-ex) == abs(3 - best_coord.first)){
                    if(abs(ex - kingx) + abs(ey - kingy) < manhat_dist){
                        best_pair = {curr, adversary.second};
                        best_coord = {ex, ey};
                        best_piece = (b->data.board_0[start] & 0x1f);
                        manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                    }
                    else if (abs(ex - kingx) + abs(ey - kingy) == manhat_dist){
                        if (ey > best_coord.second){
                            best_pair = {curr, adversary.second};
                            best_coord = {ex, ey};
                            best_piece = (b->data.board_0[start] & 0x1f);
                            manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                        }
                        else if(ey == best_coord.second){
                            if ((b->data.board_0[start] & 0x1f) < best_piece){
                                best_pair = {curr, adversary.second};
                                best_coord = {ex, ey};
                                best_piece = (b->data.board_0[start] & 0x1f);
                                manhat_dist = abs(ex - kingx) + abs(ey - kingy);
                            }
                        }
                    }
                }
            }
        }
        // if (depth == 0) std::cout << curr << " " << best_pair.first << " " << adversary.second << " " << best_pair.second << " " << (b->data.board_0[start] & 0x1f) << " " << best_piece << std::endl;
    }
    return best_pair;
}   

void Engine::find_best_move(const Board& b) {

    maxD = 0;
    Board *_b = b.copy();
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        this->best_move = 0;
    }
    else {
        while(search){
            maxD += 1;
            // maxD = 2;
            auto best_pair = minimax_node(_b, 0, search, 1);
            if (best_pair.first != 0xfffe and best_pair.first != 0xffff) this->best_move = best_pair.first;
            std::cout << this->best_move << " " << maxD << std::endl;
        }
    }
}




