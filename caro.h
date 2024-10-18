#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
enum CellState
{
    X = 1,
    O = 0,
    N = -1
};
class Cell
{
private:
    int row, col;
    enum CellState state;

public:
    Cell();
    Cell(int mrow, int mcol);
    void draw();
    void clear();
    void setRow(int mrow);
    void setCol(int mrow);
    int getRow();
    int getCol();
    void setState(enum CellState mstate);
    enum CellState getState();
};
class BoardGame
{
private:
    SDL_Surface *win, *board, *imageX, *imageO, *imageToDraw;
    SDL_Rect areaBoard = {0, 0, 800, 800};
    SDL_Rect areaXO = {0, 0, 50, 50};
    Cell cells[16][16];
    char turn;

public:
    BoardGame(SDL_Surface *mwin);
    // ~BoardGame();
    bool winner(int mrow, int mcol);
    void click(int mrow, int mcol);
};