#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

//  ////////////////////////////////////////initial setup\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void initialiseGrid(int myGrid[4][4]){           //for if the default config is not recognised
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            myGrid[i][j] = 0;
        }
    }
    myGrid[3][3] = 2;
}
void printGrid(const int myGrid[4][4]){          //general print grid function
    for(int i = 0; i < 4; i++){
        for(int j = 0; j <4 ; j++){
            cout << myGrid[i][j] << "\t";
        }
        cout << endl << endl << endl;
    }
}
//  ////////////////////////////////////////game mechanics\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void spawnNumber(int myGrid[4][4]){
    bool zeroPresent = false;                    // initially we assume there are no zeros
    for(int i = 0; i < 4; i++){
        for(int j = 0; j <4 ; j++){              // first we must check if it is possible to print a 0, if there is a free space
            if(myGrid[i][j] == 0){
                zeroPresent = true;              // if a free space is detected, zeroPresent is set to true
            }
        }
    }
    bool isItPrinted = false;                    //loop which is utilised to print a 2 if there is a free space

    if(zeroPresent){
        while(!isItPrinted){
            int i = rand() % 4;
            int j = rand() % 4;

            if(myGrid[i][j] == 0){
                myGrid[i][j] = 2;
                isItPrinted = true;
            }

        }
    }
}
void combineSameUp(int myGrid[4][4]){            //the following void functions are solely for the addition/combination of identical grids
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){

            if((myGrid[j][i] != 0) && (myGrid[j][i] == myGrid[j+1][i])){

                myGrid[j][i] = myGrid[j][i] * 2;
                myGrid[j+1][i] = 0;
            }
        }
    }
}
void combineSameLeft(int myGrid[4][4]){
    for(int j = 0; j < 4; j++){
        for(int i = 0; i < 3; i++){

            if((myGrid[j][i] != 0) && (myGrid[j][i] == myGrid[j][i+1])){

                myGrid[j][i] = myGrid[j][i] * 2;
                myGrid[j][i+1] = 0;
            }
        }
    }
}
void combineSameRight(int myGrid[4][4]){
    for(int j = 0; j < 4; j++){
        for(int i = 3; i > 0; i--){

            if((myGrid[j][i] != 0) && (myGrid[j][i] == myGrid[j][i-1])){

                myGrid[j][i] = myGrid[j][i] * 2;
                myGrid[j][i-1] = 0;
            }
        }
    }
}
void combineSameDown(int myGrid[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 3; j > 0; j--){

            if((myGrid[j][i] != 0) && (myGrid[j-1][i] == myGrid[j][i])){

                myGrid[j][i] = myGrid[j][i] * 2;
                myGrid[j-1][i] = 0;
            }
        }
    }
}
//  ////////////////////////////////////////game controls\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void moveUp(int myGrid[4][4]){

    int rowBelow;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            bool breakloop = false;

            if(myGrid[j][i] == 0){
                for(rowBelow = j + 1; rowBelow < 4 && !breakloop; rowBelow++){
                    if(myGrid[rowBelow][i] != 0){
                        myGrid[j][i] = myGrid[rowBelow][i];
                        myGrid[rowBelow][i] = 0;
                        breakloop = true;
                    }
                }
            }
        }
    }
}
void moveDown(int myGrid[4][4]){

    int rowAbove;

    for(int i = 0; i < 4; i++){
        for(int j = 3; j >= 0; j--){
            bool breakloop = false;

            if(myGrid[j][i] == 0){
                for(rowAbove = j - 1; rowAbove >= 0 && !breakloop; rowAbove--){
                    if(myGrid[rowAbove][i] != 0){
                        myGrid[j][i] = myGrid[rowAbove][i];
                        myGrid[rowAbove][i] = 0;
                        breakloop = true;
                    }
                }
            }
        }
    }
}
void moveRight(int myGrid[4][4]){

    int columnLeft;

    for(int j = 0; j < 4; j++){
        for(int i = 3; i >= 0 ; i--){
            bool breakloop = false;

            if(myGrid[j][i] == 0){
                for(columnLeft = i - 1; (columnLeft >= 0) && !breakloop; columnLeft--){
                    if(myGrid[j][columnLeft] != 0){
                        myGrid[j][i] = myGrid[j][columnLeft];
                        myGrid[j][columnLeft] = 0;
                        breakloop = true;
                    }
                }
            }
        }
    }
}
void moveLeft(int myGrid[4][4]){

    int columnRight;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            bool breakloop = false;

            if(myGrid[i][j] == 0){
                for(columnRight = j + 1; columnRight < 4 && !breakloop; columnRight++){
                    if(myGrid[i][columnRight] != 0){
                        myGrid[i][j] = myGrid[i][columnRight];
                        myGrid[i][columnRight] = 0;
                        breakloop = true;
                    }
                }
            }
        }
    }
}
bool checkIfValid(int myGrid[4][4], string entry){

    int myGridCopy[4][4];                            // making a copy of the grid for comparison purposes
    for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    myGridCopy[i][j] = myGrid[i][j];
                }
        }

    if(entry == "s"){
            moveDown(myGridCopy);
            combineSameDown(myGridCopy);
            moveDown(myGridCopy);
    }
    else if(entry == "w"){
            moveUp(myGridCopy);
            combineSameUp(myGridCopy);
            moveUp(myGridCopy);
    }
    else if(entry == "d"){
            moveRight(myGridCopy);
            combineSameRight(myGridCopy);
            moveRight(myGridCopy);
    }
    else if(entry == "a"){
            moveLeft(myGridCopy);
            combineSameLeft(myGridCopy);
            moveLeft(myGridCopy);
    }
    else if(entry == "restart" || entry == "y" || entry == "n" || entry == "exit"){}
                                                      // performs movement/combination functions on grid copy
    for(int i = 0; i < 4; i++){                       // if the copy is the same as the original grid, the move had no purpose and thus "invalid"
        for(int j = 0; j < 4; j++){
            if(myGridCopy[i][j] != myGrid[i][j]){
                return true;
            }
        }
    }
    return false;
}
bool gameOver(int myGrid[4][4]){

    if(!checkIfValid(myGrid, "w") && !checkIfValid(myGrid, "a") && !checkIfValid(myGrid, "s") && !checkIfValid(myGrid, "d")){
        return true;
    }
    return false;                                      // ends the game when no moves are valid anymore
}
void playGame(string entry, int myGrid[4][4]){
    if(entry == "w"){
            moveUp(myGrid);
            combineSameUp(myGrid);
            moveUp(myGrid);
            spawnNumber(myGrid);
            printGrid(myGrid);
    }
    else if(entry == "s"){                            // movement is followed by combination, in the direction of the move
            moveDown(myGrid);                         // then the "combined" grid is shifted up too so that we don't get zeros
            combineSameDown(myGrid);                  // in the wrong place
            moveDown(myGrid);
            spawnNumber(myGrid);
            printGrid(myGrid);
    }
    else if(entry == "d"){
            moveRight(myGrid);
            combineSameRight(myGrid);
            moveRight(myGrid);
            spawnNumber(myGrid);
            printGrid(myGrid);
    }
    else if(entry == "a"){
            moveLeft(myGrid);
            combineSameLeft(myGrid);
            moveLeft(myGrid);
            spawnNumber(myGrid);
            printGrid(myGrid);
    }
}


int main(){

    int myGrid[4][4];

    ifstream inputconfig;
    string entry;
    string filename;

    cout << "Please enter the name of the file/location of your input configuration: " << endl;
    getline(cin, filename);
    inputconfig.open(filename.c_str());

    if(inputconfig.is_open()){
        cout << "File found! Loading configuration." << endl << endl;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                inputconfig >> myGrid[i][j];
            }
        }
    }
    if(!inputconfig.is_open()){
        cout << "The file can not be found. Using default start configuration." << endl;
        initialiseGrid(myGrid);
    }
    printGrid(myGrid);

    do{
        cin >> entry;
        if(checkIfValid(myGrid, entry)){
            playGame(entry, myGrid);
        }
        if(gameOver(myGrid) || entry == "restart"){
                if(gameOver(myGrid)){
                    cout << "Game over. Play again? y/n" << endl;
                }
                else if(entry == "restart"){
                    cout << "Are you sure?y/n" << endl;
                }
                cin >> entry;
                if(entry == "y"){
                    initialiseGrid(myGrid);
                    printGrid(myGrid);
                }
                else if(entry == "n" & !gameOver(myGrid)){
                	printGrid(myGrid);
                }
                else{
                    entry = "exit";
                }
        }
    }while(entry != "exit");

return 0;
}
