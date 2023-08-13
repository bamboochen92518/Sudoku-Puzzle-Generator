#include <bits/stdc++.h>
#include <cstdio>
#include <string>
using namespace std;

#ifndef PUZZLE
#define PUZZLE
typedef struct _block{
    int row;
    int col;
    int num;
    int possible_array[10];
}block;

typedef struct _puzzle{
    block B[9][9];
    int failed;
}puzzle;

puzzle init_puzzle(){
    puzzle new_puzzle;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            new_puzzle.B[i][j].row = i;
            new_puzzle.B[i][j].col = j;
            new_puzzle.B[i][j].num = 0;
            for(int k = 1; k < 10; k++){
                new_puzzle.B[i][j].possible_array[k] = 1;
            }
        }
    }
    new_puzzle.failed = 0;
    return new_puzzle;
}

void print_puzzle(puzzle p){
    for(int i = 0; i < 9; i++){
        if(i % 3 == 0) cout << "+-----+-----+-----+\n";
        cout << "|";
        for(int j = 0; j < 9; j++){
            cout << p.B[i][j].num;
            if(j % 3 == 2) cout << "|";
            else cout << " ";
        }
        cout << "\n";
    }
    cout << "+-----+-----+-----+\n";
    return;
}

puzzle filled_puzzle(puzzle p, int r, int c, int n){
    if(n == 0) return p;
    if(p.B[r][c].possible_array[n] == 0){
        p.failed = 1;
    }
    // filled number
    p.B[r][c].num = n;
    // modify possible array
    for(int i = 0; i < 9; i++){
        p.B[r][i].possible_array[n] = 0;
        p.B[i][c].possible_array[n] = 0;
    }
    int R = r / 3, C = c / 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            p.B[3 * R + i][3 * C + j].possible_array[n] = 0;
        }
    }
    p.B[r][c].possible_array[n] = 1;
    return p;
}

// mode = 0: ordered, mode = 1: reverse, mode = 2: random
puzzle solve_puzzle(puzzle p, int r, int c, int mode){
    puzzle backup = p;
    vector<int> try_vector;
    if(p.B[r][c].num != 0) try_vector.push_back(p.B[r][c].num);
    else{
        for(int i = 1; i < 10; i++){
            if(p.B[r][c].possible_array[i] == 1) try_vector.push_back(i);
        }
        if(mode == 1) reverse(try_vector.begin(), try_vector.end());
        if(mode == 2){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            shuffle(try_vector.begin(), try_vector.end(), default_random_engine(seed));
        }
    }
    int len = try_vector.size();
    if(len == 0){
        p.failed = 1;
        return p;
    }
    for(int i = 0; i < len; i++){
        p = backup;
        p = filled_puzzle(p, r, c, try_vector[i]);
        if(p.failed == 0){
            int next_r = r, next_c = c;
            if(r == 8 && c == 8) return p;
            else if(c == 8){
                next_r += 1;
                next_c = 0;
            }
            else next_c += 1;
            p = solve_puzzle(p, next_r, next_c, mode);
            if(p.failed == 0) return p;
        }
    }
    p.failed = 1;
    return p;
}

int compare_puzzle(puzzle p1, puzzle p2){
    int re = 1;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(p1.B[i][j].num != p2.B[i][j].num){
                re = 0;
                break;
            }
        }
    }
    return re;
}

int check_solution(puzzle p){ // return 0: no solution, return 1: unique solution, return 2: multiple solution
    puzzle sol = solve_puzzle(p, 0, 0, 0);
    puzzle sol_reverse = solve_puzzle(p, 0, 0, 1);
    if(sol.failed == 1) return 0;
    else if(compare_puzzle(sol, sol_reverse) == 1) return 1;
    else return 2;
}

puzzle add_block(puzzle p, int r, int c, int num){
    p = filled_puzzle(p, r, c, num);
    return p;
}

puzzle remove_block(puzzle p, int r, int c){
    puzzle new_p = init_puzzle();
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(p.B[i][j].num != 0 && !(i == r && j == c)) new_p = filled_puzzle(new_p, i, j, p.B[i][j].num);
        }
    }
    return new_p;
}

puzzle create_puzzle_by_count(puzzle p, puzzle p_sol, int count, vector<pair<int, int>> order, int current_index){
    if(count == 0){
        if(check_solution(p) != 1) p.failed = 1;
        else p.failed = 0;
        return p;
    }
    if(current_index == 81){
        p.failed = 1;
        return p;
    }
    int r = order[current_index].first;
    int c = order[current_index].second;
    p = add_block(p, r, c, p_sol.B[r][c].num);
    p = create_puzzle_by_count(p, p_sol, count - 1, order, current_index + 1);
    if(p.failed == 1){
        p = remove_block(p, r, c);
        p = create_puzzle_by_count(p, p_sol, count, order, current_index + 1);
    }
    return p;
}


#endif
