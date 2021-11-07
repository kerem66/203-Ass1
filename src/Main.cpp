#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
void placeBombAndCalculate(int **array,int row, int column, int* total, int size){
    int tempTotal = 0; // we will sum the values on each bomb and add it to total
    int bombValue = (array[row][column]); // we will check equality based on this value
    if(bombValue == 0){ // bombed cell is 0, no action needed
        return;
    }else{ // cell value is different then 0 ,we will check all directions
        int tempRow = row;
        int tempColumn = column;
        tempTotal+= bombValue;
        array[row][column] = 0;
        for(int i = row-1 , j = column-1; i>=0 && j>=0 ; j--, i--){ // left upper diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = row+1, j = column+1; j<size && i<size ; j++, i++){ // right down diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = row-1, j = column+1 ; j<size && i>=0 ; i-- , j++){ // right upper diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = row+1, j = column-1 ; j>=0 && i<size ; i++ , j--){ // left down diagonal
            if(array[i][j] == bombValue){
                tempTotal+= bombValue;
                array[i][j] = 0;
            }
        }
        for(int i = column-1 ; i>= 0 ; i--){ // left direction
            if(array[row][i] == bombValue){
                tempTotal+= bombValue;
                array[row][i] = 0;
            }
        }
        for(int i = column+1 ; i<size ; i++){ // right direction
            if(array[row][i] == bombValue){
                tempTotal+= bombValue;
                array[row][i] = 0;
            }
        }
        for(int i = row-1 ; i>=0 ; i--){ // upper direction
            if(array[i][column] == bombValue){
                tempTotal+= bombValue;
                array[i][column] = 0;
            }
        }
        for(int i = row+1 ; i<size ; i++){ // down direction
            if(array[i][column] == bombValue){
                tempTotal+= bombValue;
                array[i][column] = 0;
            }
        }

    }
    *total += tempTotal; // adding bombed total to main total
}
void secondPart(string fileName, string outputFile){
    ifstream file(fileName);
    if(!file) {
        cout << "Cannot open input file.\n";
        exit(1);
    }
    string str;
    int size = 0;
    int count = 0;
    int total = 0;
    if (getline(file, str)){ //reading first line and getting size
        size = stoi(str);
    }
    int** array = new int*[size];
    for(int i = 0 ; i<size ; i++){ //creating 2d array
        array[i] = new int[size];
    }
    for(int i = 0 ; i<size ; i++){ // initalizing array with -1 as empty values
        for(int j = 0 ; j<size ; j++){
            array[i][j] = -1;
        }
    }
    while (getline(file, str)) {
        if(size != 0 && count<size){
            // creating array here
            int tempCount = 0;
            stringstream ss(str);
            string word;
            while (ss >> word) {
                array[count][tempCount] = stoi(word); //initializing array here, count holds row value, tempCount holds column value
                tempCount++;
            }
            count++;
        }else{
            //placing bombs from here
            stringstream ss(str);
            string word;
            int row = -1;
            int column = -1;
            while (ss >> word) { //reading row, column values
                if(row!= -1){
                    column = stoi(word);
                }else{
                    row = stoi(word);
                }
            }
            placeBombAndCalculate(array,row,column,&total,size);
        }
    }
    file.close();

    fstream outputfile;
    outputfile.open(outputFile, std::ios_base::app | std::ios_base::in | std::ios_base::out);
    if (outputfile.is_open()){ // writing to file
        outputfile<< "PART 2:\n";
        for(int i = 0 ; i<size ; i++){
            for(int j = 0 ; j<size ; j++){
                if(j==size-1){
                    outputfile<<array[i][j];
                }else{
                    outputfile<<array[i][j] << " ";
                }
            }
            outputfile << "\n";
        }
        outputfile << "Final Point: " << total<<"p";
    }else{
        cout<< "cannot open file to write";
    }
    outputfile.close();
    for(int i = 0 ; i<size ; i++){ // deleting allocated memory for array
        delete[] array[i];
    }
}
bool checkLeft(int **array, int row , int column, int value, int size){
    bool found = false;
    if(column-1>=0){
        if(array[row][column-1] == value){
            found = true;
        }
    }
    return found;
}
bool checkRight(int **array, int row , int column, int value, int size){
    bool found = false;
    if(column+1<size){
        if(array[row][column+1] == value){
            found = true;
        }
    }
    return found;
}
bool checkBottom(int **array, int row , int column, int value, int size){
    bool found = false;
    if(row+1<size){
        if(array[row+1][column] == value){
            found = true;
        }
    }
    return found;
}
bool checkUp(int **array, int row , int column, int value, int size){
    bool found = false;
    if(row-1>=0){
        if(array[row-1][column] == value){
            found = true;
        }
    }
    return found;
}
void placeValues (int** array, int row , int column, int value , int size){
    array[row][column] = value; //inserting new value to location

    int foundSameValues = 0;
    bool isMainUp = false; // i will use these boolean values if 3 values are connected with each other on the newly added node, in that case function is not entering
    bool isMainDown = false; // to inner functions because of that values are not changing
    bool isMainLeft = false;
    bool isMainRight = false;
    // from there i am checking 4 direction for newly added value, whenever i find same value in one of the directions, i am checking 4 direction of found spot,
    // if i found on inner part i am changing them to 0, also counting the how many same values i found, since i might not found on the second search( inner 4 direction)
    // i am checking if foundSameValues are greater than 2, because i have the same value on newly added spot and that makes 3, i am doing the operation if i found
    // same value on first 4 direction search and equaling them to 0  then increasing the newly added value and sending it back to function again.
    if(checkUp(array,row,column,value,size)){
        isMainUp = true;
        foundSameValues++;
        if(checkUp(array,row-1,column,value,size) || checkRight(array,row-1,column,value,size) || checkLeft(array,row-1,column,value,size)){
            if(checkLeft(array,row-1,column,value,size)){
                array[row-1][column]=0;
                array[row-1][column-1]=0;
            }
            if(checkRight(array,row-1,column,value,size)){
                array[row-1][column]=0;
                array[row-1][column+1]=0;
            }
            if(checkUp(array,row-1,column,value,size)){
                array[row-1][column]=0;
                array[row-2][column]=0;
            }
            foundSameValues++;
        }
    }
    if(checkBottom(array,row,column,value,size)){
        isMainDown = true;
        foundSameValues++;
        if(checkBottom(array,row+1,column,value,size) || checkRight(array,row+1,column,value,size) || checkLeft(array,row+1,column,value,size)){
            if(checkLeft(array,row+1,column,value,size)){
                array[row+1][column]=0;
                array[row+1][column-1]=0;
            }
            if(checkRight(array,row+1,column,value,size)){
                array[row+1][column]=0;
                array[row+1][column+1]=0;
            }
            if(checkBottom(array,row+1,column,value,size)){
                array[row+1][column]=0;
                array[row+2][column]=0;
            }
            foundSameValues++;
        }
    }
    if(checkRight(array,row,column,value,size)){
        isMainRight = true;
        foundSameValues++;
        if(checkUp(array,row,column+1,value,size) || checkBottom(array,row,column+1,value,size) || checkRight(array,row,column+1,value,size) ){
            if(checkUp(array,row,column+1,value,size)){
                array[row][column+1]=0;
                array[row-1][column+1]=0;
            }
            if(checkRight(array,row,column+1,value,size)){
                array[row][column+1]=0;
                array[row][column+2]=0;
            }
            if(checkBottom(array,row,column+1,value,size)){
                array[row][column+1]=0;
                array[row+1][column+1]=0;
            }
            foundSameValues++;
        }
    }
    if(checkLeft(array,row,column,value,size)){
        isMainLeft = true;
        foundSameValues++;
        if(checkUp(array,row,column-1,value,size) || checkBottom(array,row,column-1,value,size) ||  checkLeft(array,row,column-1,value,size)){
            if(checkUp(array,row,column-1,value,size)){
                array[row][column-1]=0;
                array[row-1][column-1]=0;
            }
            if(checkLeft(array,row,column-1,value,size)){
                array[row][column-1]=0;
                array[row][column-2]=0;
            }
            if(checkBottom(array,row,column-1,value,size)){
                array[row][column-1]=0;
                array[row+1][column-1]=0;
            }
            foundSameValues++;
        }
    }
    if(foundSameValues >=2){
        if(isMainLeft){
            array[row][column-1] = 0;
        }
        if(isMainRight){
            array[row][column+1] = 0;
        }
        if(isMainDown){
            array[row+1][column] = 0;
        }
        if(isMainUp){
            array[row-1][column] = 0;
        }
        placeValues(array,row,column,value+1,size);
    }
}
void firstPart(string filename, string outputFile){
    ifstream file(filename);
    if(!file) {
        cout << "Cannot open input file.\n";
        exit(1);
    }
    string str;
    int size = 0;
    if (getline(file, str)){ // getting first line as size
        size = stoi(str);
    }
    int** array = new int*[size];
    for(int i = 0 ; i<size ; i++){ //creating 2d array
        array[i] = new int[size];
    }
    for(int i = 0 ; i<size ; i++){ // initalizing array with -1 as empty values
        for(int j = 0 ; j<size ; j++){
            array[i][j] = 0;
        }
    }
    while (getline(file, str)) {
            stringstream ss(str);
            string word;
            int row = -1;
            int column = -1;
            int value = -1;
            while (ss >> word) {
                if(value != -1){ // reading row, column and values
                    if(row!= -1){
                        column = stoi(word);
                    }else{
                        row = stoi(word);
                    }
                }else{
                    value = stoi(word);
                }
            }
            placeValues(array, row, column, value, size);
        
    }
    file.close();
    fstream outputfile;
    outputfile.open(outputFile, std::ios_base::app | std::ios_base::in | std::ios_base::out);
    if (outputfile.is_open()){ // writing to file
        outputfile<< "PART 1:\n";
        for(int i = 0 ; i<size ; i++){
            for(int j = 0 ; j<size ; j++){
                if(j==size-1){
                    outputfile<<array[i][j];
                }else{
                    outputfile<<array[i][j] << " ";
                }

            }
            outputfile << "\n";
        }
    }else{
        cout<< "cannot open file to write";
    }
    outputfile << "\n";
    outputfile.close();
    for(int i = 0 ; i<size ; i++){ //  freeing allocated memory for array
        delete[] array[i];
    }
}
int main(int argc, char **argv) {
    remove(argv[3]); // since i am appending to file, i am removing the output file here to get rid of writing every output to same file.
    firstPart(argv[1],argv[3]);
    secondPart(argv[2],argv[3]);
    return 0;
}
