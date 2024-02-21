#pragma once

#include "engine_base.hpp"
#include <atomic>


class Engine : public AbstractEngine {

    // add extra items here. 
    // Note that your engine will always be instantiated with the default 
    // constructor.

    
    public:
    U16 prev_move=0;
    U16 prev_prev_move=0;
    U16 prev_prev_prev_move=0;
    U16 prev_prev_prev_prev_move=0;
    void find_best_move(const Board& b) override;









};



