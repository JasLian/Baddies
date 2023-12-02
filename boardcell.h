/*File contains the Boardcell class and all its derived classes.
attemptMoveTo() function written by Jason Liang*/

#ifndef _BOARDCELL_H
#define _BOARDCELL_H

using namespace std;

// First, the BoardCell abstract base class 

class BoardCell {
	
    public:  
		BoardCell() {} // default contstructor (do nothing)
        virtual ~BoardCell() {} // destructor (do nothing)
        
        virtual char display( ) = 0; // pure virtual function; this is an abstract base class

        //Default attemptMoveTo() functions for the BoardCell class, overridden in derived classes
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            newR = myRow;
            newC = myCol;
        }
        
        virtual bool isHero( ) {return false;}
    	virtual bool isBaddie( ) {return false;}
    	virtual bool isSpace( ) {return false;}
        virtual bool isBarrier( ) {return false;}
        virtual bool isHole( ) {return false;}
    	virtual bool isExit( ) {return false;}
    	virtual bool isStatic( ) {return true;}

        virtual void setPower(int num) {}
        virtual int getPower() {return 1;}
        virtual void setNextMove(char inChar) {}
        
        void setMoved(bool m) {moved = m;}
        bool getMoved() {return moved;}
        void setRow(size_t r) {myRow = r;}
        size_t getRow() {return myRow;}
        void setCol(size_t c) {myCol = c;}
        size_t getCol() {return myCol;}
        void setPos(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

    private:
        size_t myRow; // current row for this board cell in a 2D grid
        size_t myCol; // current column for this board cell in a 2D grid
        bool moved;   // true = this board cell already moved in the current round

}; // BoardCell (abstract base class)


// Then, all the derived classes

class Hero: public BoardCell {
	
    public:
    	Hero(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        
        virtual bool isHero( ) {return true;}
        virtual bool isStatic( ) {return false;}
        virtual char display( ) {return 'H';}
        
        virtual void setNextMove(char inChar ) {
            nextMove = inChar;
        }
    	
        /*Function proposes a move for the Hero to make by assigning the 
        passed by reference parameters newR and newC based on the nextMove data member*/
        virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            
            switch(nextMove){

                //up and left
                case 'q':
                    newR = hRow - 1;
                    newC = hCol - 1;
                    break;
                
                //up
                case 'w':
                    newR = hRow - 1;
                    newC = hCol;
                    break;

                //up and right
                case 'e':
                    newR = hRow - 1;
                    newC = hCol + 1;
                    break;

                //left
                case 'a':
                    newR = hRow;
                    newC = hCol - 1;
                    break;

                //right
                case 'd':
                    newR = hRow;
                    newC = hCol + 1;
                    break;

                //down and right
                case 'z':
                    newR = hRow + 1;
                    newC = hCol - 1;
                    break;

                //down
                case 'x':
                    newR = hRow + 1;
                    newC = hCol;
                    break;

                //down and right
                case 'c':
                    newR = hRow + 1;
                    newC = hCol + 1;
                    break;

                //stay in place
                case 's':
                default:
                    newR = hRow;
                    newC = hCol;
                    break;
                
            }
        }

    private:
        char nextMove;

}; // Hero


class Monster: public BoardCell {
    
    public:
		Monster(size_t r, size_t c) {
            setRow(r);
            setCol(c);
            power = 1;
        }
        
        virtual bool isBaddie( ) {return true;}
        virtual bool isStatic( ) {return false;}
        
        virtual char display( ) {
            if (power == 2) {
                return 'M'; // Super Monster
            } else {
                return 'm'; // Monster
            } 
        }

        virtual void setPower(int num) {
            power = num;
        }

        virtual int getPower() {
            return power;
        }
        
        /*Function proposes a move for the Monster to make by assigning the 
        passed by reference parameters newR and newC based on the Hero's position*/
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            
            //always attempt to move to the same row and coloumn as the Hero
            if (this->getRow() == hRow){
                newR = this->getRow();
            }
            else{
                
                if (this->getRow() < hRow){
                    newR = this->getRow() + power;
                }
                else{
                    newR = this->getRow() - power; 
                }
            }

            if (this->getCol() == hCol){
                newC = this->getCol();
            }
            else{
                
                if (this->getCol() < hCol){
                    newC = this->getCol() + power;
                }
                else{
                    newC = this->getCol() - power; 
                }
            }


        }
    
    private:
        int power; // power = 1 for Monster, power = 2 for SuperMonster

}; // Monster

class Bat: public BoardCell {
    public:
		Bat(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual bool isBaddie( ) {return true;}
        virtual bool isStatic( ) {return false;}
        virtual char display( ) {return '~';}
        
        /*Function proposes a move for the Bat to make by assigning the 
        passed by reference parameters newR and newC based on the Hero's position*/
    	virtual void attemptMoveTo(size_t& newR, size_t& newC, size_t hRow, size_t hCol) {
            
            //Bat will always attempt to navigate to the Hero's column, but cannot change rows;
            newR = this->getRow();
            newC = hCol;

        }

}; // Bat


class Abyss: public BoardCell {
	public:
    	Abyss(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '#';}
        virtual bool isHole( ) {return true;}
}; // Abyss


class Wall: public BoardCell {
	public:
    	Wall(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '+';}
    	virtual bool isBarrier( ) {return true;}
}; // Wall


class Nothing: public BoardCell {
	public:
    	Nothing(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return ' ';}
    	virtual bool isSpace( ) {return true;}
}; // Nothing


class EscapeLadder: public BoardCell {
	public:
    	EscapeLadder(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }
        virtual char display( ) {return '*';}
    	virtual bool isExit( ) {return true;}
}; // EscapeLadder


#endif //_BOARDCELL_H
