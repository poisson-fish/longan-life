#ifndef _GOL_H
#define _GOL_H
extern "C" { 
    #include "lcd/lcd.h"
}

class GameOfLife{
    public:
        GameOfLife();
        void Tick();
        void Reset();
        void FillRandom();
        void RenderState();
    private:
        void Swap();
        bool StateGridGet(int x,int y);
        void UpdateGridSet(int x,int y,bool state);
        bool *StateGrid;
        bool *UpdateGrid;
};

#endif