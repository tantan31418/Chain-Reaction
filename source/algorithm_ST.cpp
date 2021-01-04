#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/


void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
    srand(time(NULL)*time(NULL));
    int row, col;
    int color = player.get_color();
    
    while(1){
        row = rand() % 5;
        col = rand() % 6;
        if(board.get_cell_color(row, col) == color || board.get_cell_color(row, col) == 'w') break;
    }

    index[0] = row;
    index[1] = col;
    
}


int score (Board board, Player player) {
    int color = player.get_color();
    int sc = 0;
    int my_orbs =0 , enemy_orbs = 0;
    for (int row = 0; row < 5; row ++){
        for (int col = 0; col <6;col++){
            if (board.get_cell_color(row, col) == color){
                my_orbs +=  board.get_orbs_num(row,col);
                int flag_not_vun = 1;
                //negibors
                if (row!=0 && col!=0){
                    if (board.get_cell_color(row-1,col-1) != color){
                        if (board.get_orbs_num(row-1,col-1)==board.get_capacity(row-1,col-1)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                if (row!=0){
                    if (board.get_cell_color(row-1,col) != color){
                        if (board.get_orbs_num(row-1,col)==board.get_capacity(row-1,col)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                if (row!=0 && col!=5){
                    if (board.get_cell_color(row-1,col+1) != color){
                        if (board.get_orbs_num(row-1,col+1)==board.get_capacity(row-1,col+1)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                if (col!=0){
                    if (board.get_cell_color(row,col-1) != color){
                        if (board.get_orbs_num(row,col-1)==board.get_capacity(row,col-1)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                if (col!=5){
                    if (board.get_cell_color(row,col+1) != color){
                        if (board.get_orbs_num(row,col+1)==board.get_capacity(row,col+1)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                if (row!=4 && col!=0){
                    if (board.get_cell_color(row+1,col-1) != color){
                        if (board.get_orbs_num(row+1,col-1)==board.get_capacity(row+1,col-1)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                if (row!=4){
                    if (board.get_cell_color(row+1,col) != color){
                        if (board.get_orbs_num(row+1,col)==board.get_capacity(row+1,col)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                if (row!=4 && col!=5){
                    if (board.get_cell_color(row+1,col+1) != color){
                        if (board.get_orbs_num(row+1,col+1)==board.get_capacity(row+1,col+1)-1){
                            sc -= 5-board.get_capacity(row,col);
                            flag_not_vun = 0;
                        }
                    }
                }
                /*neigbor end*/
                if (flag_not_vun==1){
                    //corner
                    if (board.get_capacity(row,col)==3){
                        sc+=3;
                    }
                    //edge
                    else if (board.get_capacity(row,col)==5){
                        sc+=2;
                    }
                    //unstable
                    if (board.get_orbs_num(row,col)==board.get_capacity(row,col)-1){
                        sc +=2;
                    }
                }
            }
            else {
                enemy_orbs += board.get_orbs_num(row,col);
            }
        }
    }
    sc += my_orbs;
    if (enemy_orbs == 0 && my_orbs > 1) {
        return 10000;
    }
    else if (my_orbs ==0 && enemy_orbs >1) {
        return -10000;
    }
    //chain

    return sc;
}