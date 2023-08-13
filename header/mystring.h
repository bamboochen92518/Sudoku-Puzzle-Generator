#include <bits/stdc++.h>
#include <cstdio>
#include <string>
#include "myerror.h"
using namespace std;

#ifndef MY_STRING
#define MY_STRING
vector<string> split_str(char d, string s){
    vector<string> word_list;
    string tmp = "";
    for(auto x : s){
        if(x == d){
            word_list.push_back(tmp);
            tmp = "";
        }
        else{
            tmp = tmp + x;
        }
    }
    if(tmp != "") word_list.push_back(tmp);
    return word_list;
}

vector<pair<int, int>> turn_string_to_pair(vector<string> cmd, int mode){ // mode = 0: add, remove, mode = 1: swap
    int len = cmd.size();
    vector<pair<int, int>> rc_vector;
    for(int i = 1; i < len; i++){
        if(cmd[i].size() != 2){
            rc_error();
            rc_vector.push_back(make_pair(-1, -1));
            break;
        }
        else{
            if(mode == 0){
                int row = cmd[i][0] - 'a';
                int col = cmd[i][1] - '1';
                if(row < 0 || row > 9 || col < 0 || col > 9){
                    rc_error();
                    rc_vector.push_back(make_pair(-100, -100));
                    break;
                }
                rc_vector.push_back(make_pair(row, col));
            }
            else if(mode == 1){ // row is positive and column is negative
                if(cmd[i][0] >= 'a' && cmd[i][0] <= 'i' && cmd[i][1] >= 'a' && cmd[i][1] <= 'i'){
                    int row1 = cmd[i][0] - 'a';
                    int row2 = cmd[i][1] - 'a';
                    rc_vector.push_back(make_pair(row1, row2));
                }
                else if(cmd[i][0] >= '1' && cmd[i][0] <= '9' && cmd[i][1] >= '1' && cmd[i][1] <= '9'){
                    int col1 = -(cmd[i][0] - '1');
                    int col2 = -(cmd[i][1] - '1');
                    rc_vector.push_back(make_pair(col1, col2));
                }
                else{
                    rc_error();
                    rc_vector.push_back(make_pair(-100, -100));
                    break;
                }
            }
        }
    }
    return rc_vector;
}
#endif
