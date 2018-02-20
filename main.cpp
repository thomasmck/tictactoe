/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Tom
 *
 * Created on 07 January 2018, 20:22
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

vector< vector<int> > processTurn(vector< vector<int> > rows, int x, int y, int player, int* ok){
    
    // Check if position is already written to
    if (rows[y-1][x-1] == 0){
        rows[y-1][x-1] = player;
        // Set success flag
        if(ok) { *ok = 1; }
    } else {
        // Set error flag
        if(ok) { *ok = 0; }
    }
    return rows;
}

void printState(vector< vector<int> > rows){
    
    // Create iterators for the inner and outer vectors
    vector< vector<int> >::iterator it_ex;
    vector<int>::iterator it_in;
    
    //Print out current game state in grid
    for (it_ex = rows.begin(); it_ex != rows.end(); it_ex++){
        int row_it = 1;
        for (it_in = (*it_ex).begin(); it_in != (*it_ex).end(); it_in++){
            cout << "|";
            if ((*it_in) == 0) cout << " ";
            // Player 1 is "x"'s
            if ((*it_in) == 1) cout << "x";
            // Player 2 us "0"'s
            if ((*it_in) == 2) cout << "0";
            if (row_it == 3) cout << "|" << endl;
            row_it++;
        }
    }
}

bool checkForWinner(vector< vector<int> > rows){
    
    // Check is any of the winning combinations are met
    // TODO: This is really ugly, must be a nicer way
    if (rows[0][0] == rows[1][0] and rows[1][0] == rows[2][0] and rows[1][0] != 0) return 1;
    if (rows[0][1] == rows[1][1] and rows[1][1] == rows[2][1] and rows[1][1] != 0) return 1;
    if (rows[0][2] == rows[1][2] and rows[1][2] == rows[2][2] and rows[1][2] != 0) return 1;
    
    if (rows[0][0] == rows[0][1] and rows[0][1] == rows[0][2] and rows[0][1] != 0) return 1;
    if (rows[1][0] == rows[1][1] and rows[1][1] == rows[1][2] and rows[1][1] != 0) return 1;
    if (rows[2][0] == rows[2][1] and rows[2][1] == rows[2][2] and rows[2][1] != 0) return 1;
    
    if (rows[0][0] == rows[1][1] and rows[1][1] == rows[2][2] and rows[1][1] != 0) return 1;
    if (rows[0][2] == rows[1][1] and rows[1][1] == rows[2][0] and rows[1][1] != 0) return 1;
    return 0;
}

int main(int argc, char** argv) {
    
    // Construct initial game board
    vector<int> row = {0,0,0};
    vector< vector<int> > rows;
    rows.push_back(row);
    rows.push_back(row);
    rows.push_back(row);
    
    // Set up parameters
    bool winner = 0;
    int turn = 1;
    int player;
    cout<<"Welcome to this game of tic tac toe"<<endl;
    
    // Keep playing till we find a winner
    while (winner != 1){
        // Error flag
        int ok = 0;
        
        // Work out which players turn it is
        if (turn % 2 == 0) player = 2;
        else player = 1;
        
        cout << "The current game state is:" << endl;
        printState(rows);
        
        // Get player's moves
        cout << "Player " << player << " it is your turn, enter x and y coordinates" <<endl;
        int x;
        cin>>x;
        int y;
        cin>>y;
    
        // Check is user's move selection is valid
        while (!ok){
            rows = processTurn(rows, x, y, player, &ok);
            if(!ok) {
                printf("Invalid turn please pick again");
                cout << "Player " << player << " it is your turn, enter x and y coordinates" <<endl;
                cin>>x;
                cin>>y;
            }
        }
        
        // Check is someone has won
        winner = checkForWinner(rows);
        turn++;
    }
    
    // Declare winner
    cout<<"Winner is player " << player <<endl;
    return 0;
}

