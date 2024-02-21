#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include "board.hpp"
#include "engine.hpp"
using namespace std;
using namespace chrono;

#define color(p) ((PlayerColor)(p & (WHITE | BLACK)))
#define cw_90_pos(p) cw_90[p]
#define cw_180_pos(p) cw_180[p]
#define acw_90_pos(p) acw_90[p]
#define cw_90_move(m) move_promo(cw_90[getp0(m)], cw_90[getp1(m)], getpromo(m))
#define acw_90_move(m) move_promo(acw_90[getp0(m)], acw_90[getp1(m)], getpromo(m))
#define cw_180_move(p) move_promo(cw_180[getp0(m)], cw_180[getp1(m)], getpromo(m))
std::vector<U16> transform_moves(const std::vector<U16>& moves, const U8 *transform) {

    vector<U16> rot_moves;

    for (U16 move : moves) {
        rot_moves.push_back(move_promo(transform[getp0(move)], transform[getp1(move)], getpromo(move)));
    }

    return rot_moves;
}
U8 cw_90[64] = {
    48, 40, 32, 24, 16, 8,  0,  7,
    49, 41, 33, 25, 17, 9,  1,  15,
    50, 42, 18, 19, 20, 10, 2,  23,
    51, 43, 26, 27, 28, 11, 3,  31,
    52, 44, 34, 35, 36, 12, 4,  39,
    53, 45, 37, 29, 21, 13, 5,  47,
    54, 46, 38, 30, 22, 14, 6,  55,
    56, 57, 58, 59, 60, 61, 62, 63
};

U8 acw_90[64] = {
     6, 14, 22, 30, 38, 46, 54, 7,
     5, 13, 21, 29, 37, 45, 53, 15,
     4, 12, 18, 19, 20, 44, 52, 23,
     3, 11, 26, 27, 28, 43, 51, 31,
     2, 10, 34, 35, 36, 42, 50, 39,
     1,  9, 17, 25, 33, 41, 49, 47,
     0,  8, 16, 24, 32, 40, 48, 55,
    56, 57, 58, 59, 60, 61, 62, 63
};

U8 cw_180[64] = {
    54, 53, 52, 51, 50, 49, 48, 7,
    46, 45, 44, 43, 42, 41, 40, 15,
    38, 37, 18, 19, 20, 33, 32, 23,
    30, 29, 26, 27, 28, 25, 24, 31,
    22, 21, 34, 35, 36, 17, 16, 39,
    14, 13, 12, 11, 10,  9,  8, 47,
     6,  5,  4,  3,  2,  1,  0, 55,
    56, 57, 58, 59, 60, 61, 62, 63
};

U8 id[64] = {
     0,  1,  2,  3,  4,  5,  6,  7,
     8,  9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39,
    40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59, 60, 61, 62, 63
};



class Handle_Weights_White{
    //36+6+36+6+2+1
    private:
        vector <vector<double>> weight_white_attack;
        vector <double> weight_white_dof;
        vector <vector<double>> weight_black_attack;
        vector <double> weight_black_dof;
        vector<double> weight_count;
        vector <double> weight_others;

    public:
    int read_weights_w(){
        vector<double> white_weights={};
        string st="./src/weights_w.txt";
        ifstream file;
        file.open(st);
        if(file.fail()) {cout<<"DISASTER"<<endl; return 0;}
        for (int i=0;i<6;i++){
            std::vector<double> row;
            for(int j=0;j<6;j++){
               double x=0;
               file>>x;
               
               row.push_back(x);
            }
            this->weight_white_attack.push_back(row);
        }
        for (int i=0;i<6;i++){
               double x=0;
               file>>x;
               
               this->weight_white_dof.push_back(x);
        }
        for (int i=0;i<6;i++){
            std::vector<double> row;
            for(int j=0;j<6;j++){
               double x=0;
               file>>x;
               
               row.push_back(x);
            }
            this->weight_black_attack.push_back(row);
        }
        for (int i=0;i<6;i++){
               double x;
               file>>x;
               
               this->weight_black_dof.push_back(x);
        }
        for(int i=0;i<12;i++){
                double x=0;
                file>>x;
                
                this->weight_count.push_back(x);
        }
        for(int i=0;i<3;i++){
                double x=0;
                file>>x;
                
                this->weight_others.push_back(x);
        }
        file.close();
        return 1;
    }

    int read_weights_b(){
        vector<double> white_weights={};
        string st="./src/weights_b.txt";
        ifstream file;
        file.open(st);
        if(file.fail()) {cout<<"DISASTER"<<endl; return 0;}
        for (int i=0;i<6;i++){
            std::vector<double> row;
            for(int j=0;j<6;j++){
               double x=0;
               file>>x;
               
               row.push_back(x);
            }
            this->weight_white_attack.push_back(row);
        }
        for (int i=0;i<6;i++){
               double x=0;
               file>>x;
               
               this->weight_white_dof.push_back(x);
        }
        for (int i=0;i<6;i++){
            std::vector<double> row;
            for(int j=0;j<6;j++){
               double x=0;
               file>>x;
               
               row.push_back(x);
            }
            this->weight_black_attack.push_back(row);
        }
        for (int i=0;i<6;i++){
               double x;
               file>>x;
               
               this->weight_black_dof.push_back(x);
        }
        for(int i=0;i<12;i++){
                double x=0;
                file>>x;
                
                this->weight_count.push_back(x);
        }
        for(int i=0;i<3;i++){
                double x=0;
                file>>x;
                
                this->weight_others.push_back(x);
        }
        file.close();
        return 1;
    }

    void print_weights(){
        cout<<"Printing weights from file"<<endl;
        for (int i=0;i<6;i++){
            for(int j=0;j<6;j++){
               cout<<this->weight_white_attack[i][j]<<" ";
            }
            cout<<endl;
        }
        for (int i=0;i<6;i++){
               cout<<this->weight_white_dof[i]<<" ";
        }
        cout<<endl;
        for (int i=0;i<6;i++){
            for(int j=0;j<6;j++){
             cout<<this->weight_black_attack[i][j]<<" ";
            }
            cout<<endl;
        }
        for (int i=0;i<6;i++){
               cout<<this->weight_black_dof[i]<<" ";
        }
        cout<<endl;
        for (int i=0;i<12;i++){
               cout<<this->weight_count[i]<<" ";
        }
        cout<<endl;
        
        cout<<this->weight_others[0]<<endl;
        cout<<this->weight_others[1]<<endl;
        cout<<this->weight_others[2]<<endl;
    }

    void Update_weights(vector<int> backed_pred, vector<int> this_feature,double lr){
        string st="./src/weights_w.txt";

        ofstream file(st);
        int k=0;
        for (int i=0;i<6;i++){
            for(int j=0;j<6;j++){
               file<<this->weight_white_attack[i][j]+(backed_pred[k]-this_feature[k]*weight_white_attack[i][j])*(this_feature[k])*lr<<" ";
               k++;
            }
            file<<endl;
        }
        for (int i=0;i<6;i++){
               file<<this->weight_white_dof[i]+(backed_pred[k]-this_feature[k]*weight_white_dof[i])*(this_feature[k])*lr<<" ";
               k++;
        }
        file<<endl;
        for (int i=0;i<6;i++){
            for(int j=0;j<6;j++){
               file<<this->weight_black_attack[i][j]+(backed_pred[k]-this_feature[k]*weight_black_attack[i][j])*(this_feature[k])*lr<<" ";
               k++;
            }
            file<<endl;
        }
        for (int i=0;i<6;i++){
               file<<this->weight_black_dof[i]+(backed_pred[k]-this_feature[k]*weight_black_dof[i])*(this_feature[k])*lr<<" ";
               k++;
        }
        file<<endl;
        for (int i=0;i<12;i++){
               file<<this->weight_count[i]+(backed_pred[k]-this_feature[k]*weight_count[i])*(this_feature[k])*lr<<" ";
               k++;
        }
        file<<endl;
        
        file<<this->weight_others[0]+(backed_pred[k]-this_feature[k]*weight_others[0])*(this_feature[k])*lr<<endl;
        k++;
        file<<this->weight_others[1]+(backed_pred[k]-this_feature[k]*weight_others[1])*(this_feature[k])*lr<<endl;
        k++;
        file<<this->weight_others[2]+(backed_pred[k]-this_feature[k]*weight_others[2])*(this_feature[k])*lr<<endl;
        k++;
        file.close();
    }

    vector<vector<double>> access_weight_white_attack(){
        return weight_white_attack;
    }
    vector<double> access_weight_white_dof(){
        return weight_white_dof;
    }
    vector<vector<double>> access_weight_black_attack(){
        return weight_black_attack;
    }
    vector<double> access_weight_black_dof(){
        return weight_black_dof;
    }
    vector<double> access_weight_count(){
        return weight_count;
    }
    vector<double> access_weight_other(){
        return weight_others;
    }


};


U16 alpha_beta(Board* b, Handle_Weights_White wt, string player, unordered_map <unsigned long long int, tuple<int, U16, vector<int>> >& transposition_table, int depth, unordered_map <unsigned long long int, vector<U16>>& move_orders, time_point <high_resolution_clock> start);
vector<int> give_features(Board* b);
bool cutoff(Board* b, int curr_depth, int max_depth);
std::vector<U16> e_bishop_moves(U8 type,U8 p0, U8* board);
std::vector<U16> e_king_moves(U8 type,U8 p0, U8* board);
std::vector<U16> e_pawn_moves(U8 type,U8 p0, U8* board, bool promote);
std::vector<U16> e_rook_moves(U8 type,U8 p0, U8* board);
double evaluation_func_white(Board* b, Handle_Weights_White wt);
tuple<double,U16,vector<int>> min_value(Board* b,int curr_depth,int depth,int alpha ,int beta,Handle_Weights_White& wt, string player, unordered_map <unsigned long long int, tuple<int, U16, vector<int>> >& transposition_table, unordered_map <unsigned long long int,vector<U16>>& move_orders, time_point <high_resolution_clock> start);
tuple<double,U16,vector<int>> max_value(Board* b,int curr_depth,int depth,int alpha ,int beta,Handle_Weights_White& wt, string player,unordered_map <unsigned long long int, tuple<int, U16, vector<int>> >& transposition_table, unordered_map <unsigned long long int,vector<U16>>& move_orders, time_point <high_resolution_clock> start);
vector<int> give_features_main(Board* b);
vector<int> give_predictions_main(Board* b, Handle_Weights_White wt);


std::vector<U16> e_rook_moves(U8 type,U8 p0, U8* board) {

    int left_rook_reflect[7] = {0, 8, 16, 24, 32, 40, 48};
    PlayerColor color = color(board[p0]);
    std::vector<U16> rook_moves;
    bool refl_blocked = false;

    if (p0 < 8 || p0 == 13) {
        if (!(board[p0+pos(0,1)] & color)) rook_moves.push_back(move(p0, (p0+pos(0,1)))); // top
        if (p0 == 1) { // top continued on the edge
            for (int y = 1; y<=6; y++) {
                U8 p1 = pos(1, y);
                if (board[p1]) {
                    if (board[p1] & color) break;         // our piece
                    else rook_moves.push_back(move(p0, p1)); // their piece - capture
                    break;
                }
                else rook_moves.push_back(move(p0, p1));
            }
        }
    
    }
    else {
        if (!(board[p0-pos(0,1)] & color)) rook_moves.push_back(move(p0,(p0-pos(0,1)) )); // bottom
    }

    if (p0 != 6) {
        if (!(board[p0+pos(1,0)] & color)) rook_moves.push_back(move(p0, (p0+pos(1,0)))); // right
    }

    for (int x=getx(p0)-1; x>=0; x--) {
        U8 p1 = pos(x, gety(p0));
        if (board[p1]) {
            refl_blocked = true;
            if (board[p1] & color) break;         // our piece
            else rook_moves.push_back(move(p0, p1)); // their piece - capture
            break;
        }
        else {
            rook_moves.push_back(move(p0, p1));
        }
    }

    if (refl_blocked) return rook_moves;
    
    if (p0 < 8) {
        for (int p1 : left_rook_reflect) {
            if (board[p1]) {
                if (board[p1] & color) break;         // our piece
                else rook_moves.push_back(move(p0, p1)); // their piece - capture
                break;
            }
            else {
                rook_moves.push_back(move(p0, p1));
            }
        }
    }

    return rook_moves;
}

std::vector<U16> e_pawn_moves(U8 type,U8 p0, U8* board, bool promote) {
    
    PlayerColor color = color(board[p0]);
    std::vector<U16> pawn_moves;

    if (!(board[pos(getx(p0)-1,0)] & color)) {
        if (promote) {
            pawn_moves.push_back(move_promo(p0, pos(getx(p0)-1,0), PAWN_ROOK));
            pawn_moves.push_back(move_promo(p0, pos(getx(p0)-1,0), PAWN_BISHOP));
        }
        else {
            pawn_moves.push_back(move(p0, pos(getx(p0)-1,0)));
        }
    }
    if (!(board[pos(getx(p0)-1,1)] & color)) {
        if (promote) {
            pawn_moves.push_back(move_promo(p0, pos(getx(p0)-1,1), PAWN_ROOK));
            pawn_moves.push_back(move_promo(p0, pos(getx(p0)-1,1), PAWN_BISHOP));
        }
        else {
            pawn_moves.push_back(move(p0, pos(getx(p0)-1,1)));
        }
    }
    if (p0 == 10 && !(board[17] & color)) pawn_moves.push_back(move(p0, 17));

    return pawn_moves;
}


std::vector<U16> e_king_moves(U8 type,U8 p0, U8* board) {

    // king can't move into check. See if these squares are under threat from 
    // enemy pieces as well.
    
    PlayerColor color = color(board[p0]);
    std::vector<U16> king_moves;
    if (!(board[pos(getx(p0)-1,0)] & color)) king_moves.push_back(move(p0, pos(getx(p0)-1,0)));
    if (!(board[pos(getx(p0)-1,1)] & color)) king_moves.push_back(move(p0, pos(getx(p0)-1,1)));
    if (p0 == 10 && !(board[pos(getx(p0)-1,2)] & color)) king_moves.push_back(move(p0, pos(getx(p0)-1,2)));
    if (p0 != 6 && !(board[pos(getx(p0)+1,0)] & color)) king_moves.push_back(move(p0, pos(getx(p0)+1,0)));
    if (p0 != 6 && !(board[pos(getx(p0)+1,1)] & color)) king_moves.push_back(move(p0, pos(getx(p0)+1,1)));
    if (p0 >= 12 && !(board[pos(getx(p0)+1,2)] & color)) king_moves.push_back(move(p0, pos(getx(p0)+1,2)));
    if (p0 == 13 && !(board[pos(getx(p0),2)] & color)) king_moves.push_back(move(p0, pos(getx(p0),2)));
    if (!(board[pos(getx(p0),gety(p0)^1)] & color)) king_moves.push_back(move(p0, pos(getx(p0),gety(p0)^1)));

    return king_moves;
}
std::vector<U16> e_bishop_moves(U8 type,U8 p0, U8* board) {

    PlayerColor color = color(board[p0]);
    std::vector<U16> bishop_moves;

    // top right - move back
    if (p0 < 6 || p0 == 13) {
        if (!(board[p0+pos(0,1)+pos(1,0)] & color)) bishop_moves.push_back(move(p0, (p0+pos(0,1)+pos(1,0))));
    }
    // bottom right - move back
    if (p0 > 6) {
        if (!(board[p0-pos(0,1)+pos(1,0)] & color)) bishop_moves.push_back(move(p0, (p0-pos(0,1)+pos(1,0))));
    }

    std::vector<U8> p1s;

    // top left - forward / reflections
    if (p0 == 1) {
        p1s.push_back(pos(0,1));
        p1s.push_back(pos(1,2));
    }
    else if (p0 == 2) {
        p1s.push_back(pos(1,1));
        p1s.push_back(pos(0,2));
        p1s.push_back(pos(1,3));
    }
    else if (p0 == 3) {
        p1s.push_back(pos(2,1));
        p1s.push_back(pos(1,2));
        p1s.push_back(pos(0,3));
        p1s.push_back(pos(1,4));
        p1s.push_back(pos(2,5));
        p1s.push_back(pos(3,6));
    }
    else if (p0 == 4 || p0 == 5) {
        p1s.push_back(p0-pos(2,0));
        p1s.push_back(p0+pos(0,1)-pos(1,0));
    }
    else if (p0 == 6) {
        p1s.push_back(pos(5,1));
    }
    else if (p0 == 10) {
        p1s.push_back(pos(1,0));
        p1s.push_back(pos(0,1));
        p1s.push_back(pos(1,2));
        p1s.push_back(pos(0,3));
        p1s.push_back(pos(1,4));
        p1s.push_back(pos(2,5));
        p1s.push_back(pos(3,6));
    }
    else if (p0 == 11) {
        p1s.push_back(pos(2,0));
        p1s.push_back(pos(1,1));
        p1s.push_back(pos(0,2));
    }
    else if (p0 == 12) {
        p1s.push_back(pos(3,0));
        p1s.push_back(pos(2,1));
        p1s.push_back(pos(1,2));
        p1s.push_back(pos(0,3));
    }
    else if (p0 == 13) {
        p1s.push_back(pos(4,0));
        p1s.push_back(pos(3,1));
    }

    // back 
    if (p0 < 6 || p0 >= 12) {
        p1s.push_back(pos(getx(p0)+1,gety(p0)+1));
    }
    if (p0 > 9) {
        p1s.push_back(pos(getx(p0)+1,gety(p0)-1));
    }

    for (auto p1 : p1s) {
        if (board[p1]) {
            if (board[p1] & color) break;           // our piece
            else bishop_moves.push_back(move(p0, p1)); // their piece - capture
            break;
        }
        else {
            bishop_moves.push_back(move(p0, p1));
        }
    }

    return bishop_moves;
}



vector<int> give_predictions_main(Board* b, Handle_Weights_White wt){
    vector <int> calc_pred;
    Board* c = b;
    std::unordered_set<U8> bottom({ 1, 2, 3, 4, 5, 6, 10, 11, 12, 13 });
    std::unordered_set<U8> left({ 0, 8, 16, 24, 32, 40, 9, 17, 25, 33 });
    std::unordered_set<U8> top({ 48, 49, 50, 51, 52, 53, 41, 42, 43, 44 });
    std::unordered_set<U8> right({ 54, 46, 38, 30, 22, 14, 45, 37, 29, 21 });

    U8* pieces = (U8*) &(c->data);

    //HANDLE WHITE CHECKS
    int check=0;
    if(c->in_check()){
        check=1;
    }


    //HANDLE PROMOTIONS LIKE THIS??
    int w_promo=0;
    // int b_promo=0;
    for(int i=10;i<12;i++){
         U8 piecetype_w = c->data.board_0[pieces[i]];
         if(!((pieces[i] & PAWN_BISHOP) || (pieces[i] & PAWN_ROOK) || (pieces[i] == DEAD))){
                if((getx(pieces[i])==4|| getx(pieces[i])==3 ) && (gety(pieces[i])==5 || gety(pieces[i])==6)){
                    w_promo=1;
                } 
                        
        }
    }
    int b_promo=0;
    // int b_promo=0;
    for(int i=4;i<5;i++){
         U8 piecetype_w = c->data.board_0[pieces[i]];
         if(!((pieces[i] & PAWN_BISHOP) || (pieces[i] & PAWN_ROOK) || (pieces[i] == DEAD))){
                if((getx(pieces[i])==2 || getx(pieces[i])==3) && (gety(pieces[i])==0 || gety(pieces[i])==1)){
                    b_promo=1;
                } 
                        
        }
    
    }
    vector <int> pcount(12,0);
    for(int i=0;i<12;i++)
        if(pieces[i]!=DEAD)
            pcount[i]=1;
    //VECTOR OF NO OF ATTACKING POSSIBILITIES FOR WHITE BETWEEN EACH PAIR
    //DOF OF A WHITE PIECE

    vector <vector<int>> w_attac_i_j(6, vector<int> (6,0));
    vector <int> w_dof(6,0);
    for(int i=6;i<12;i++){
        U8 piecetype_w = c->data.board_0[pieces[i]];
        U8 *board = c->data.board_0;
        U8 *coord_map = id;
        U8 *inv_coord_map = id;
        if      (left.count(pieces[i]))  { board = c->data.board_270;  coord_map = acw_90; inv_coord_map = cw_90;  }
        else if (top.count(pieces[i]))   { board = c->data.board_180; coord_map = cw_180; inv_coord_map = cw_180; }
        else if (right.count(pieces[i])) { board = c->data.board_90; coord_map = cw_90;  inv_coord_map = acw_90; }

        for(int j=0;j<6;j++){
            vector <U16> temp;
            if((piecetype_w & ROOK) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_rook_moves(piecetype_w,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"ROOK DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }

                }
                w_dof[i-6]+=k;
            }
            else if((piecetype_w & BISHOP) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_bishop_moves(piecetype_w,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"BISHOP DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }
                }
                w_dof[i-6]+=k;
            }
            else if((piecetype_w & KING) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_king_moves(piecetype_w,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"KING DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }
                }
                w_dof[i-6]+=k;
            }
            else if((piecetype_w & PAWN) && (pieces[i]!=DEAD)){
                int k=0;
                vector<U16> temp;
                if (((pieces[i] == 51 || pieces[i] == 43) && (piecetype_w & WHITE)) || 
                    ((pieces[i] == 11 || pieces[i] == 3)  && (piecetype_w & BLACK)) ) {
                        temp = transform_moves(e_pawn_moves(piecetype_w,coord_map[pieces[i]],board,true),inv_coord_map);
                    }
                    else {
                        temp = transform_moves(e_pawn_moves(piecetype_w,coord_map[pieces[i]],board,false),inv_coord_map);
                    }
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }
                }
                w_dof[i-6]+=k;
            }
        }
        w_dof[i-6]/=6;
    }
    //VECTOR OF NO OF ATTACKING POSSIBILITIES FOR BLACK BETWEEN EACH PAIR
    vector <vector<int>> b_attac_i_j(6, vector<int> (6,0));
    vector <int> b_dof(6,0);
    for(int i=0;i<6;i++){
        U8 piecetype_b = c->data.board_0[pieces[i]];
        U8 *board = c->data.board_0;
        U8 *coord_map = id;
        U8 *inv_coord_map = id;
        if      (left.count(pieces[i]))  { board = c->data.board_270;  coord_map = acw_90; inv_coord_map = cw_90;  }
        else if (top.count(pieces[i]))   { board = c->data.board_180; coord_map = cw_180; inv_coord_map = cw_180; }
        else if (right.count(pieces[i])) { board = c->data.board_90; coord_map = cw_90;  inv_coord_map = acw_90; }

        for(int j=6;j<12;j++){
            vector <U16> temp;
            if((piecetype_b & ROOK) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_rook_moves(piecetype_b,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"ROOK DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }

                }
                b_dof[i]+=k;
            }
            else if((piecetype_b & BISHOP) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_bishop_moves(piecetype_b,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"BISHOP DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }
                }
                b_dof[i]+=k;
            }
            else if((piecetype_b & KING) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_king_moves(piecetype_b,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"KING DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }
                }
                b_dof[i]+=k;
            }
            else if((piecetype_b & PAWN) && (pieces[i]!=DEAD)){
                int k=0;
                if (((pieces[i] == 51 || pieces[i] == 43) && (piecetype_b & WHITE)) || 
                    ((pieces[i] == 11 || pieces[i] == 3)  && (piecetype_b & BLACK)) ) {
                        temp = transform_moves(e_pawn_moves(piecetype_b,coord_map[pieces[i]],board,true),inv_coord_map);
                    }
                    else {
                        temp = transform_moves(e_pawn_moves(piecetype_b,coord_map[pieces[i]],board,false),inv_coord_map);
                    }
                // cout<<"PAWN DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }
                }
                b_dof[i]+=k;
            }
        }
        b_dof[i]/=6;
    }

    vector <vector<double>> weight_white_attack=wt.access_weight_white_attack();
    vector <double> weight_white_dof=wt.access_weight_white_dof();
    vector <vector<double>> weight_black_attack=wt.access_weight_black_attack();
    vector <double> weight_black_dof=wt.access_weight_black_dof();
    vector <double> weight_count= wt.access_weight_count();
    vector <double> weight_others=wt.access_weight_other();
    //CALC PREDICTIONS
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            calc_pred.push_back(weight_white_attack[i][j]*w_attac_i_j[i][j]);
        }
        // cout<<"      "<<endl;
    }
    for(int i=0;i<6;i++){
            calc_pred.push_back(weight_white_dof[i]*w_dof[i]);
            // cout<<w_dof[i]<<" ";
    }

    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            calc_pred.push_back(weight_black_attack[i][j]*b_attac_i_j[i][j]);
            // cout<<b_attac_i_j[i][j]<<" ";

        }
        // cout<<"    ay   ";

    }
    for(int i=0;i<6;i++){
            calc_pred.push_back(weight_black_dof[i]*b_dof[i]);
            // cout<<b_dof[i]<<" ";
    }

    for(int i=0;i<12;i++){
            calc_pred.push_back(weight_count[i]*pcount[i]);
            // cout<<b_dof[i]<<" ";
    }
    // cout<<endl;
    calc_pred.push_back(weight_others[0]*w_promo);
    calc_pred.push_back(weight_others[1]*b_promo);
    calc_pred.push_back(weight_others[2]*check);

    return calc_pred;
}

vector<int> give_features(Board* b){
    vector <int> calc_features;
    Board* c = b;
    std::unordered_set<U8> bottom({ 1, 2, 3, 4, 5, 6, 10, 11, 12, 13 });
    std::unordered_set<U8> left({ 0, 8, 16, 24, 32, 40, 9, 17, 25, 33 });
    std::unordered_set<U8> top({ 48, 49, 50, 51, 52, 53, 41, 42, 43, 44 });
    std::unordered_set<U8> right({ 54, 46, 38, 30, 22, 14, 45, 37, 29, 21 });

    U8* pieces = (U8*) &(c->data);

    //HANDLE WHITE CHECKS
    int check=0;
    if(c->in_check()){
        check=1;
    }


    //HANDLE PROMOTIONS LIKE THIS??
    int w_promo=0;
    // int b_promo=0;
    for(int i=10;i<12;i++){
         U8 piecetype_w = c->data.board_0[pieces[i]];
         if(!((pieces[i] & PAWN_BISHOP) || (pieces[i] & PAWN_ROOK) || (pieces[i] == DEAD))){
                if((getx(pieces[i])==4|| getx(pieces[i])==3 ) && (gety(pieces[i])==5 || gety(pieces[i])==6)){
                    w_promo=1;
                } 
                        
        }
    }
    int b_promo=0;
    // int b_promo=0;
    for(int i=4;i<5;i++){
         U8 piecetype_w = c->data.board_0[pieces[i]];
         if(!((pieces[i] & PAWN_BISHOP) || (pieces[i] & PAWN_ROOK) || (pieces[i] == DEAD))){
                if((getx(pieces[i])==2 || getx(pieces[i])==3) && (gety(pieces[i])==0 || gety(pieces[i])==1)){
                    b_promo=1;
                } 
                        
        }
    }
    vector <int> pcount(12,0);
    for(int i=0;i<12;i++)
        if(pieces[i]!=DEAD)
            pcount[i]=1; 
    //VECTOR OF NO OF ATTACKING POSSIBILITIES FOR WHITE BETWEEN EACH PAIR
    //DOF OF A WHITE PIECE

    vector <vector<int>> w_attac_i_j(6, vector<int> (6,0));
    vector <int> w_dof(6,0);
    for(int i=6;i<12;i++){
        U8 piecetype_w = c->data.board_0[pieces[i]];
        U8 *board = c->data.board_0;
        U8 *coord_map = id;
        U8 *inv_coord_map = id;
        if      (left.count(pieces[i]))  { board = c->data.board_270;  coord_map = acw_90; inv_coord_map = cw_90;  }
        else if (top.count(pieces[i]))   { board = c->data.board_180; coord_map = cw_180; inv_coord_map = cw_180; }
        else if (right.count(pieces[i])) { board = c->data.board_90; coord_map = cw_90;  inv_coord_map = acw_90; }

        for(int j=0;j<6;j++){
            vector <U16> temp;
            if((piecetype_w & ROOK) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_rook_moves(piecetype_w,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"ROOK DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }

                }
                w_dof[i-6]+=k;
            }
            else if((piecetype_w & BISHOP) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_bishop_moves(piecetype_w,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"BISHOP DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }
                }
                w_dof[i-6]+=k;
            }
            else if((piecetype_w & KING) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_king_moves(piecetype_w,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"KING DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }
                }
                w_dof[i-6]+=k;
            }
            else if((piecetype_w & PAWN) && (pieces[i]!=DEAD)){
                int k=0;
                vector<U16> temp;
                if (((pieces[i] == 51 || pieces[i] == 43) && (piecetype_w & WHITE)) || 
                    ((pieces[i] == 11 || pieces[i] == 3)  && (piecetype_w & BLACK)) ) {
                        temp = transform_moves(e_pawn_moves(piecetype_w,coord_map[pieces[i]],board,true),inv_coord_map);
                    }
                    else {
                        temp = transform_moves(e_pawn_moves(piecetype_w,coord_map[pieces[i]],board,false),inv_coord_map);
                    }
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            w_attac_i_j[i-6][j]+=1;
                        }
                }
                w_dof[i-6]+=k;
            }
        }
        w_dof[i-6]/=6;
    }
    //VECTOR OF NO OF ATTACKING POSSIBILITIES FOR BLACK BETWEEN EACH PAIR
    vector <vector<int>> b_attac_i_j(6, vector<int> (6,0));
    vector <int> b_dof(6,0);
    for(int i=0;i<6;i++){
        U8 piecetype_b = c->data.board_0[pieces[i]];
        U8 *board = c->data.board_0;
        U8 *coord_map = id;
        U8 *inv_coord_map = id;
        if      (left.count(pieces[i]))  { board = c->data.board_270;  coord_map = acw_90; inv_coord_map = cw_90;  }
        else if (top.count(pieces[i]))   { board = c->data.board_180; coord_map = cw_180; inv_coord_map = cw_180; }
        else if (right.count(pieces[i])) { board = c->data.board_90; coord_map = cw_90;  inv_coord_map = acw_90; }

        for(int j=6;j<12;j++){
            vector <U16> temp;
            if((piecetype_b & ROOK) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_rook_moves(piecetype_b,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"ROOK DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }

                }
                b_dof[i]+=k;
            }
            else if((piecetype_b & BISHOP) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_bishop_moves(piecetype_b,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"BISHOP DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }
                }
                b_dof[i]+=k;
            }
            else if((piecetype_b & KING) && (pieces[i]!=DEAD)){
                int k=0;
                vector <U16> temp = transform_moves(e_king_moves(piecetype_b,coord_map[pieces[i]],board),inv_coord_map);
                // cout<<"KING DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }
                }
                b_dof[i]+=k;
            }
            else if((piecetype_b & PAWN) && (pieces[i]!=DEAD)){
                int k=0;
                if (((pieces[i] == 51 || pieces[i] == 43) && (piecetype_b & WHITE)) || 
                    ((pieces[i] == 11 || pieces[i] == 3)  && (piecetype_b & BLACK)) ) {
                        temp = transform_moves(e_pawn_moves(piecetype_b,coord_map[pieces[i]],board,true),inv_coord_map);
                    }
                    else {
                        temp = transform_moves(e_pawn_moves(piecetype_b,coord_map[pieces[i]],board,false),inv_coord_map);
                    }
                // cout<<"PAWN DOF"<<size<<endl;
                for(k=0;k<(int)temp.size();k++){
                        if(getp1(temp[k])==pieces[j]){
                            b_attac_i_j[i][j-6]+=1;
                        }
                }
                b_dof[i]+=k;
            }
        }
        b_dof[i]/=6;
    }

    // cout<<"BLACK TO WHITE ATTACKS AT THIS STAGE"<<endl;
    //CALC FEATURES
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            calc_features.push_back(w_attac_i_j[i][j]);
            // cout<<w_attac_i_j[i][j]<<" ";
        }
        // cout<<"      "<<endl;
    }
    for(int i=0;i<6;i++){
            calc_features.push_back(w_dof[i]);
            // cout<<w_dof[i]<<" ";
    }

    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            calc_features.push_back(b_attac_i_j[i][j]);
            // cout<<b_attac_i_j[i][j]<<" ";

        }
        // cout<<"    ay   ";

    }
    for(int i=0;i<6;i++){
            calc_features.push_back(b_dof[i]);
            // cout<<b_dof[i]<<" ";
    }
    for(int i=0;i<12;i++){
            calc_features.push_back(pcount[i]);
            // cout<<b_dof[i]<<" ";
    }
    // cout<<endl;
    calc_features.push_back(w_promo);
    calc_features.push_back(b_promo);
    calc_features.push_back(check);

    return calc_features;
}




double evaluation_func_white(Board* b,Handle_Weights_White wt){
    Board* c = b;
    vector <int> features;
    features = give_features(c);
    vector <vector<double>> weight_white_attack=wt.access_weight_white_attack();
    vector <double> weight_white_dof=wt.access_weight_white_dof();
    vector <vector<double>> weight_black_attack=wt.access_weight_black_attack();
    vector <double> weight_black_dof=wt.access_weight_black_dof();
    vector <double> weight_count=wt.access_weight_count();
    vector <double> weight_others=wt.access_weight_other();
    double eval=0;
    int k=0;
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            eval+=weight_white_attack[i][j]*features[k];
            k++;
        }
    }
    for(int i=0;i<6;i++){
            eval+=weight_white_dof[i]*features[k];
            k++;
    }

    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            eval+=weight_black_attack[i][j]*features[k];
            k++;
        }
    }
    for(int i=0;i<6;i++){
            eval+=weight_black_dof[i]*features[k];
            k++;
    }
    for(int i=0;i<12;i++){
            eval+=weight_count[i]*features[k];
            k++;
    }
    eval+=weight_others[0]*features[k];
    k++;
    eval+=weight_others[1]*features[k];
    k++;
    eval+=weight_others[2]*features[k];
    k++;

    return eval;

}



unsigned long long int hasher(vector<uint8_t> vec) {
  unsigned long long int seed = vec.size();
  for(auto x : vec) {
    x = ((x >> 4) ^ x) * 0x45d9f3b;
    x = ((x >> 4) ^ x) * 0x45d9f3b;
    x = (x >> 4) ^ x;
    seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  return seed;
}

bool quiescent(Board* b,  string player){
    vector<int> features=give_features(b);
    if(player=="w"){
        int i=0;
        while(((i+216)%6==2)  && (i<36 && i>42 && i<78)){
            if(features[i]>0){
                return false;
            }
            i++;
        }
    }
    else{
        int i=0;
        while(((i+216)%6==2) && (i<36 && i>42 && i<78)){
            if(features[i]>0){
                return false;
            }
            i++;
        }
    }
    return true;
}


U16 alpha_beta(Board* b, Handle_Weights_White wt, string player, unordered_map <unsigned long long int, tuple<int, U16, vector<int>> >& transposition_table, int depth, unordered_map <unsigned long long int, vector<U16>>& move_orders, time_point <high_resolution_clock> start){
    tuple<double, U16, vector<int>> v;
    v = max_value(b,1,depth,INT_MIN,INT_MAX,wt, player,transposition_table, move_orders, start);
    return get<1>(v);
}

bool cutoff(Board* b, int curr_depth, int max_depth,string player){
    // if(!quiescent(b,player)){
    //     cout<<".........................GETS INTO QUISCENT wala code......................................"<<endl;
    // }
    if(quiescent(b, player) && curr_depth >=max_depth){
        return true;
    }
    return false;
}


bool min_cmp(pair<U16, double>& a,
        pair<U16, double>& b)
{
    return a.second < b.second;
}

tuple<double,U16,vector<int>> min_value(Board* state,int curr_depth,int max_depth,int alpha ,int beta,Handle_Weights_White& wt, string player,unordered_map <unsigned long long int, tuple<int, U16, vector<int>> >& transposition_table, unordered_map <unsigned long long int, vector <U16> >& move_orders, time_point <high_resolution_clock> start){
    // cout<<"Enters Min Node"<<endl;
    if(cutoff(state,curr_depth,max_depth,player)){
        // cout<<"Reached and returned from Leaves "<<evaluation_func_white(state,wt)<<endl;
        return make_tuple(evaluation_func_white(state,wt),0,give_predictions_main(state,wt));
    }
    double v = INT64_MAX;
    vector<int> backed_pred;
    if(duration_cast<microseconds>(high_resolution_clock::now()- start).count()>1999990){
            return make_tuple(v,0,backed_pred);
        }

    U8* my_pieces= (U8*) &(state->data);
    vector <U8> my_info; 
    for(int i=0;i<12;i++){
                            my_info.push_back(my_pieces[i]);
                            }
    unsigned long long int my_hash =hasher(my_info);
    vector <U16> moveset;
    if(move_orders.find(my_hash)==move_orders.end()){
        vector <U16> temp(state->get_legal_moves().begin(), state->get_legal_moves().end());
        moveset=temp;
    }
    else{
        moveset=move_orders.at(my_hash);
    }

    if (moveset.size() == 0) {
                    return(make_tuple(evaluation_func_white(state,wt),0,give_predictions_main(state,wt)));
                }

    U16 prev_move=moveset[0];



    unordered_map <U16,double> order;
    for(auto a:moveset){
        order.insert({a,INT64_MAX});
    }


    for(auto a:moveset){
        if(duration_cast<microseconds>(high_resolution_clock::now()- start).count()>1999990){
            return make_tuple(v,0,backed_pred);
        }
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srand((time_t)ts.tv_nsec);
        double prob=(double)rand()/RAND_MAX;
        Board* temp_state=state->copy();
        temp_state->do_move(a);
        // table
        U8* pieces= (U8*) &(temp_state->data);
        vector <U8> info; 
        for(int i=0;i<12;i++){
            info.push_back(pieces[i]);
        }
        unsigned long long int hash =hasher(info);
        tuple <double,U16,vector<int>> backed;
        // if(transposition_table.find(hash)==transposition_table.end())
        //     {
                backed=max_value(temp_state,curr_depth+1,max_depth,alpha,beta,wt,player,transposition_table, move_orders, start);
                if(duration_cast<microseconds>(high_resolution_clock::now()- start).count()>1999990){
                                    return make_tuple(v,0,backed_pred);
                                    }
            //     transposition_table[hash] = backed;
            // }
            // else
            // {   
            //     backed = transposition_table.at(hash);
            // }
        // table end
        double v2 = get<0>(backed);
        order[a]=v2;
        if (v2<v){
            v = v2;
            prev_move = a;
            backed_pred =  get<2>(backed);
            beta = min((double)beta,v);
        }

        if(v<=alpha && prob>0) {
            // cout<<"Retuurn from Min Node"<<endl;
            // cout<<"***************************P*R*U*N*E*D*******************************"<<endl;
                std::vector<std::pair<U16, double>> copy_of_map;
                std::vector<U16> store_to_move_orders;
                for (auto it = order.begin(); it != order.end(); ++it) {
                    copy_of_map.push_back(*it);
                }
                sort(copy_of_map.begin(),copy_of_map.end(),min_cmp);
                for (auto it = copy_of_map.begin(); it != copy_of_map.end(); ++it) {
                    store_to_move_orders.push_back((*it).first);
                }
                move_orders[my_hash]=store_to_move_orders;
                if(player=="w"){
                wt.Update_weights(backed_pred,give_features(state),0.001);
                int k=wt.read_weights_w();}
            return make_tuple(v,prev_move,backed_pred);
            }
    }
    // std::cout<<"Return from Min node: "<<endl;
                std::vector<std::pair<U16, double>> copy_of_map;
                std::vector<U16> store_to_move_orders;
                for (auto it = order.begin(); it != order.end(); ++it) {
                    copy_of_map.push_back(*it);
                }
                sort(copy_of_map.begin(),copy_of_map.end(),min_cmp);
                for (auto it = copy_of_map.begin(); it != copy_of_map.end(); ++it) {
                    store_to_move_orders.push_back((*it).first);
                }
                move_orders[my_hash]=store_to_move_orders;
                if(player=="w"){
                wt.Update_weights(backed_pred,give_features(state),0.001);
                int k=wt.read_weights_w();}
    return make_tuple(v,prev_move,backed_pred);
}


bool max_cmp(pair<U16, double>& a,
        pair<U16, double>& b)
{
    return a.second > b.second;
}

tuple<double,U16,vector<int>> max_value(Board* state,int curr_depth,int max_depth,int alpha ,int beta,Handle_Weights_White& wt, string player, unordered_map <unsigned long long int, tuple<int, U16, vector<int>> >& transposition_table, unordered_map <unsigned long long int, vector <U16> >& move_orders, time_point <high_resolution_clock> start){
    // std::cout<<"Enters Max Node"<<endl;
    if(cutoff(state,curr_depth,max_depth,player)){
        // std::cout<<"Reached and returned from leaves "<<evaluation_func_white(state,wt)<<endl;
        return make_tuple(evaluation_func_white(state,wt),0,give_predictions_main(state,wt));
    }
    double v = INT64_MIN;
    vector<int> backed_pred;
    if(duration_cast<microseconds>(high_resolution_clock::now()- start).count()>1999990){
            return make_tuple(v,0,backed_pred);
        }

    U8* my_pieces= (U8*) &(state->data);
    vector <U8> my_info; 
    for(int i=0;i<12;i++){
                            my_info.push_back(my_pieces[i]);
                            }
    unsigned long long int my_hash =hasher(my_info);
    vector <U16> moveset;
    if(move_orders.find(my_hash)==move_orders.end()){
        vector <U16> temp(state->get_legal_moves().begin(), state->get_legal_moves().end());
        moveset=temp;
    }
    else{
        moveset=move_orders.at(my_hash);
    }


    
    if (moveset.size() == 0) {
                    return(make_tuple(evaluation_func_white(state,wt),0,give_predictions_main(state,wt)));
                }
    U16 prev_move=moveset[0];


    unordered_map <U16,double> order;
    for(auto a:moveset){
        order.insert({a,INT64_MIN});
    }


    for(auto a:moveset){
        if(duration_cast<microseconds>(high_resolution_clock::now()- start).count()>1999990){
            return make_tuple(v,0,backed_pred);
        }
        //prob
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        srand((time_t)ts.tv_nsec);
        double prob=(double)rand()/RAND_MAX;

        Board* temp_state=state->copy();
        temp_state->do_move(a);
        // table
        U8* pieces= (U8*) &(temp_state->data);
        vector <U8> info; 
        for(int i=0;i<12;i++){
            info.push_back(pieces[i]);
        }
        unsigned long long int hash =hasher(info);
        tuple <double,U16,vector<int>> backed;
        // if(transposition_table.find(hash)==transposition_table.end())
        //     {
                backed=min_value(temp_state,curr_depth+1,max_depth,alpha,beta,wt,player, transposition_table, move_orders, start);
                if(duration_cast<microseconds>(high_resolution_clock::now()- start).count()>1999990){
                                return make_tuple(v,0,backed_pred);
                            }
            //     transposition_table[hash] = backed;
            // }
            // else
            // {
            //     backed = transposition_table.at(hash);
            // }
        // table end
        double v2 = get<0>(backed);
        order[a]=v2;
        if (v2>v){
            v = v2;
            prev_move = a;
            backed_pred = get<2>(backed);
            alpha = max((double)alpha,v);
        }
        if(v>=beta && prob>0) {
            // std::cout<<"Return from Max node by "<<endl;
            // cout<<"**************************P*R*U*N*E*D*******************************"<<endl;
                std::vector<std::pair<U16, double>> copy_of_map;
                std::vector<U16> store_to_move_orders;
                for (auto it = order.begin(); it != order.end(); ++it) {
                    copy_of_map.push_back(*it);
                }
                sort(copy_of_map.begin(),copy_of_map.end(),max_cmp);
                for (auto it = copy_of_map.begin(); it != copy_of_map.end(); ++it) {
                    store_to_move_orders.push_back((*it).first);
                }
                move_orders[my_hash]=store_to_move_orders;
                if(player=="w"){
                wt.Update_weights(backed_pred,give_features(state),0.001);
                int k=wt.read_weights_w();}
            return make_tuple(v,prev_move,backed_pred);
            }
    }
    // cout<<"Returns from Max Node"<<endl;
                std::vector<std::pair<U16, double>> copy_of_map;
                std::vector<U16> store_to_move_orders;
                for (auto it = order.begin(); it != order.end(); ++it) {
                    copy_of_map.push_back(*it);
                }
                sort(copy_of_map.begin(),copy_of_map.end(),max_cmp);
                for (auto it = copy_of_map.begin(); it != copy_of_map.end(); ++it) {
                    store_to_move_orders.push_back((*it).first);
                }
                move_orders[my_hash]=store_to_move_orders;
                if(player=="w"){
                wt.Update_weights(backed_pred,give_features(state),0.001);
                int k=wt.read_weights_w();}
    return make_tuple(v,prev_move,backed_pred);
}





int count_pices(Board* B){
    Board* c= B->copy();
    U8* pieces = (U8*) &(c->data);
    int co=0;
    for(int i=0;i<12;i++){
        if(!(pieces[i] == DEAD)){
            co++;
        }
    }
    return co;


}

void Engine::find_best_move(const Board& b) {

        Board* c = b.copy();
        // Board* c2 = b.copy();
        string player="w";
        if(c->data.player_to_play==WHITE) player="w";
        else player="b";
        unordered_map <unsigned long long int, vector<U16>> move_orders;
        if(player=="w"){
                auto moveset = b.get_legal_moves();
                if (moveset.size() == 0) {
                    this->best_move = 0;
                }
                else {
                        cout<<"#####WHITE MOVE#####"<<endl;
                        auto start = high_resolution_clock::now();
                        Handle_Weights_White wt;
                        int k= wt.read_weights_w();
                        U16 best;
                        for(int i=3;i<300;i++){
                                    unordered_map <unsigned long long int, tuple<int, U16, vector<int>> > transposition_table;
                                    best = alpha_beta(c,wt,player,transposition_table,i, move_orders, start);
                                    if(best==0)
                                        break;
                                    this->best_move = best;
                                    cout<<"Depth "<<i;
                                    // cout<<"Size of transposition table: "<<transposition_table.size()<<endl;
                                    cout<<" Time required "<<duration_cast<milliseconds>(high_resolution_clock::now()- start).count()<<endl;
                        }
                        
                        
                        cout<<"moveset in white ";
                        for(auto i:moveset){
                            // Board* c2=c->copy();
                            // c2->do_move(i);
                            cout<<move_to_str(i)<<" ";
                        }
                        cout<<endl;
                        // c2->do_move(best);
                        std::cout <<"Best move found for white: "<<move_to_str(this->best_move)<<"\n";
                }
        }
        else{   
                auto moveset = b.get_legal_moves();
                if (moveset.size() == 0) {
                    this->best_move = 0;
                }
                else {  
                        auto start = high_resolution_clock::now();
                        cout<<"######BLACK MOVE#####"<<endl;
                        Handle_Weights_White wt;
                        int k= wt.read_weights_b();
                        U16 best;
                        for(int i=3;i<300;i++){
                                    unordered_map <unsigned long long int, tuple<int, U16, vector<int>> > transposition_table;
                                    best = alpha_beta(c,wt,player,transposition_table, i, move_orders, start);
                                    if(best==0)
                                        break;
                                    this->best_move = best;
                                    cout<<"Depth "<<i;
                                    // cout<<"Size of transposition table: "<<transposition_table.size()<<endl;
                                    cout<<" Time required "<<duration_cast<milliseconds>(high_resolution_clock::now()- start).count()<<endl;
                        }

                        cout<<"moveset in white ";
                        for(auto i:moveset){
                            // Board* c2=c->copy();
                            // c2->do_move(i);
                            cout<<move_to_str(i)<<" ";
                        }
                        cout<<endl;
                        // Board* c2=c->copy();
                        // c2->do_move(best);
                        std::cout <<"Best move found for Black: "<<move_to_str(this->best_move)<<"\n";
                }

                
    }
        

}

