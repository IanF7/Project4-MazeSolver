//Source for MazeSolver
//Ian Fletcher
//CST-201
//10/14/2022
//The depthFirst method is my own, the rest is from the template

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "myStack.h"
#include "MazeCell.h"

using namespace std;

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define DONE 4
#define SUCCESS 10
#define FAILURE 20

//method headers*******************************************************

//depthFirst header
void depthFirst(MazeCell start, MazeCell end);

//global variables*****************************************************

//# rows and cols in the maze
int rows, cols;
//pointer to the grid (2-d array of ints)
int** grid;
//pointer to the maze cells (2-d array of MazeCell objects)
MazeCell** cells;

int main() {
	//create the Maze from the file
	ifstream fin("maze.in");
	if (!fin) {
		cout << "File not found\n";
		exit(2);
	}

	//read in the rows and cols
	fin >> rows >> cols;

	//create the maze rows
	grid = new int* [rows];

	//add each column
	for (int i = 0; i < rows; i++)
		grid[i] = new int[cols];

	//read in the data from the file to populate
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			fin >> grid[i][j];
		}
	}

	//look at it 
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] == 3)
				cout << "S" << " ";
			else if (grid[i][j] == 4)
				cout << "E" << " ";
			else
				cout << grid[i][j] << " ";
		}
		cout << endl;
	}

	//make a 2-d array of cells
	cells = new MazeCell * [rows];
	for (int i = 0; i < rows; i++) {
		cells[i] = new MazeCell[cols];
	}

	//all MazeCell in the cells grid has a default init
	//only update those cells that are not walls

	MazeCell start, end;

	//iterate over the grid
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j] != 0) {
				cells[i][j].setCoordinates(i, j);
				//look for the start and end cells
				if (grid[i][j] == 3)
					start = cells[i][j];
				if (grid[i][j] == 4)
					end = cells[i][j];

			}

		}
	}

	//testing
	cout << "start: " << start << " end: " << end << endl;

	//solve it!
	depthFirst(start, end);


	return 0;
}


//this function should find a path through the maze
//if found, output the path from start to end
//if not path exists, output a message stating so

void depthFirst(MazeCell start, MazeCell end)
{
	//creates ints row and col and sets them equal to the row and col at start
	int row = start.getRow();
	int col = start.getCol();
	//creates an int stuck and sets it equal to 0
	int stuck = 0;
	//creates stack MazeCell
	MyStack<MazeCell> stack;
	cout << " " << endl;
	//runs while
	while (row != end.getRow() || col != end.getRow())
	{
		//resets stuck
		stuck = 0;
		//check left
		//removes 1 from col
		col--;
		//if col is not out of bounds, runs, otherwise resets col to the previous value
		//and updates stuck
		if (col >= 0)
		{
			//if the value isn't -1 and is unvisted runs, otherwise resets col to the previous 
			//value and updates stuck
			if (cells[row][col].getCol() != -1 && cells[row][col].unVisited())
			{
				//adds previous space to top and marks it as visited
				stack.push(cells[row][col + 1]);
				cells[row][col + 1].visit();
				//prints out the top and left
				cout << stack.top() << endl;
				cout << "left" << endl;
			}
			else
			{
				col++;
				stuck++;
			}
		}
		else
		{
			col++;
			stuck++;
		}
		//check down
		//adds 1 to row
		row++;
		//if row is not out of bounds, runs, otherwise resets row to the previous value
		//and updates stuck
		if (row < rows)
		{
			//if the value isn't -1 and is unvisted runs, otherwise resets row to the previous 
			//value and updates stuck
			if (cells[row][col].getRow() != -1 && cells[row][col].unVisited())
			{
				//adds previous space to top and marks it as visited
				stack.push(cells[row - 1][col]);
				cells[row - 1][col].visit();
				//prints out the top and left
				cout << stack.top() << endl;
				cout << "down" << endl;
			}
			else
			{
				row--;
				stuck++;
			}
		}
		else
		{
			row--;
			stuck++;
		}
		//check right
		//adds 1 to col
		col++;
		//if col is not out of bounds, runs, otherwise resets col to the previous value
		//and updates stuck
		if (col < cols)
		{
			//if the value isn't -1 and is unvisted runs, otherwise resets col to the previous 
			//value and updates stuck
			if (cells[row][col].getCol() != -1 && cells[row][col].unVisited())
			{
				//adds previous space to top and marks it as visited
				stack.push(cells[row][col - 1]);
				cells[row][col - 1].visit();
				//prints out the top and left
				cout << stack.top() << endl;
				cout << "right" << endl;
			}
			else
			{
				col--;
				stuck++;
			}
		}
		else
		{
			col--;
			stuck++;
		}
		//check up
		//removes 1 to row
		row--;
		//if row is not out of bounds, runs, otherwise resets row to the previous value
		//and updates stuck
		if (row >= 0)
		{
			//if the value isn't -1 and is unvisted runs, otherwise resets row to the previous 
			//value and updates stuck
			if (cells[row][col].getRow() != -1 && cells[row][col].unVisited())
			{
				//adds previous space to top and marks it as visited
				stack.push(cells[row + 1][col]);
				cells[row + 1][col].visit();
				//prints out the top and left
				cout << stack.top() << endl;
				cout << "up" << endl;
			}
			else
			{
				row++;
				stuck++;
			}
		}
		else
		{
			row++;
			stuck++;
		}
		//checks if row and col equal the end values of row and col
		if (row == end.getRow() && col == end.getCol())
		{
			//prints out results and breaks loop
			cout << "" << endl;
			cout << end << endl;
			cout << "There was a path!" << endl;
			break;
		}
		//checks if stuck is 4
		if (stuck == 4)
		{
			//updates current value to visited
			cells[row][col].visit();
			//removes top value from stack
			stack.pop();
			//checks if stack is empty
			if (stack.empty())
			{
				//prints out results and ends loop
				cout << "No route was found" << endl;
				break;
			}
			//resets visited of the new top
			cells[stack.top().getRow()][stack.top().getCol()].reset();
			//sets row and col equal to row and col at the new top
			row = stack.top().getRow();
			col = stack.top().getCol();
			//prints out new top and that the top was popped
			cout << stack.top() << endl;
			cout << "pop" << endl;
		}
		cout << " " << endl;
	}
}