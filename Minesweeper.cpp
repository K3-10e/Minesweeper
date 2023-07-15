#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct tile{
  char letter;
  bool hasmine;
};
struct minesweeper{
  tile board[9][12];
  int width;
  int height;
  int mineCount;
  int flagCount;
  int unrevealedCount;
  int moves;
};
void displayBoard(minesweeper mine_sweeper);
void displayMines(minesweeper mine_sweeper);
bool hasPlayerWon(minesweeper mine_sweeper);

int main(int argc, char* argv[]){
  minesweeper game;
  char option;
  int x=0;
  int y=0;
  bool placemines=true;
  int row=0;
  int col=0;
  int mines=0;
  bool checkAgain=true;
  bool xcheck=true;
  bool ycheck=true;
  bool gameloop=true;
  bool switchloop=true;
  game.moves=1;
  game.flagCount=0;
  game.mineCount=0;
  game.width=12;
  game.height=9;
  game.unrevealedCount=0;

  for(int i=0; i < 9; i++){
    for(int j=0; j < 12; j++){ //boards initialized to false and '?'
      game.board[i][j].hasmine=false;
      game.board[i][j].letter='?';
    }
  }
  if(argc > 1){
    srand(0);
    cout<<endl;
    cout<<"    ****************DEBUG MODE********************"<<endl;
  }
  else
    srand(time(NULL));

  cout<<endl;
  cout<<"               Welcome to MineSweeper!"<<endl;
  cout<<endl;
  
  while(placemines){
    row=(rand()%100); //% is used for remainder of big numbers
    col=(rand()%100);

    if(row < 9 && col < 12)
      game.board[row][col].hasmine=true; //places mines
    for(int i=0; i < 9; i++){
      for(int j=0; j < 12; j++){
		if(game.board[i][j].hasmine == true)
		mines++; //checks how many mines are on the board
      }
    }
    if(mines == 10)
      placemines=false;
    mines=0; //resets mines if it is less than 10
  }

  while(gameloop){
    
    if(argc > 1) //debug mode shows where the mines are
      displayMines(game);
    
    cout<<endl;
    displayBoard(game);
    cout<<endl;
    cout<<"Move #"<<game.moves<<endl;
    
    while(switchloop){
      cout<<endl;
      cout<<"[D/d] - Dig up Tile"<<endl;
      cout<<"[F/f] - Flag/Unflag tiles  "<<game.flagCount<<" flag(s) placed"<<endl;
      cout<<"[Q/q] - Quit"<<endl;
      cout<<endl;
      cout<<"Selection: ";
      cin>>option;
      
      switch(option){
      case 'D':
      case 'd':
		cout<<"   Dig:"<<endl;
		while(xcheck){ //loops until valid x coordinate
		cout<<"   X: ";
		cin>>x;
		if( 1 > x || x > 12)
			cout<<"   Coordinate must be between 1-12, Try Again"<<endl;
		else{
			x--; //decremented for array
			xcheck=false;
		}
		}
		while(ycheck){
		cout<<"   Y: ";
		cin>>y;
		if( 1 > y || y > 9)
			cout<<"   Coordinate must be between 1-9, Try Again"<<endl;
		else{
			y--;
			ycheck=false;
		}
		}

		if(game.board[y][x].letter != 'P'){
		if(game.board[y][x].hasmine == true){
			displayMines(game);
			cout<<"  You hit a mine! Game Over"<<endl;
			cout<<endl;
			return 0;
		}
		game.board[y][x].letter='c';
		}
		else{
			cout<<"  Flag spaces cannot be dug, it must be removed first"<<endl;
		break;
		}
		
		while(checkAgain){
		checkAgain=false;
		for(int i=0; i < 9; i++){
			for(int j=0; j < 12; j++){
				if(game.board[i][j].letter == 'c'){
					if(j > 0){ //checks if left side of c exists
						if(game.board[i][j-1].hasmine == true)
							game.mineCount++;
						if(i > 0) //checks if the top of c exists
							if(game.board[i-1][j-1].hasmine == true)
							game.mineCount++;
						if(i < 8) //checks if the bottom of c exists
							if(game.board[i+1][j-1].hasmine == true)
							game.mineCount++;
					}
					if(j < 11){ //checks if right side of c exists
						if(game.board[i][j+1].hasmine == true)
							game.mineCount++;
						if(i > 0) //copies that above, checks top/bottom
							if(game.board[i-1][j+1].hasmine == true)
							game.mineCount++;
						if(i < 8)
							if(game.board[i+1][j+1].hasmine == true)
							game.mineCount++;
					}
					if(i > 0 && (game.board[i-1][j].hasmine == true)) //checks top
						game.mineCount++;
					if(i < 8 && (game.board[i+1][j].hasmine == true))//checks bottom
						game.mineCount++;
				
					if(game.mineCount == 0){
						if(j > 0){ //copies above if statements, checking sides
							if(game.board[i][j-1].letter == '?')
							game.board[i][j-1].letter='c';
							if(i > 0 && (game.board[i-1][j-1].letter == '?'))
							game.board[i-1][j-1].letter='c';
							if(i < 8 && (game.board[i+1][j-1].letter == '?'))
							game.board[i+1][j-1].letter='c';
						}
						if(j < 11){
							if(game.board[i][j+1].letter == '?')
							game.board[i][j+1].letter='c';
							if(i > 0 && (game.board[i-1][j+1].letter == '?'))
							game.board[i-1][j+1].letter='c';
							if(i < 8 && (game.board[i+1][j+1].letter == '?'))
							game.board[i+1][j+1].letter='c';
						}
						if(i > 0 && (game.board[i-1][j].letter == '?'))
							game.board[i-1][j].letter='c';
						if(i < 8 && (game.board[i+1][j].letter == '?'))
							game.board[i+1][j].letter='c';
						game.board[i][j].letter=' ';
						checkAgain=true;
					}
					else
						game.board[i][j].letter=('0'+game.mineCount); //outputs number at c
				}
				game.mineCount=0; //resets for when other locations are set to c
			}
		}
		}
		if(hasPlayerWon(game) == true){//outputs "YOU WON" big
		cout<<"      _________________________________________"<<endl;
		cout<<"     *                                         *"<<endl;
		cout<<"     * "<<'\\'<<"   / _      "<<'\\'
			<<"            /  _        | *"<<endl;
		cout<<"     *  "<<'\\'<<" / | | | |  "<<'\\'<<"    /"<<'\\'
			<<"    /  | | |"<<'\\'<<"  | | *"<<endl;
		cout<<"     *   |  | | | |   "<<'\\'<<"  /  "<<'\\'<<"  /   | | | "
			<<'\\'<<" | | *"<<endl;
		cout<<"     *   |  |_| |_|    "<<'\\'<<"/    "<<'\\'<<"/    |_| |  "
			<<'\\'<<"| o *"<<endl;
		cout<<"     *_________________________________________*"<<endl;
		cout<<endl;
		cout<<"      You won in "<<game.moves<<" moves!"<<endl;
		cout<<endl;
		gameloop=false;
		}
		//resets variables to check them in next loop
		game.moves++;
		checkAgain=true;
		switchloop=false;
		break;
      case 'F':
      case 'f':
	cout<<"   Place flag at: "<<endl;
		while(xcheck){ //loops until valid x coordinate
		cout<<"   X: ";
		cin>>x;
		if( 1 > x || x > 12)
			cout<<"   Coordinate must be between 1-12, Try Again"<<endl;
		else{
			x--; //decremented for array
			xcheck=false;
		}
		}
		while(ycheck){
		cout<<"   Y: ";
		cin>>y;
		if( 1 > y || y > 9)
			cout<<"   Coordinate must be between 1-9, Try Again"<<endl;
		else{
			y--;
			ycheck=false;
		}
		}
	
		if(game.board[y][x].letter == 'P'){
			game.board[y][x].letter='?';
			game.flagCount--; //changes flag to '?'
		}
		else{
			if(game.board[y][x].letter == '?'){
				game.board[y][x].letter= 'P';
				game.flagCount++; //changes '?' to flag
			}
		}
		if(argc > 1) //mine locations displayed again after placing flag
			displayMines(game);
		displayBoard(game);
		break;
	case 'Q':
	case 'q':
		cout<<"Quitting.... Thanks for playing!"<<endl;
		return 0;
	default:
		cin.ignore(50, '\n');
		cout<<" Invalid input, try again"<<endl;
	}
	xcheck=true;
	ycheck=true;
	}
	switchloop=true;
  }
}

/*displayBoard: Function displays the game board
parameters: char array, ints of the width and height
return value: function does not return anything*/  
void displayBoard(minesweeper mine_sweeper){
  cout<<"    1   2   3   4   5   6   7   8   9  10  11  12"<<endl;
  for(int i=0; i < mine_sweeper.height; i++){
    cout<<"  +---+---+---+---+---+---+---+---+---+---+---+---+"<<endl;
    cout<<i+1<<" | ";
    for(int j=0; j < mine_sweeper.width; j++){
      cout<<mine_sweeper.board[i][j].letter<<" | ";
    }
    cout<<endl;
  }
  cout<<"  +---+---+---+---+---+---+---+---+---+---+---+---+"<<endl;
}

/*displayMines: If player loses, the mine locations are displayed
parameters: bool array, ints of the width and height
return value: function does not return anything*/
void displayMines(minesweeper mine_sweeper){
  cout<<endl;
  cout<<"    1   2   3   4   5   6   7   8   9  10  11  12"<<endl;
  for(int i=0; i < mine_sweeper.height; i++){
    cout<<"  +---+---+---+---+---+---+---+---+---+---+---+---+"<<endl;
    cout<<i+1<<" | ";
    for(int j=0; j < mine_sweeper.width; j++){
		if(mine_sweeper.board[i][j].hasmine == false)
			cout<<" ";
		else
			cout<<"*";
		cout<<" | ";
    }
    cout<<endl;
  }
  cout<<"  +---+---+---+---+---+---+---+---+---+---+---+---+"<<endl;
  cout<<endl;
}

/*hasPlayerWon: Checks if the player has won the game
parameters: char and bool array, ints of the width and height
return value: true if the mine amount matches the '?' amount
              false otherwise*/
bool hasPlayerWon(minesweeper mine_sweeper){
  
  for(int i=0; i < mine_sweeper.height; i++){
    for(int j=0; j < mine_sweeper.width; j++){
      if(mine_sweeper.board[i][j].letter == '?' ||
	 mine_sweeper.board[i][j].letter == 'P')
		mine_sweeper.unrevealedCount++; //counts the amount of '?'
      if(mine_sweeper.board[i][j].hasmine == true)
		mine_sweeper.mineCount++; //counts the amount of mines
    }
  }
  if(mine_sweeper.unrevealedCount == mine_sweeper.mineCount)
    return true;
  
  mine_sweeper.mineCount=0; //resets variables
  mine_sweeper.unrevealedCount=0;
  return false;
}
