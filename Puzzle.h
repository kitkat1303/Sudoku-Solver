/**
 * @file Puzzle.h
 * @author Katarina Mcgaughy 
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
#include <iostream>
#ifndef PUZZLE
#define PUZZLE
using namespace std;

class Puzzle
{

public:
   /**
    * Puzzle
    *
    * constructor
    */
   Puzzle();

   /**
    * ~Puzzle
    *
    * destructor for the puzzle object
    */
   ~Puzzle();


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
   bool Solve();

   /**
    * get
    *
    * this function returns the value of the sqaure at the location
    * entered
    * PRE: the row and collumn must be between 0 and 8.
    * @param row : the row where the square is located
    * @param col : the col where the square is located
    */
   int get(int row, int col);

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
   bool set(int row, int col, int value);

   /**
    * size
    *
    * this function returns the number of variable entries in the puzzle
    * before any blanks are filled
    * @return int
    */
   int size();

   /**
    * numEmpty
    *
    * this function returns the current number of empty squares
    * @return int : returns the number of empty squares
    */
   int numEmpty();

   /**
    * operator<<
    *
    * this function takes in an ostream and puzzle object
    * and returns the ostream in a specific grid format
    * @param os : the output stream
    * @param puzzle : the sudoku puzzle
    * @return ostream& : the output stream edited
    */
   friend ostream &operator<<(ostream &os, Puzzle &puzzle);

   /**
    * operator>>
    *
    * this function takes in an istream and puzzle object and initializes
    * the squares with the values in order and places them in a 2D array
    * @param is: input stream
    * @param puzzle : puzzle object
    * @return istream& : returns the istream
    */
   friend istream &operator>>(istream &in, Puzzle &puzzle);

private:
   class Square
   {

   public:
      /**
       * Square
       * @brief Construct a new Square object
       * this constructor sets the newly initialized
       * sqaure's value to -1. The fixed will also be set.
       * @param setValue: the integer value the square will contain
       *
       */
      Square();

      /**
       * ~Square
       * @brief Destroy the Square object
       * this function destroys the square object
       */
      ~Square();

      /**
       * getValue
       * @brief Get the Value object
       * this function returns the value stored in the square
       * @return int: integer value held in square
       */
      int getValue();

      /**
       * setValue
       * @brief Set the Value object
       * this function takes in a new integer value and sets it
       * this function does not enforce any constraints among values in the
       * same row, collumn, or block
       * @param newValue
       * @return true
       * @return false
       */
      void setValue(int newValue);

      // not sure if you can do this...
      /**
       * @brief Set the object to either fixed false or fixed is true
       *
       * @param fixed : true or false depending on if the square value is variable
       */
      void setFixed(bool fixed);

      /**
       * @brief Get wether or not fixed is true or false
       *
       * @return true : if the square value is fixed
       * @return false : false if the square value is not fixed
       */
      bool getFixed();

   protected:
      // value stored in the square
      int value;
      // wether or not the squares value is fixed
      bool fixed;
   };

   // number of variables that the puzzle started out with
   int numberOfVariables;

   // number of empty squares at current
   int numberOfEmptyVars;

   // puzzle grid that is 9 by 9 and holds squares
   Square puzzleGrid[9][9];

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
   bool findNextEmpty(int &row, int &col);

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
   bool isSafe(int row, int col, int value);

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
   bool numberInBox(int row, int col, int value);

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
   bool numberInCol(int col, int value);

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
   bool numberInRow(int row, int value);

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
   bool isVariableEmpty(int row, int col);


};
#endif