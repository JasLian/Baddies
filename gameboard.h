/*File contains the GameBoard class that represents the game board.
getHeroPosition(), setHeroPosition(), findHero(), and makeMoves() function written by Jason Liang*/

#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard {
	private: 
	    Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        int HeroRow; // Hero's position row
	    int HeroCol; // Hero's position column
        int numMonsters;
        int numSuperMonsters;
        int numAbysses;
        int numBats;
        bool wonGame; // false, unless the Hero reached the exit successfully

        /*Function detects collisions and out of bounds movements for the Hero
        Try-catch blocks are used to alter movements to avoid collisions into barriers or out of bounds, OR
        to detect when the Hero comes into contact with baddies or holes*/
	void heroCollisionChecking(size_t& newR, size_t& newC, bool& heroRemoved){

            //first out of bounds are checked
            try {
                if (newR < 0 || newR >= numRows) { 
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid row");
                }
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newR = HeroRow;
                cout << "Changing row for Hero position to stay in-bounds\n";
            }

            try {
                if (newC < 0 || newC >= numCols){
                    throw runtime_error("Hero trying to move out-of-bounds with an invalid col");
                }
            }
            catch (runtime_error& excpt){
                cout << excpt.what() << endl;
                newC = HeroCol;
                cout << "Changing column for Hero position to stay in-bounds\n";
            }

            //checks for exit
            try {
                if (board(newR, newC)->isExit()){
                    throw runtime_error("Hero has reached the exit!");
                }
            }
            catch(runtime_error& excpt){
                cout << excpt.what() << endl;
                heroRemoved = true;
                wonGame = true;
                cout << "Hero has escaped!\n";
                return;
            }

            //checks for hole or baddie
            try {
                if (board(newR, newC)->isHole() || board(newR, newC)->isBaddie()){
                    throw runtime_error("Uh Oh! Hero has moved into a Baddie or the Abyss...");
                }
            }   
            catch (runtime_error& excpt){
                heroRemoved = true;
                cout << excpt.what() << endl;
                cout << "Be more careful next time...\n";
                return;
            }

            //checks for barrier
            try {
                if (board(newR, newC)->isBarrier()){
                    throw runtime_error("Hero trying to move into a barrier");
                }
            }
            catch (runtime_error& excpt){
                cout << excpt.what() << endl;

                newC = HeroCol;
                if (board(newR, newC)->isBarrier()){
                    newR = HeroRow;
                }

                cout << "Changing Hero position to stay off barrier\n";
            }

            
        }

        /*Function detects collisions and out of bounds movements for a baddie
        Try-catch blocks are used to alter movements to avoid collisions into barriers or out of bounds, OR
        to detect when the baddie comes into contact with baddies or holes*/
        void baddieCollisionChecking(BoardCell* &baddie, size_t& newR, size_t& newC, bool& heroRemoved, bool& baddieRemoved){

            //first out of bounds are checked
            try {
                if (newR < 0 || newR >= numRows) { 
                    throw runtime_error("Baddie trying to move out-of-bounds with an invalid row");
                }
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                newR = baddie->getRow();
                cout << "Changing row for Baddie position to stay in-bounds\n";
            }

            try {
                if (newC < 0 || newC >= numCols){
                    throw runtime_error("Baddie trying to move out-of-bounds with an invalid col");
                }
            }
            catch (runtime_error& excpt){
                cout << excpt.what() << endl;
                newC = baddie->getCol();
                cout << "Changing column for Baddie position to stay in-bounds\n";
            }

            //checks if the Hero is caught
            try {
                if (board(newR, newC)->isHero()){
                    throw runtime_error("Uh Oh! A Baddie has caught the Hero...");
                }
            }
            catch (runtime_error& excpt){
                cout << excpt.what() << endl;
                cout << "Better luck next time\n";

                heroRemoved = true;
                return;
            }

            //checks for hole
            try {
                if (board(newR, newC)->isHole()){
                    throw runtime_error("Yipee! A Baddie has moved into the Abyss...");
                }
            }
            catch (runtime_error& excpt){
                cout << excpt.what() << endl;
                cout << "One less Baddie on the board!\n";

                baddieRemoved = true;
                return;
            }

            //checks if colliding with another baddie
            try {
                if (board(newR, newC)->isBaddie()){
                    throw runtime_error("Baddie is trying to move onto another Baddie");
                }
            }
            catch (runtime_error& excpt) {
                cout << excpt.what() << endl;
                cout << "Changing Baddie position to stay off other Baddie\n";

                newR = baddie->getRow();
                newC = baddie->getCol();
                return;
            }

            //checks for barrier
            try {
                if (board(newR, newC)->isBarrier()){
                    throw runtime_error("Baddie trying to move into a barrier");
                }
            }
            catch (runtime_error& excpt){
                cout << excpt.what() << endl;

                newC = baddie->getCol();
                if (board(newR, newC)->isBarrier()){
                    newR = baddie->getRow();
                }

                cout << "Changing Baddie position to stay off barrier\n";
            }

            //checks for exit
            try {
                if (board(newR, newC)->isExit()){
                    throw runtime_error("Baddie trying to move onto exit");
                }
            }
            catch (runtime_error& excpt){
                cout << excpt.what() << endl;

                newC = baddie->getCol();
                if (board(newR, newC)->isBarrier() || board(newR, newC)->isExit()){
                    newR = baddie->getRow();
                }

                cout << "Changing Baddie position to stay off exit\n";
            }

        }

	public: 
		/* default constructor */
        GameBoard() {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 50;
            numBats = 2;
            wonGame = false;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* param constructor */
        GameBoard(size_t numRows, size_t numCols) {
            numMonsters = 4;
            numSuperMonsters = 2;
            numAbysses = 20;
            numBats = 3;
            wonGame = false;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* destructor */
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }

        void blankBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col) = new Nothing(row,col);
                }
            }
        }

        char getCellDisplay(size_t r, size_t c) {
            return board(r,c)->display();
        }

        void setCell(BoardCell* myCell, size_t r, size_t c) {
            board(r,c) = myCell;
        }
    
        void freeCell(size_t r, size_t c) {
            delete board(r,c);
        }

        // fills board with by randomly placing...
        //  - Hero (H) in the first three columns
        //  - EscapeLadder (*) in last three columns
        //  - 3 vertical Walls (+), each 1/2 of board height, in middle segment
        //  - Abyss cells (#), quantity set by numAbysses, in middle segment
        //  - Baddies [Monsters (m), Super Monsters (M), & Bats (~)] in middle segment;
        //    number of Baddies set by numMonsters, numSuperMonsters, & numBats
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            r = rand() % numRows;
            c = rand() % 3;
            delete board(r,c);
            board(r,c) = new Hero(r,c);
            HeroRow = r;
            HeroCol = c;

            r = rand() % numRows;
            c = numCols - 1 - (rand() % 3);
            delete board(r,c);
            board(r,c) = new EscapeLadder(r,c);
            
            int sizeMid = numCols - 6;

            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);           
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
            }

            for (int i = 0; i < numMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c);  
                board(r,c)->setPower(1);        
            }

            for (int i = 0; i < numSuperMonsters; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Monster(r,c); 
                board(r,c)->setPower(2);               
            }

            for (int i = 0; i < numBats; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Bat(r,c); 
            }

            for (int i = 0; i < numAbysses; ++i) {
                r = rand() % numRows;
                c = 3 + (rand() % sizeMid);
                while (board(r,c)->display() != ' ') {
                    r = rand() % numRows;
                    c = 3 + (rand() % sizeMid);
                }
                delete board(r,c);
                board(r,c) = new Abyss(r,c);              
            }
        }

        // neatly displaying the game board 
		void display( ) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
        }
		
        bool getWonGame() {
            return wonGame;
        }
        
        // distributing total number of monsters so that 
        //  ~1/3 of num are Super Monsters (M), and
        //  ~2/3 of num are Regular Monsters (m)
        void setNumMonsters(int num) {
            numSuperMonsters = num/3;
            numMonsters = num - numSuperMonsters;
        }

        void setNumAbysses(int num) {
            numAbysses = num;
        }

        void setNumBats(int num) {
            numBats = num;
        }

        size_t getNumRows() {
            return numRows;
        }

        size_t getNumCols() {
            return numCols;
        }

        
        /*Function finds the position of the Hero by assigning the passed by reference
        parameters row and col with the private data members HeroRow and HeroCol*/
        void getHeroPosition(size_t& row, size_t& col) {
            row = HeroRow;
            col = HeroCol;
        }

        /*Function sets the Hero's position by assigning the private data members 
        HeroRow and HeroCol with parameters row and col*/
        void setHeroPosition(size_t row, size_t col) {
            HeroRow = row;
            HeroCol = col;
        }

        /*Function searches the board to find the Hero and sets the position accordingly*/
        void findHero() {
            
            for (size_t r = 0; r < numRows; r++){

                for (size_t c = 0; c < numCols; c++){

                    if (board(r,c)->isHero()){
                        setHeroPosition(r, c);
                        return;
                    }
                }
            }

            setHeroPosition(-1, -1); //if the Hero is not found, set the position to (-1, -1)
    
        }

        /*Function makes moves for the Hero and all the baddies on the board for one single round of the game.
        Parameter HeroNextMove represents the direction the Hero will attempt to move in
        Returns true if Hero is still on board at the end of the round, returns false otherwise*/
        bool makeMoves(char HeroNextMove) {

            //initializes all cell's moved data member to false before any movements happen
            for (size_t r = 0; r < numRows; r++){

                for (size_t c = 0; c < numCols; c++){
                    board(r,c)->setMoved(false);
                }

            }

            size_t newR, newC;

            //suggest a new location the Hero should move to
            board(HeroRow,HeroCol)->setNextMove(HeroNextMove);
            board(HeroRow,HeroCol)->attemptMoveTo(newR,newC,HeroRow,HeroCol);

            bool heroRemoved = false;
            heroCollisionChecking(newR, newC, heroRemoved); //checks for collisions or out of bounds, altering the destination accordingly
            
            //remove the Hero from its current cell
            freeCell(HeroRow, HeroCol);
            Nothing* nothingCell = new Nothing(HeroRow, HeroCol);
            setCell(nothingCell, HeroRow, HeroCol);
            setHeroPosition(newR, newC);

            //end the round immediately if the Hero will be removed from the board
            if (heroRemoved){
                return false;
            }

            //move the Hero to its new cell
            freeCell(newR, newC);
            Hero* heroCell = new Hero(newR, newC);
            heroCell->setMoved(true);
            setCell(heroCell, newR, newC);

            //iterate through the board, moving all baddies in respect to the Hero's position
            for (size_t r = 0; r < numRows; r++){
                for (size_t c = 0; c < numCols; c++){

                    bool baddieRemoved = false;
            
                    if (board(r,c)->isBaddie() && !board(r,c)->getMoved()){ //check if it is a baddie that hasn't been moved

                        //suggest a destintion for the baddie to move to
                        size_t newBadR, newBadC;
                        board(r,c)->attemptMoveTo(newBadR, newBadC, HeroRow, HeroCol);

                        if (newBadR == r && newBadC == c){ //for not moving
                            continue;
                        }
                        
                        baddieCollisionChecking(board(r,c), newBadR, newBadC, heroRemoved, baddieRemoved); //adjusts for collisions or out of bounds

                        if (newBadR == r && newBadC == c){
                            continue;
                        }

                        Nothing* nothingCell = new Nothing(r, c);

                        //when the baddie will be removed
                        if (baddieRemoved){
                            freeCell(r, c);
                            setCell(nothingCell, r, c);
                            continue;
                        }

                        //move the baddie
                        freeCell(newBadR, newBadC);
                        setCell(board(r, c), newBadR, newBadC);
                        board(r,c)->setRow(newBadR);
                        board(r,c)->setCol(newBadC);
                        board(r,c)->setMoved(true);

                        setCell(nothingCell, r, c);
                        
                    }
                }
            }

            return !heroRemoved;

        }

};

#endif //_GAMEBOARD_H
