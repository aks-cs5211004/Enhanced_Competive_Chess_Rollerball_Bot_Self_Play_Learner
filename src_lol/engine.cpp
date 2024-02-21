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
            feature_size=2*10+2*10+2*6*8*8+2;
            no_of_players=10;
            size_of_board=8;
            st="./src/wt3"+type+".txt";
        }
        else if(btype==2){
            feature_size=2*8+2*8+2*5*8*8+2;
            no_of_players=8;
            size_of_board=8;
            st="./src/wt2"+type+".txt";
        }
        else{
            feature_size=2*6+2*6+2*4*7*7+2;
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
        if(btype==1)
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
        else{
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
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
        if(btype==1)
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
        else{
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        file<<weights_backed_dynmaic[k]<<" ";
                        k++;
                }
                file<<endl;
            }
        }

        for(int i=0;i<2;i++){
                    file<<weights_backed_dynmaic[k]<<" ";
                    k++;
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
        if(btype==1){
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
            }
        }
        else{
                for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
                }
                    for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
                }
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
        // PAWNS
        if(btype==1){
            for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
            }
        }
        else{
                for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
                }
                    for(int i=0;i<size_of_board;i++){
                for(int j=0;j<size_of_board;j++){
                        cout<<features[k]<<" ";
                        k++;
                }
                cout<<endl;
                }
        }
        for(int i=0;i<2;i++){
                    cout<<features[k]<<" ";
                    k++;
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
        if(state.under_threat(peice_pos[i+adv_color*10]) && (state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_ROOK)){
            features[k]=2.7;
        }
        else if(state.under_threat(peice_pos[i+adv_color*10]) && peice_pos[i+adv_color*10]!=DEAD)
            features[k]=1;
        
        k++;
    }
    state.flip_player_();
    // threat_to_player 
    for(int i:peices_under_consideration){
        if(state.under_threat(peice_pos[i+color*10]) && (state.data.board_0[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+color*10]]==PAWN_ROOK)){
            features[k]=2.7;
        }
        else if(state.under_threat(peice_pos[i+color*10]) && peice_pos[i+color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // player_count
    for(int i:peices_under_consideration){
        if((state.data.board_0[peice_pos[i+color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+color*10]]==PAWN_ROOK)){
            features[k]=2.7;
        }
        else if(peice_pos[i+color*10]!=DEAD)
            features[k]=1;
        k++;
    }
    // adversary_count
    for(int i:peices_under_consideration){
        if((state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_BISHOP || state.data.board_0[peice_pos[i+adv_color*10]]==PAWN_ROOK)){
            features[k]=2.7;
        }
        else if(peice_pos[i+adv_color*10]!=DEAD)
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
    // PAWNS T1
    if(state.data.board_type==1){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[6+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
        }
    }
    else if(state.data.board_type==2){
        // PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[8+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }
    }

    else if (state.data.board_type==3){
        // PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[9+color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
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

    // ADV  PAWNS T1
    if(state.data.board_type==1){
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
        for(int j=0;j<weight_ob->size_of_board;j++){
            if(peice_pos[6+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                features[k]=1;
        k++;
        }
        }
    }
    else if(state.data.board_type==2){
        // ADV PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // ADV PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[8+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[9+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }
    }

    else if (state.data.board_type==3){
        // ADV PAWNS T1
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[6+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[7+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board) || peice_pos[8+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }

        // ADV PAWNS T2
        for(int i=weight_ob->size_of_board-1;i>=0;i--){
            for(int j=0;j<weight_ob->size_of_board;j++){
                if(peice_pos[9+adv_color*10]==create_pos(j,i,color,weight_ob->size_of_board))
                    features[k]=1;
            k++;
            }
        }
    }


    if(state.get_pseudolegal_moves_for_piece(peice_pos[2+adv_color*10]).size()<=5 && state.under_threat(peice_pos[2+adv_color*10])){
            features[k]+=1;
            k++;
    }
    if(state.get_pseudolegal_moves_for_piece(peice_pos[2+color*10]).size()<=5 && state.under_threat(peice_pos[2+color*10])){
            features[k]+=1;
            k++;
    }



    return features;

}

double evaluation(Board state,WEIGHTS* weight_ob, PlayerColor player){
    vector<int> features= get_features(state,weight_ob);
    double eval=0;
    for(int fs=0;fs<features.size();fs++){
        if(player==BLACK){
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
    int visits;
    double totalScore;
    U16 move_done;
    MCTSNode* parent;
    std::vector<MCTSNode*> children;
    Board board;
    PlayerColor player;
    WEIGHTS* weight_ob;
    //Constructor
    MCTSNode(Board st, PlayerColor player, WEIGHTS* ob) : visits(0), totalScore(0.0),move_done(0), parent(nullptr), board(st), player(player), weight_ob(ob) {children.resize(0, nullptr);}
};

//MCTS Function

MCTSNode* selectNode(MCTSNode* root){
    root->visits+=1;
    double parent_visit = root->visits;
    double Max_value = INT_MIN;
    // double exploration_factor = 0.0075; //EXPLORATION FACTOR
    double exploration_factor = 0.03;
    MCTSNode* choosenode= root->children[0];
    for(auto x:root->children){
        double curr_visits = x->visits;
        double total = x->totalScore;
        // if(curr_visits==0){
        //     choosenode=x;
        //     return choosenode;
        // }
        double value;
        if(root->board.data.player_to_play==root->player){
            value = (total+0.0001)/(curr_visits+0.0001) + exploration_factor*sqrt(log(parent_visit))/(curr_visits+0.0001);
        }
        else{
            value = 1 - (total+0.0001)/(curr_visits+0.0001) + exploration_factor*sqrt(log(parent_visit))/(curr_visits+0.0001);
        }
        // cout<<(total+0.0001)/(curr_visits+0.0001)<<", "<<exploration_factor*sqrt(log(parent_visit))/(curr_visits+0.0001)<<", "<<curr_visits<<" :::: ";
        if(value >= Max_value){
            choosenode = x;
            Max_value = value;
        }
    }
    // cout<<endl;
    return choosenode;
}

void expandNode(MCTSNode* node){
    if(node->children.size()!=node->board.get_legal_moves().size()){
        node->children.resize(0);
        for(auto x:node->board.get_legal_moves()){
            Board copy = Board((node->board));
            copy.do_move_(x);
            MCTSNode* childnode = new MCTSNode(copy,node->player, node->weight_ob);
            childnode->parent = node;
            childnode->move_done = x;
            node->children.push_back(childnode);
        }
    }
    else{
        // Node already Expanded
    }
}

double utility(MCTSNode* node){
    U8* peice_pos=(U8*) &(node->board.data);
    int adv_color=1;
    if(node->player==WHITE){
        adv_color=1;   
    }
    else adv_color=0;

    if(node->board.get_legal_moves().size()==0 && node->board.data.player_to_play==node->player){
        return 0;
    }
    else if(node->board.get_legal_moves().size()==0 && node->board.data.player_to_play!=node->player) {
        return 1;
    }

    if(node->board.data.player_to_play==node->player){
            return sigmoid(evaluation(node->board,node->weight_ob, node->player));
    }
    else{
            return 1-sigmoid(evaluation(node->board,node->weight_ob, node->player));
    }
}

void backpropagate(MCTSNode* node , double score, int depth, int simulations){
    int iter=0;
    auto leafnode= node;
    // cout<<"Laef "<<leafboard.data.player_to_play<<endl;
    // double lr=0.0000000005*depth*depth*depth*simulations;
    double lr=0.000000001*depth*depth*depth*simulations;
    while(node != nullptr){
        if(node->player==WHITE)
            if(node->board.data.player_to_play==WHITE){
                node->weight_ob->update_weights(score,sigmoid(evaluation(node->board,node->weight_ob, node->player)), get_features(node->board,node->weight_ob), lr);
            }
        node->totalScore += score;
        // cout<<node->totalScore<<endl;
        node = node->parent; 
    }
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
        for(int depth=3;depth<4;depth++){
                cout<<"......>>>>>>>IDA_STAR<<<<<<..........."<<depth<<endl;
                simulations=100*depth;
                // SIMULATIONS
                for(int i=0;i<simulations;i++){
                    // cout<<"\nSIMULATION NO........................................................ "<<i<<endl;
                    int curr_depth=0;
                    MCTSNode* childNode=root;
                    expandNode(childNode);
                    while (!childNode->children.empty() && (curr_depth<depth)) {
                        // cout<<"Depth "<<curr_depth<<" ";
                        MCTSNode* selectedNode = selectNode(childNode);
                        childNode=(MCTSNode*)selectedNode;
                        expandNode(childNode);
                        curr_depth++;
                    }
                    // cout<<"Get leafs util..."<<endl;
                    double playoutResult = utility(childNode);
                    cout<<childNode->visits<<" ";
                    // cout<<"Result for this Simulation "<<i<<" "<<playoutResult<<endl;
                    childNode->visits+=1;
                    // cout<<"Now back prop"<<endl;
                    backpropagate(childNode, playoutResult, depth, i);
                }
                // cout<<endl;
                // Choose the best action based on the tree's statistics
                // cout<<"Choosen the Best action for this IDA_STAR";
                MCTSNode* bestChild = root->children[0];
                for (MCTSNode* child : root->children) {
                    if(child->visits!=0){
                    if (child->totalScore/child->visits >= bestChild->totalScore/bestChild->visits ) {
                        bestChild = child;
                        best_action = child->move_done;
                    }
                    }
                }
                for(auto i:moveset){
                    cout<< move_to_str(i)<<" ";
                }
                cout<<endl;
                cout<< move_to_str(best_action)<<endl;
                this->best_move = best_action;
                weight_ob.write_weights((int)b.data.board_type);
                cout<<"Trained Weights Written"<<endl;
            }
    }
    

}


