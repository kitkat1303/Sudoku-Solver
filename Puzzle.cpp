/**
 * @file Puzzle.cpp
 * @author Katarina McGaughy 
 * @brief The Puzzle class takes initializes 81 square objects into a 9x9
 * array. It takes 81 numbers as input and initializes the
 * square objects with the numbers. It then attempts to solve the puzzle 
 * via a backtracking mechanism.
 * @version 0.1 
 * @date 2021-11-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Puzzle.h"
#include <iostream>
#include <string>
using namespace std;

/**
 * Puzzle
 *
 * constructor initializes numberOfEmtyVars to 0 and
 * numberOfVariables to 0
 */
Puzzle::Puzzle() : numberOfEmptyVars(0), numberOfVariables(0), puzzleGrid()
{
}

/**
 * ~Puzzle
 *
 * destructor for the puzzle object
 */
Puzzle::~Puzzle()
{
}

/**
 * findNextEmpty
 *
 * this function iterates through the rows and columns
 * of the puzzle and returns true and the
 * row and col if the square is empty (value = 0)
 * @param row: row of the puzzle
 * @param col: col of the puzzle
 * @return true : if square at row and col is empty
 * @return false : if square at row and col is not
 * empty
 */
bool Puzzle::findNextEmpty(int &row, int &col)
{
   for (row = 0; row < 9; row++)
   {
      for (col = 0; col < 9; col++)
      {
         if (get(row, col) == 0)
         {               // marked with 0 is empty
            return true; // returns col and row
         }
      }
   }
   return false;
}

/**
 * Solve
 *
 * this function takes in a row and a collumn and attempts to fill the
 * empty variable squares with numbers in order to solve the puzzle. This
 * function calls the set function to see if the a number between 1-9 will
 * work.
 * PRE: the row and collumn must be between 0 and 8.
 * @return true : if the puzzle is solved
 * @return false : false if the puzzle does not have a solution
 */
bool Puzzle::Solve()
{
   int row, col;
   if (!findNextEmpty(row, col))
   {
      return true; // at end of puzzle
   }
   for (int value = 1; value <= 9; value++)
   {
      if (set(row, col, value))
      {
         numberOfEmptyVars--;
         puzzleGrid[row][col].setFixed(true);
         if (Solve())
         {
            return true;
         }
         puzzleGrid[row][col].setValue(0);
         numberOfEmptyVars++;
         puzzleGrid[row][col].setFixed(false);
      }
   }
   return false;
}

/**
 * get
 *
 * this function returns the value of the sqaure at the location
 * entered
 * PRE: the row and collumn must be between 0 and 8.
 * @param row : the row where the square is located
 * @param col : the col where the square is located
 */
int Puzzle::get(int row, int col)
{
   return puzzleGrid[row][col].getValue();
}

/**
 * set
 *
 * this function takes in an x and y location and sets the value
 * of the square at that location
 * PRE: the row and collumn must be between 0 and 8. The value must be between
 * 1 and 9.
 * @param row : current row of square
 * @param col : current collumn of square
 * @param value : an integer value that the square will be set to
 * @return: true if the value was set
 */
bool Puzzle::set(int row, int col, int value)
{
   // only set if accurate
   if (isSafe(row, col, value))
   {
      puzzleGrid[row][col].setValue(value);
      return true;
   }
   else
   {
      return false;
   }
}

/**
 * size
 *
 * this function returns the number of variable entries in the puzzle
 * before any blanks are filled
 * @return int
 */
int Puzzle::size()
{
   return numberOfVariables;
}

/**
 * numEmpty
 *
 * this function returns the current number of empty squares
 * @return int : returns the number of empty squares
 */
int Puzzle::numEmpty()
{
   return numberOfEmptyVars;
}

/**
 * isSafe
 *
 * this functions checks to see if it is safe to add the given value to
 * the square located in the given row and collumn. This function also calls
 * numberInBox, numberInRow, and numberInCol to see if it is safe to add the
 * value. It would be safe to add the value if the number is not in the box,
 * row, or collumn.
 * PRE: the row and collumn must be between 0 and 8. The value must be between
 * 1 and 9.
 * @param row : the row where the square is located
 * @param col : the col where the square is located
 * @param value : the value that is being tested to see if it is safe to
 * add at that location
 * @return true : if it is a valid place to place the square
 * @return false : if the value is not valid to add at that location
 */
bool Puzzle::isSafe(int row, int col, int value)
{
   // if the square is not empty return false
   if (!isVariableEmpty(row, col))
   {
      return false;
   }
   // if the number is in the box return false
   else if (numberInBox(row, col, value))
   {
      // cout << "Number is in box." << endl;
      return false;
   }
   // if the number is in row return false
   else if (numberInRow(row, value))
   {
      // cout << "Number is in row." << endl;
      return false;
   }
   // if the number is in collumn return false
   else if (numberInCol(col, value))
   {
      // cout << "Number is in collumn." << endl;
      return false;
   }
   return true;
}

/**
 * numberInBox
 *
 * this function checks to see if the value given is in the box
 * PRE: the row and collumn must be between 0 and 8. The value must be between
 * 1 and 9.
 * @param row : the row where the square is located
 * @param col : the col where the square is located
 * @param value : value to see if the value appears in the box
 * @return true : if the value is in the box
 * @return false : if the value is not in the box
 */
bool Puzzle::numberInBox(int row, int col, int value)
{
   int boxStartRow = -1;
   int boxStartCol = -1;
   int boxEndRow = -1;
   int boxEndCol = -1;
   if (row >= 0 && row < 3)
   {
      boxStartRow = 0;
      boxEndRow = 3;
   }
   else if (row >= 3 && row < 6)
   {
      boxStartRow = 3;
      boxEndRow = 6;
   }
   else
   {
      boxStartRow = 6;
      boxEndRow = 9;
   }
   if (col >= 0 && col < 3)
   {
      boxStartCol = 0;
      boxEndCol = 3;
   }
   else if (col >= 0 && col < 3)
   {
      boxStartCol = 3;
      boxEndCol = 6;
   }
   else
   {
      boxStartCol = 6;
      boxStartCol = 9;
   }

   for (int y = boxStartCol; y < boxEndCol; y++){
      for (int x = boxStartRow; x < boxEndRow; x++){
         if (get(x, y) == value)
            return true;
      }
   }
   return false;
}

/**
 * numberInRow
 *
 * this function checks to see if the value given is in the row
 * PRE: the row must be between 0 and 8. The value must be between
 * 1 and 9.
 * @param row : the row where the square is located
 * @param value : value to see if the value appears in the row
 * @return true : if the value is in the row
 * @return false : if the value is not in the row
 */
bool Puzzle::numberInRow(int row, int value)
{
   for (int col = 0; col < 9; col++)
      if (get(row, col) == value)
         return true;
   return false;
}

/**
 * numberInCol
 *
 * this function checks to see if the value given is in the col
 * PRE: the collumn must be between 0 and 8. The value must be between
 * 1 and 9.
 * @param col : the col where the square is located
 * @param value : value to see if the value appears in the collumn
 * @return true : if the value is in the collumn
 * @return false : if the value is not in the collumn
 */
bool Puzzle::numberInCol(int col, int value)
{
   for (int row = 0; row < 9; row++)
      if (get(row, col) == value)
         return true;
   return false;
}

/**
 * isVariableEmpty
 *
 * this functiomn takes in a row and col and returns true if the square
 * at that location is a 0.
 * PRE: the row and collumn must be between 0 and 8.
 * @param row : row where the square is located
 * @param col : collumn where the sqaure is located
 * @return true : if value of square is 0
 * @return false : if value of square is not 0
 */
bool Puzzle::isVariableEmpty(int row, int col)
{
   return puzzleGrid[row][col].getFixed() == false &&
          puzzleGrid[row][col].getValue() == 0;
}

/**
 * operator<<
 *
 * this function takes in an ostream and puzzle object
 * and returns the ostream in a specific grid format
 * @param os : the output stream
 * @param puzzle : the sudoku puzzle
 * @return ostream& : the output stream edited
 */
ostream &operator<<(ostream &os, Puzzle &puzzle)
{
   for (int row = 0; row < 9; row++)
   {
      for (int col = 0; col < 9; col++)
      {
         if (col == 2 || col == 5)
         {
            cout << puzzle.get(row, col) << "|";
         }
         else if (col == 8)
         {
            cout << puzzle.get(row, col) << endl;
         }
         else
         {
            cout << puzzle.get(row, col) << " ";
         }
      }
      if (row == 2 || row == 5)
      {
         cout << "-----+-----+-----" << endl;
      }
   }
   cout << endl;
   return os;
}

/**
 * operator>>
 *
 * this function takes in an istream and puzzle object and initializes
 * the squares with the values in order and places them in a 2D array
 * @param is: input stream
 * @param puzzle : puzzle object
 * @return istream& : returns the istream
 */
istream &operator>>(istream &in, Puzzle &puzzle)
{

   string numbers;
   cout << "Please enter 81 numbers to initialize the Sudoku puzzle: " << endl;
   in >> numbers;

   // if the numbers entered do not amount to 81, print out an error
   // message
   if (numbers.length() != 81)
   {
      cerr << "The input is not 81 characters long.";
      cerr << "Please input a correct Sudoku puzzle" << endl;
   }

   else
   {

      int number = 0;
      for (int row = 0; row < 9; row++)
      {
         for (int col = 0; col < 9; col++)
         {
            puzzle.puzzleGrid[row][col].setValue((int)numbers[number] - '0');
            if ((int)numbers[number] - '0' == 0)
            {
               puzzle.puzzleGrid[row][col].setFixed(false);
               puzzle.numberOfVariables++;
               puzzle.numberOfEmptyVars++;
            }
            number++;
         }
      }
   }
   return in;
}

/**
 * Sqaure
 *
 * @brief Construct a new Square object
 * this constructor sets the newly initialized
 * sqaure's value to -1. The fixed will also be set to true.
 * @param setValue: the integer value the square will contain
 *
 */
Puzzle::Square::Square() : value(-1), fixed(true)
{
}

/**
 * ~Square
 *
 * @brief Destroy the Square object
 * this function destroys the square object
 */
Puzzle::Square::~Square()
{
}

/**
 * getValue
 *
 * @brief Get the Value object
 * this function returns the value stored in the square
 * @return int: integer value held in square
 */
int Puzzle::Square::getValue()
{
   return value;
}

/**
 * setValue
 * @brief Set the Value object
 * this function takes in a new integer value and sets it
 * this function does not enforce any constraints among values in the
 * same row, collumn, or block
 *
 * @param newValue : new value the objects value will be set to
 */
void Puzzle::Square::setValue(int newValue)
{
   value = newValue;
}

/**
 * setFixed
 *
 * this function takes in a bool and sets fixed to that bool value
 * @param newFixed : what the member variable, fixed, will be set
 * to
 */
void Puzzle::Square::setFixed(bool newFixed)
{
   fixed = newFixed;
}

/**
 * getFixed
 *
 * returns true if fixed is true and false is fixed is false
 * @return true : if fixed is true
 * @return false : if fixed is false
 */
bool Puzzle::Square::getFixed()
{
   return fixed;
}
