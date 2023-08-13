#include <bits/stdc++.h>
#include "puzzle.h"
#include "help.h"
#include "mystring.h"
#include <cstdio>
#include <string>
#include <ctime>
using namespace std;

#ifndef MY_FILE
#define MY_FILE

puzzle read_puzzle(string filename){
    puzzle empty_puzzle = init_puzzle();
    ifstream file(filename);
    if(!file.is_open()){
        file_error();
        empty_puzzle.failed = 1;
    }
    else{
        string line;
        int row = 0;
        while(getline(file, line)){
            vector<string> digit = split_str(' ', line);
            if(digit.size() != 9){
                format_error();
                empty_puzzle.failed = 1;
                break;
            }
            for(int i = 0; i < 9; i++){
                int d = stoi(digit[i]);
                if(d < 0 || d > 9){
                    digit_error();
                    empty_puzzle.failed = 1;
                    break;
                }
                if(d != 0) empty_puzzle = filled_puzzle(empty_puzzle, row, i, d);
            }
            row += 1;
            if(row == 9) break;
        }
        file.close();
    }
    return empty_puzzle;
}

int save_puzzle(string filename, puzzle p){
    ofstream outdata;
    outdata.open(filename);
    if(!outdata){
        file_error();
        return 0;
    }
    else{
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                outdata << p.B[i][j].num << " ";
            }
            outdata << "\n";
        }
        outdata.close();
    }
    return 1;
}

string get_filename(){
    char tmp_f[128] = {0};
    time_t now = time(0);
    tm *ltm = localtime(&now);
    sprintf(tmp_f, "%d-%d-%d_%d:%d:%d_puzzle", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    string filename = tmp_f;
    return filename;
}

vector<pair<int, int>> read_pattern(string filename){
    vector<pair<int, int>> rc;
    ifstream file(filename);
    if(!file.is_open()){
        file_error();
        rc.push_back(make_pair(-100, -100));
    }
    else{
        string line;
        int row = 0;
        while(getline(file, line)){
            vector<string> digit = split_str(' ', line);
            if(digit.size() != 9){
                format_error();
                rc.push_back(make_pair(-100, -100));
                break;
            }
            for(int i = 0; i < 9; i++){
                int d = stoi(digit[i]);
                if(d != 0) rc.push_back(make_pair(row, i));
            }
            row += 1;
            if(row == 9) break;
        }
        file.close();
    }
    return rc;
}

#endif
