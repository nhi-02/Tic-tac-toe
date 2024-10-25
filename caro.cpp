#include "caro.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
using namespace std;
Cell::Cell()
{
    state = N;
}
Cell::Cell(int mrow, int mcol)
{
    row = mrow;
    col = mcol;
    state = N;
}
void Cell::setRow(int mrow)
{
    row = mrow;
}
void Cell::setCol(int mCol)
{
    col = mCol;
}
int Cell::getRow()
{
    return row;
}
int Cell::getCol()
{
    return col;
}
void Cell::setState(enum CellState mstate)
{
    state = mstate;
}
enum CellState Cell::getState()
{
    return state;
}
BoardGame::BoardGame(SDL_Surface *mwin, SDL_Window *mwindow)
{
    turn = 'x';
    win = mwin;
    window = mwindow;
    for (int i = 0; i < 16; i++)
        for (int j = 0; j < 16; j++)
        {
            cells[i][j].setRow(i);
            cells[i][j].setCol(j);
            cells[i][j].setState(N);
        }
    board = NULL;
    board = IMG_Load("board.png");
    imageX = IMG_Load("x1.png");
    imageO = IMG_Load("o1.png");
    imageN = IMG_Load("n1.png");
    SDL_BlitSurface(board, NULL, win, &areaBoard);
}
void BoardGame::click(int mrow, int mcol)
{
    areaXO.x = mcol * 50;
    areaXO.y = mrow * 50;
    if (cells[mrow][mcol].getState() != N)
        return;
    if (turn == 'x')
    {
        imageToDraw = imageX;
        cells[mrow][mcol].setState(X);
        turn = 'o';
    }
    else
    {
        imageToDraw = imageO;
        cells[mrow][mcol].setState(O);
        turn = 'x';
    }
    SDL_BlitSurface(imageToDraw, NULL, win, &areaXO);
    SDL_UpdateWindowSurface(window);
    winner(mrow, mcol);
}
void BoardGame::click_win(int mrow, int mcol)
{
    areaXO.x = mcol * 50;
    areaXO.y = mrow * 50;
    SDL_FillRect(win, &areaXO, 0x0000000);
    if (cells[mrow][mcol].getState() == X)
        imageToDraw = imageX;
    if (cells[mrow][mcol].getState() == O)
        imageToDraw = imageO;
    SDL_BlitSurface(imageToDraw, NULL, win, &areaXO);
}
bool BoardGame::winner(int mrow, int mcol)
{
    CellState s = cells[mrow][mcol].getState();
    cout << "state: " << s << ", (" << mrow << "," << mcol << ")" << endl;
    bool result = false;
    int d1 = 1, d2 = 1, d3 = 1, d4 = 1;
    // tính thắng theo cột mcol
    for (int i = mrow - 1; i >= 0; i--)
        if (cells[i][mcol].getState() == s)
            d1++;
        else
            break;
    for (int i = mrow + 1; i <= 15; i++)
        if (cells[i][mcol].getState() == s)
            d1++;
        else
            break;
    // đánh dấu cột nếu chiến thắng
    if (d1 >= 5)
    {
        // tính thắng theo cột mcol
        click_win(mrow, mcol);
        for (int i = mrow - 1; i >= 0; i--)
            if (cells[i][mcol].getState() == s)
                click_win(i, mcol);
            else
                break;
        for (int i = mrow + 1; i <= 15; i++)
            if (cells[i][mcol].getState() == s)
                click_win(i, mcol);
            else
                break;
    }
    // tính thắng theo hàng mrow
    for (int i = mcol - 1; i >= 0; i--)
        if (cells[mrow][i].getState() == s)
            d2++;
        else
            break;
    for (int i = mcol + 1; i <= 15; i++)
        if (cells[mrow][i].getState() == s)
            d2++;
        else
            break;
    // Tinh chien thang cho hang
    if (d2 >= 5)
    {
        click_win(mrow, mcol);
        for (int i = mcol - 1; i >= 0; i--)
            if (cells[mrow][i].getState() == s)
                click_win(i, mcol);
            else
                break;
        for (int i = mcol + 1; i <= 15; i++)
            if (cells[mrow][i].getState() == s)
                click_win(i, mcol);
            else
                break;
    }
    // tính thắng theo đường chéo 1
    // tính ngược lùi về gốc 0,0
    for (int i = mrow - 1, j = mcol - 1; i >= 0, j >= 0; i--, j--)
        if (cells[i][j].getState() == s)
            d3++;
        else
            break;
    // tính ngược tiến xa gốc 0,0
    for (int i = mrow + 1, j = mcol + 1; i <= 15, j <= 15; i++, j++)
        if (cells[i][j].getState() == s)
            d3++;
        else
            break;
    // ve duong chien thang
    if (d3 >= 5)
    {
        click_win(mrow, mcol);
        for (int i = mrow - 1, j = mcol - 1; i >= 0, j >= 0; i--, j--)
            if (cells[i][j].getState() == s)
                click_win(i, j);
            else
                break;
        // tính ngược tiến xa gốc 0,0
        for (int i = mrow + 1, j = mcol + 1; i <= 15, j <= 15; i++, j++)
            if (cells[i][j].getState() == s)
                click_win(i, j);
            else
                break;
    }
    // tính thắng theo đường chéo 2
    // tính chiều đi lên
    for (int i = mrow - 1, j = mcol + 1; i >= 0, j <= 15; i--, j++)
        if (cells[i][j].getState() == s)
            d4++;
        else
            break;
    // tính chiều đi xuống
    for (int i = mrow + 1, j = mcol - 1; i <= 15, j >= 0; i++, j--)
        if (cells[i][j].getState() == s)
            d4++;
        else
            break;
    // ve duong chien thang
    if (d4 >= 5)
    {
        click_win(mrow, mcol);
        for (int i = mrow - 1, j = mcol + 1; i >= 0, j <= 15; i--, j++)
            if (cells[i][j].getState() == s)
                click_win(i, j);
            else
                break;
        // tính chiều đi xuống
        for (int i = mrow + 1, j = mcol - 1; i <= 15, j >= 0; i++, j--)
            if (cells[i][j].getState() == s)
                click_win(i, j);
            else
                break;
    }
    if (d1 >= 5)
    {
        result = true;
        cout << "Nguoi choi " << s << " da chien thang theo cot doc!" << endl;
    }
    if (d2 >= 5)
    {
        result = true;
        cout << "Nguoi choi " << s << " da chien thang theo hang ngang!" << endl;
    }
    if (d3 >= 5)
    {
        result = true;
        cout << "Nguoi choi " << s << " da chien thang theo duong cheo NW-SE (1)!" << endl;
    }
    if (d4 >= 5)
    {
        result = true;
        cout << "Nguoi choi " << s << " da chien thang theo duong cheo SW-NE (2)!" << endl;
    }
    return result;
}