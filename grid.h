/*Header file contaning the Grid class and all of its member functions's declaration and definitions
Written by Jason Liang*/

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
  private:
    struct ROW {
      T*  Cols;     // array of column elements
      size_t NumCols;  // total # of columns (0..NumCols-1)
    };

  ROW* Rows;     // array of ROWs
  size_t  NumRows;  // total # of rows (0..NumRows-1)

  public:
    
    /*Default constructor
    Creates a grid with 4 rows and 4 columns, with grid value initialized to default value of T*/
    Grid() {
      Rows = new ROW[4];  // 4 rows
      NumRows = 4;

      // initialize each row to have 4 columns:
      for (size_t r = 0; r < NumRows; ++r) {
        Rows[r].Cols = new T[4];
        Rows[r].NumCols = 4;

        // initialize the elements to their default value:
        for (size_t c = 0; c < Rows[r].NumCols; ++c) {
          Rows[r].Cols[c] = T();  // default value for type T:
        }
      }
    }

    /*Parameterized constructor
    Creates a grid with R rows and C columns, with grid value initialized to default value of T
    Takes 2 parameters:
      1. R: the number of rows
      2. C: the number of columns*/
    Grid(size_t R, size_t C) {
      Rows = new ROW[R];  //allocates memory for R rows
      NumRows = R;

      // initialize each row to have C columns:
      for (size_t r = 0; r < NumRows; ++r) {
        Rows[r].Cols = new T[C];
        Rows[r].NumCols = C;

        //initialize each grid to default value for type T
        for (size_t c = 0; c < Rows[r].NumCols; ++c) {
          Rows[r].Cols[c] = T(); 
        }

      }

    }

    /*Destructor
    Frees the Rows[] array and each Cols of each element in Rows[]*/
    virtual ~Grid() {

      //iterates through Rows[] and delete each Cols
      for (size_t r = 0; r < NumRows; r++){
        delete[] Rows[r].Cols;
      }

      delete[] Rows;

    }

    /*Copy constructor
    Creates a copy of an exisiting grid
    Takes 1 parameter:
      1. other: the existing grid being copied*/
    Grid(const Grid<T>& other) {

    //copy the row values
    NumRows = other.NumRows;
    Rows = new ROW[NumRows];  

    size_t otherCols = other.Rows[0].NumCols;

    //iterate through each column of other and copy each value 
    for (size_t r = 0; r < NumRows; r++){
      Rows[r].NumCols = otherCols;
      Rows[r].Cols = new T[otherCols];

      for (size_t c = 0; c < otherCols; c++){
        Rows[r].Cols[c] = other.Rows[r].Cols[c];
      }
    }


    }

    /*assignment operator
    Assigns the prexisting grid's values with another prexisiting grid's
    Takes 1 parameter:
      1. other: the Grid object on the RHS of the = operator i.e. this = other
    Return a Grid object*/
    Grid& operator=(const Grid& other) {

      this->~Grid(); //clears the current grid

      //copy the row values
      NumRows = other.NumRows;
      Rows = new ROW[NumRows];  

      size_t otherCols = other.Rows[0].NumCols;

      //iterate through each column of other and copy each value 
      for (size_t r = 0; r < NumRows; r++){
        Rows[r].NumCols = otherCols;
        Rows[r].Cols = new T[otherCols];

      for (size_t c = 0; c < otherCols; c++){
          Rows[r].Cols[c] = other.Rows[r].Cols[c];
        }
      }

      return *this;

    }

    //Function returns the number of rows are in the grid
    size_t numrows() const {
      return NumRows;
    }


    /*Function returns the number of columns in row R
    Takes 1 parameter:
      1. r: the row index*/
    size_t numcols(size_t r) const {

      //checks if the grid has 0 rows
      if (NumRows == 0){return -1;}

      //checks if r is within range
      else if (r < 0 || r > NumRows - 1){return -1;}

      return Rows[r].NumCols;

    }

    /*Function calculates and returns the number of cells in the grid
    by counting how many columns are in each row*/
    size_t size() const {

      size_t gridSize = 0;


      //iterates through each row and sums how many columns there are
      for (size_t r = 0; r < NumRows; r++){
        gridSize += Rows[r].NumCols;
      }

      return gridSize;

    }

    /*() operator returns a reference to the grid cell at (r,c),
    allowing access and assigning to the cell's value
    Takes 2 parameters:
      1. r: the row index
      2. c: the column index*/
    T& operator()(size_t r, size_t c) {

      //checks if r and c are within range, throws exceptions otherwise
      if (r < 0 || r > NumRows - 1){throw invalid_argument("Invalid row index\n");}
      
      if (c < 0 || c > Rows[r].NumCols - 1){throw invalid_argument("Invalid col index\n");}

      return Rows[r].Cols[c];
    }

    /*Function outputs the contents of the grid*/
    void _output() {

      cout << "Grid contents:\n";
      for (size_t r = 0; r < NumRows; r++){

        for (size_t c = 0; c < Rows[r].NumCols; c++){
            cout << "| " << (*this)(r, c) << " ";
          }
          cout << "|\n";
        }

      cout << endl; 

    }

};
