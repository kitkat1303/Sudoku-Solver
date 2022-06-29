/**
 * @file SquareTester.cpp
 * @author Katarina McGaughy 
 * @brief SquareTester performs tests on the Puzzle class by 
 * taking in 81 numbers and solving the sudoku puzzle if possible 
 * @version 0.1
 * @date 2021-11-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Puzzle.h"
#include <iostream>
using namespace std;

int main()
{

   Puzzle puzzle;
   cin >> puzzle;
   cout << "Printing puzzle before solving: " << endl;
   cout << puzzle;
   if (puzzle.Solve()){
      cout << "Printing puzzle after solving: " << endl;
      cout << puzzle;
   }
   else {
       cout << "Puzzle could not be solved." << endl;
   }

   return 0;
}
