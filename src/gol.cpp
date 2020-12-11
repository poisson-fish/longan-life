#include "gol.hpp"
#include <random>

GameOfLife::GameOfLife()
{
    StateGrid = new bool[LCD_W*LCD_H];
    UpdateGrid = new bool[LCD_W*LCD_H];
}
bool GameOfLife::StateGridGet(int x,int y)
{
    int realx,realy;
    if(x < 0)
    {
        realx = LCD_W - x;
    }
    else
    {
        realx = x % LCD_W;
    } 
    if(y < 0)
    {
        realy = LCD_H - y;
    }
    else{
        realy = y % LCD_H;
    }
    return StateGrid[(realy * LCD_W) + realx];
}
void GameOfLife::UpdateGridSet(int x,int y,bool state)
{
    UpdateGrid[(x+(LCD_W*y))] = state;
}
void GameOfLife::Tick()
{
    int x, y = 0;
    for (y = 0; y <= LCD_H; y++)
    {
        for (x = 0; x <= LCD_W; x++)
        {
            int neighborAliveCellCount = StateGridGet(x-1,y+1)
                                        +StateGridGet(x,y+1)
                                        +StateGridGet(x+1,y+1)
                                        +StateGridGet(x-1,y)
                                        +StateGridGet(x+1,y)
                                        +StateGridGet(x-1,y-1)
                                        +StateGridGet(x,y-1)
                                        +StateGridGet(x+1,y-1)
                                        ;
            if(StateGridGet(x,y)){
                if(neighborAliveCellCount == 2 || neighborAliveCellCount == 3){
                    UpdateGridSet(x,y,true);
                }
                else{
                    UpdateGridSet(x,y,false);
                }
            }
            else{
                if(neighborAliveCellCount == 3){
                    UpdateGridSet(x,y,true);
                }
                else{
                    UpdateGridSet(x,y,false);
                }
            }
        }
    }
    Swap();
}
void GameOfLife::Swap()
{
    bool* tempPtr = StateGrid;
    StateGrid = UpdateGrid;
    UpdateGrid = tempPtr;
}
void GameOfLife::FillRandom(){
    int x, y = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 1);
    for (y = 0; y <= LCD_H; y++)
    {
        for (x = 0; x <= LCD_W; x++)
        {
            bool random = distrib(gen);
            StateGrid[(x+(LCD_W*y))] = random;
        }
    }
}
void GameOfLife::RenderState()
{
    int x, y = 0;
    bool cellState;
    for (y = 0; y <= LCD_H; y++)
    {
        for (x = 0; x <= LCD_W; x++)
        {
            cellState = StateGridGet(x,y);
            LCD_DrawPoint(x,y,cellState ? WHITE : BLACK);
        }
    }
}