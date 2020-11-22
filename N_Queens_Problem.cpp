/*
CS302 Assignment 2
Carlos Georges
*/

#include <iostream>
#include <iomanip>
using namespace std;
const int BOARD_SIZE = 8;
const int MIN_SIZE = 1;

void readCoordinates(int&, int&);
void printBoard(int, int);
bool solve(bool[BOARD_SIZE][BOARD_SIZE],int, int);
bool isSafe(bool , int , int );

int main(){
	int r,c;
	readCoordinates(r,c);
	printBoard(r,c);
}

/*
  FUNCTION: readCoordinates
  PARAMETERS: r, c, by reference so i can use them elsewhere
  RETURN TYPE: void
  DESCRIPTION: gets the initial placement from the user
 */
void readCoordinates(int& r, int &c) {
	do{
		cout << "Enter initial coordinates for the first queen: ";
		cin >> r >> c;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}while(r<MIN_SIZE || r>BOARD_SIZE || c < MIN_SIZE || c > BOARD_SIZE); //condition for board size
	
}

/*
  FUNCTION: printBoard
  PARAMETERS: r, c
  RETURN TYPE: void
  DESCRIPTION: creates the 2d array to store the queens and prints out the board
 */
void printBoard(int r, int c) {
	char board[BOARD_SIZE][BOARD_SIZE]; //create 2d array to print

	for (int i = 0; i < BOARD_SIZE; ++i)	
		for (int j = 0; j < BOARD_SIZE; ++j)			
			board[i][j] = '-'; //fill with dashes

	bool queens[BOARD_SIZE][BOARD_SIZE]; //create bool 2d array to maintain queens

	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j) 
			queens[i][j] = 0; //no queens in the array
	
	queens[r-1][c-1]=1; // mark the initial queen, 
	solve(queens, 0, r-1); // solve the problem
	
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			if(queens[i][j])
				board[i][j] = 'Q'; // if theres a queen, put a Q
		
	
	for (int i = 0; i<BOARD_SIZE+1; ++i) { // output formatting
		for(int j =0; j<BOARD_SIZE+1; ++j) {
			if (i==0&&j==0)
				cout << ' ';
			else if (i==0)
				cout << setw(3) <<j;
			else if (j==0)
				cout << i;
			if(i!=0&&j!=0)
			cout <<setw(3) << board[i-1][j-1];
		}
		cout << endl;
	}
	
}

/*
  FUNCTION: isSafe
  PARAMETERS: queens array, row and column to check
  RETURN TYPE: bool
  DESCRIPTION: checks if the position is under attack
 */
bool isSafe(bool queens[BOARD_SIZE][BOARD_SIZE], int r, int c) {
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			if (queens[i][j] && ((i==r||j==c||i+j==r+c||i-j==r-c)))	//if theres a queen, check the attacked spots
				return false;

	return true;
}

/*
  FUNCTION: solve
  PARAMETERS: queens, row to solve, initial row
  RETURN TYPE: bool
  DESCRIPTION: recursively solves the problem with backtracking algorithm
 */
bool solve(bool queens[BOARD_SIZE][BOARD_SIZE], int i, int r) {
	
	if (i== BOARD_SIZE) //base case, if we've reached the last row, we found the solution
		return true;
	
	for(int j=0; j < BOARD_SIZE; ++j) { 
		if (i==r) {// if row i has the row of the initial queen, skip it
			if (solve(queens, i+1, r)) //go to next row
				{return true;}
			else {
					queens[i][j] = 0; //if it doesnt work with initial queen, move initial queen to next column and try again
					queens[i][j+1]= 1;
				if (solve(queens, i+1, r))
					return true;	
				 
				 }
				}
		if (isSafe(queens,i,j)) { 
			queens[i][j] = 1; 		//if its safe, put a queen
			if(solve(queens, i+1, r)) //keep going on to the next row
					return true;
			queens[i][j]= 0;	//heres the backtracking
			}
		}
	return false; //if it gets here, its a dead end
}

/*
 * Quick summary of the algorithm, basically we're placing 
 * queens where it's safe, and trying to place all 8,
 * if we get to a row where theres no safe spots, remove
 * the last queen we placed and try the next safe spot.
 * we're basically exploring paths until we reach one that 
 * isn't a dead end.
 */