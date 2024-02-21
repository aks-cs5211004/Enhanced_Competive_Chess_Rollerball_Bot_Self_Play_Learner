#include <algorithm>
#include <random>
#include <iostream>
#include <thread>
#include <random>
#include <time.h>
#include <chrono>
#include <iostream>
#include <bits/stdc++.h>
#include "board.hpp"
#include "engine.hpp"
#include "butils.hpp"
using namespace std;
using namespace chrono;
#define pos(x,y) (((y)<<3)|(x))
#include <unistd.h>

class WEIGHTS{
    public:
    int feature_size;
    int no_of_players;
    int size_of_board;
    vector<double> weights;
    vector<double> weights_static;
    vector<double> weights_backed_dynmaic;
    // Use 1 for using static wt
    int read_weights(int btype, string type){
        string st;
        if(btype==3){
            feature_size=2*10+4*10+2*5*8*8;
            no_of_players=10;
            size_of_board=8;
            st="./src/wt3"+type+".txt";
        }
        else if(btype==2){
            feature_size=2*8+4*8+2*4*8*8;
            no_of_players=8;
            size_of_board=8;
            st="./src/wt2"+type+".txt";
        }
        else{
            feature_size=2*6+4*6+2*4*7*7;
            no_of_players=6;
            size_of_board=7;
            st="./src/wt1"+type+".txt";
        }
        ifstream file;
        file.open(st);
        for (int i=0;i<feature_size;i++){
               double x=0;
               file>>x;
               if(type=="1")
                    this->weights_static.push_back(x);
               else{
                    this->weights.push_back(x);
               }
        }
        weights_backed_dynmaic=weights;
        if(weights.size()!=feature_size){
            cout<<"Expected Feature size and Read size mismatch (!)"<<endl;
        }
        return 1;
    }

    
    void write_weights(int btype){
        string st="./src/wt"+to_string(btype)+"0.txt";
        ofstream file(st);
        int k=0;
        //threat to adversary
        for(int i=0;i<no_of_players;i++){
            file<<weights_backed_dynmaic[k]<<" ";
            k++;
        }
        file<<endl;
        // threat_to_player 
        for(int i=0;i<no_of_players;i++){
            file<<weights_backed_dynmaic[k]<<" ";
            k++;
        }
        file<<endl;
        // player_DOF
        for(int i=0;i<no_of_players;i++){
            file<<weights_backed_dynmaic[k]<<" ";
            k++;
        }
        file<<endl;
        // Adversary_DOF
        for(int i=0;i<no_of_players;i++){
                file<<weights_backed_dynmaic[k]<<" ";
                k++;
        }
        file<<endl;
        // player_count
        for(int i=0;i<no_of_players;i++){
                file<<weights_backed_dynmaic[k]<<" ";
                k++;
        }
        file<<endl;
        // adversary_count
        for(int i=0;i<no_of_players;i++){
                file<<weights_backed_dynmaic[k]<<" ";
                k++;
        }
        file<<endl;
        // ROOKS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
        // KING
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
        // BISHOP
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
        // KNIGHTS
        if(btype==3){
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
        }
        // PAWNS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
        // ADV ROOKS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
        // ADV KING
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
        // ADV  BISHOP
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
        // ADV KNIGHTS
        if(btype==3){
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
        }
        // ADV PAWNS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
            }
            file<<endl;
        }
    }



    double sigmoid(double x){
    return (1/(1+exp(-x)));
    }


    void update_weights(double  backed_eval, double this_eval ,vector<int> this_feature, double lr){
        if(this_feature.size()!=feature_size){
            cout<<"Check the Feature size part (!)"<<endl;
        }
        for(int i=0;i<this_feature.size();i++){
            double prev_wt=weights_backed_dynmaic[i];
            weights_backed_dynmaic[i]= weights_backed_dynmaic[i] + lr*(backed_eval-this_eval)*(this_eval*(1-this_eval))*this_feature[i];
        }
    }

void handy_print_features(vector<int> features, int btype){
    int k=0;
        //threat to adversary
        for(int i=0;i<no_of_players;i++){
            cout<<features[k]<<" ";
            k++;
        }
        cout<<endl;
        // threat_to_player 
        for(int i=0;i<no_of_players;i++){
            cout<<features[k]<<" ";
            k++;
        }
        cout<<endl;
        // player_DOF
        for(int i=0;i<no_of_players;i++){
            cout<<features[k]<<" ";
            k++;
        }
        cout<<endl;
        // Adversary_DOF
        for(int i=0;i<no_of_players;i++){
                cout<<features[k]<<" ";
                k++;
        }
        cout<<endl;
        // player_count
        for(int i=0;i<no_of_players;i++){
                cout<<features[k]<<" ";
                k++;
        }
        cout<<endl;
        // adversary_count
        for(int i=0;i<no_of_players;i++){
                cout<<features[k]<<" ";
                k++;
        }
        cout<<endl;
        // ROOKS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }
        // KING
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }
        // BISHOP
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }
        // KNIGHTS
        if(btype==3){
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
            }
        }
        // PAWNS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }
        // ADV  ROOKS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }
        // ADV KING
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }
        // ADV BISHOP
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }
        // ADV KNIGHTS
        if(btype==3){
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
            }
        }
        // ADV PAWNS
        for(int i=0;i<size_of_board;i++){
            for(int j=0;j<size_of_board;j++){
                    cout<<features[k]<<" ";
                    k++;
            }
            cout<<endl;
        }

}


};

double sigmoid(double x){
    return (1/(1+exp(-x)));
}


int create_pos(int j, int i, int color, int board_size){
    if(color==1){
        return pos(board_size-1-j,board_size-1-i);
    }
    else{
        return pos(j,i);
    }
}
vector<int> get_features(Board state,WEIGHTS* weight_ob){
    vector <int> features(weight_ob->feature_size,0);
    int k=0;
    int color=0, adv_color=0;
    if(state.data.player_to_play==WHITE) {adv_color=1;color=0;}
    else {color=1;adv_color=0;}
    U8* peice_pos=(U8*) &(state.data);

    vector <int> peices_under_consideration;
    if(state.data.board_type==1){
        peices_under_consideration={0,1,2,3,6,7};
    }
    else if(state.data.board_type==2){
        peices_under_consideration={0,1,2,3,6,7,8,9};
    }
    else{
        peices_under_consideration={0,1,2,3,4,5,6,7,8,9};
    }

    // threat_to_adversary
    state.flip_player_();
    for(int i:peices_under_consideration){
        if(state.under_threat(peice_pos[i+adv_color*10]) && peice_pos[i+adv_color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    state.flip_player_();
    // threat_to_player 
    for(int i:peices_under_consideration){
        if(state.under_threat(peice_pos[i+color*10]) && peice_pos[i+color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // player_DOF
    for(int i:peices_under_consideration){
        if(peice_pos[i+color*10]!=DEAD)
            features[k]=state.get_pseudolegal_moves_for_piece(peice_pos[i+color*10]).size();
        k++;
    }
    // Adversary_DOF
    for(int i:peices_under_consideration){
        if(peice_pos[i+adv_color*10]!=DEAD)
            features[k]=state.get_pseudolegal_moves_for_piece(peice_pos[i+adv_color*10]).size();
        k++;
    }
    // player_count
    for(int i:peices_under_consideration){
        if(peice_pos[i+color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // adversary_count
    for(int i:peices_under_consideration){
        if(peice_pos[i+adv_color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // ROOKS
    
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[0+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[1+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // KING
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[2+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // BISHOP
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[3+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // KNIGHTS   in case of board 3 ONLY
    if(state.data.board_type==3){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[4+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[5+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
                k++;
            }
        }
    }
    // PAWNS
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[6+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }


    // ADV ROOKS
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[0+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[1+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // ADV KING
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[2+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // ADV BISHOP
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[3+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }
    // ADV KNIGHTS   in case of board 3 ONLY
    if(state.data.board_type==3){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[4+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[5+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
                k++;
            }
        }
    }
    // ADV PAWNS
    for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[6+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
    }

    return features;

}

double evaluation(Board state,WEIGHTS* weight_ob){
    vector<int> features= get_features(state,weight_ob);
    double eval=0;
    for(int fs=0;fs<features.size();fs++){
        if(state.data.player_to_play==BLACK){
            eval=eval+weight_ob->weights_static[fs]*features[fs];
        }
        else{
            eval=eval+weight_ob->weights[fs]*features[fs];
        }
    }
    return eval;

}



// Defining MCTS Node
struct MCTSNode {
    Board board;
    PlayerColor player;
    WEIGHTS* weight_ob;
    //Constructor
    MCTSNode(Board st, PlayerColor player, WEIGHTS* ob) : board(st), player(player), weight_ob(ob) {}
};

//Minimax Function

pair<U16, double> minimax(MCTSNode* node, int curr_depth ,int max_depth, WEIGHTS* weight_ob){
    if(curr_depth>max_depth){
        if(node->board.data.player_to_play==node->player)
            return {sigmoid(evaluation(node->board, weight_ob)),0};
        else
            return {1-sigmoid(evaluation(node->board, weight_ob)),0};
    }
    double v=INT64_MIN;
    U16 m=0;
    for(auto move: node->board.get_legal_moves()){
            double prev_v=v;
            Board copy = Board((node->board));
            copy.do_move_(move);
            MCTSNode* childnode = new MCTSNode(copy,node->player, node->weight_ob);
            v=std::max(v,minimax(childnode,curr_depth+1,max_depth, weight_ob).second);
            if(v!=prev_v){
                m=move;
            }
    }
    double lr=0.0000000001*curr_depth*curr_depth*curr_depth;
    if(node->player==WHITE)
            if(node->board.data.player_to_play==WHITE){
                node->weight_ob->update_weights(v,sigmoid(evaluation(node->board,node->weight_ob)), get_features(node->board,node->weight_ob), lr);
            }
    return {m,v};
}





void Engine::find_best_move(const Board& b) {
    auto player=b.data.player_to_play;
    // If WHITE WTS are to be updated, use 0 as DYNAMIC PLAYER; 1 as STATIC pLAYER
    WEIGHTS weight_ob;
    weight_ob.read_weights((int)b.data.board_type,"0");
    weight_ob.read_weights((int)b.data.board_type,"1");
    auto moveset = b.get_legal_moves();
    if (moveset.size() == 0) {
        std::cout << "Could not get any moves from board!\n";
        std::cout << board_to_str(&b.data);
        this->best_move = 0;
    }
    else{
        
        U16 best_action = 0;
        Board copy=Board(b);
        weight_ob.handy_print_features(get_features(copy,&weight_ob), (int)copy.data.board_type);
        cout<<endl;
        MCTSNode* root = new MCTSNode(copy,player, &weight_ob);
        
        int simulations;
        // IDA*
        for(int depth=4;depth<5;depth++){
                cout<<"......>>>>>>>IDA_STAR<<<<<<..........."<<depth<<endl;
                best_action= minimax(root,0,depth, &weight_ob).first;
                cout<< move_to_str(best_action)<<endl;
                this->best_move = best_action;
                weight_ob.write_weights((int)b.data.board_type);
                cout<<"Trained Weights Written"<<endl;
            }
    }
    

}


