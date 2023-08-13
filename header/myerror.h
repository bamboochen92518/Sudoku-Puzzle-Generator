#include <bits/stdc++.h>
using namespace std;

#ifndef MY_ERROR
#define MY_ERROR
void argument_error(){
    cout << "Error: The number of argument is wrong. Please try again. \n\n";
    return;
}

void command_not_found_error(){
    cout << "Error: Command not found. Please try again. \n\n";
    return;
}

void file_error(){
    cout << "Error: Failed to open file. \n\n";
}

void format_error(){
    cout << "Error: The format of the puzzle or pattern is wrong. \n\n";
}

void digit_error(){
    cout << "Error: Digits in the puzzle can only be 0 to 9. \n\n";
}

void save_error(){
    cout << "Error: There are no puzzle to save. You may need to create or load a puzzle first. \n\n";
}

void rc_error(){
    cout << "Error: row and column is wrong. the range of row is 'a' to 'i', and the range of colummn is '1' to '9'. \nExample: a1, b5, c8, .... \n";
}

void attempt_error(){
    cout << "Error: Attept more than 1000 times, please try again, increase count number, or change pattern. \n\n";
}

#endif
