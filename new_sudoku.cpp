#include <bits/stdc++.h>
#include "./header/myfile.h"
#include "./header/myerror.h"
#include "./header/mystring.h"
#include "./header/puzzle.h"
#include "./header/help.h"
#include <cstdio>
#include <string>
#include <ctime>
using namespace std;

vector<string> read_cmd(){
    string line;
    cerr << ">>> ";
    line = "\n";
    getline(cin, line);
    cout << "\n";
    vector<string> cmd = split_str(' ', line);
    return cmd;
}

puzzle CMD_create(){
    puzzle p = init_puzzle();
    p = solve_puzzle(p, 0, 0, 2);
    print_puzzle(p);
    return p;
}

puzzle CMD_create_c(int count){
    int success = 0, r, c, counter = 0;
    puzzle p, new_p, sol, sol_reverse;
    vector<pair<int, int>> random_order;
    unsigned seed;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            random_order.push_back(make_pair(i, j));
        }
    }
    while(success == 0){
        counter += 1;
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        shuffle(random_order.begin(), random_order.end(), default_random_engine(seed));
        p = init_puzzle();
        p = solve_puzzle(p, 0, 0, 2);
        p = create_puzzle_by_count(init_puzzle(), p, count, random_order, 0);
        if(p.failed == 0) success = 1;
        if(counter == 10){
            attempt_error();
            break;
        }
    }
    if(success) print_puzzle(p);
    return p;
}

puzzle CMD_create_p(string filename){
    puzzle p, p_sol;
    vector<pair<int, int>> rc = read_pattern(filename);
    int rc_size = rc.size(), r, c, success = 0, counter = 0;
    if(rc[0].first != -100){
        while(!success){
            p = init_puzzle();
            p_sol = solve_puzzle(p, 0, 0, 2);
            for(int i = 0; i < rc_size; i++){
                r = rc[i].first;
                c = rc[i].second;
                p = filled_puzzle(p, r, c, p_sol.B[r][c].num);
            }
            if(check_solution(p) == 1) success = 1;
            else counter += 1;
            if(counter == 1000){
                attempt_error();
                break;
            }
        }
        if(success) print_puzzle(p);
    }
    return p;
}

puzzle CMD_load(string filename){
    puzzle p = read_puzzle(filename);
    if(p.failed == 0){
        print_puzzle(p);
        cout << "\nFinish. \n";
    }
    return p;
}

puzzle CMD_solve(puzzle p, int mode){ // mode = 1: print solution, mode = 2: silent 
    puzzle sol = solve_puzzle(p, 0, 0, 0);
    puzzle sol_reverse = solve_puzzle(p, 0, 0, 1);

    if(sol.failed == 1){
        if(mode != 2) cout << "There are NO solution. \n";
    }

    else if(compare_puzzle(sol, sol_reverse)){
        if(mode != 2) cout << "There exist unique solution. \n";
        if(mode == 1) print_puzzle(sol);
    }

    else{
        if(mode != 2) cout << "There exist more than one solutions. \n";
        if(mode == 1){
            cout << "A: \n";
            print_puzzle(sol);
            cout << "B: \n";
            print_puzzle(sol_reverse);
        }
    }
    return sol;
}

void CMD_save(string filename, puzzle p){
    if(p.failed == 0){
        int re = save_puzzle(filename, p);
        if(re == 1){
            cout << "Finish! Save the file as " << filename << ". \n";
        }
    }
    else save_error();
    return;
}

puzzle CMD_add(puzzle p, puzzle p_sol, vector<pair<int, int>> rc){
    int rc_size = rc.size(), r, c;
    if(rc[rc_size - 1].first != -100){
        for(int i = 0; i < rc_size; i++){
            r = rc[i].first;
            c = rc[i].second;
            p = add_block(p, r, c, p_sol.B[r][c].num);
        }
        cout << "Finish! \n";
        print_puzzle(p);
        CMD_solve(p, 0);
    }
    return p;
}

puzzle CMD_remove(puzzle p, vector<pair<int, int>> rc){
    int rc_size = rc.size();
    if(rc[rc_size - 1].first != -100){
        for(int i = 0; i < rc_size; i++) p = remove_block(p, rc[i].first, rc[i].second);
        cout << "Finish! \n";
        print_puzzle(p);
        CMD_solve(p, 0);
    }
    return p;
}

puzzle CMD_swap(puzzle p, vector<pair<int, int>> rc){
    int rc_size = rc.size();
    if(rc[rc_size - 1].first != -100){
        puzzle new_p;
        int row = 1; // swap row = 1, swap column = 0
        for(int i = 0; i < rc_size; i++){
            new_p = init_puzzle();
            if(rc[i].first >= 0 && rc[i].second >= 0) row = 1;
            else row = 0;
            for(int j = 0; j < 9; j++){
                for(int k = 0; k < 9; k++){
                    // swap column
                    if(row == 0 && k == -rc[i].first) new_p = filled_puzzle(new_p, j, -rc[i].second, p.B[j][k].num);
                    else if(row == 0 && k == -rc[i].second) new_p = filled_puzzle(new_p, j, -rc[i].first, p.B[j][k].num);
                    // swap row
                    else if(row == 1 && j == rc[i].first) new_p = filled_puzzle(new_p, rc[i].second, k, p.B[j][k].num);
                    else if(row == 1 && j == rc[i].second) new_p = filled_puzzle(new_p, rc[i].first, k, p.B[j][k].num);
                    // other
                    else new_p = filled_puzzle(new_p, j, k, p.B[j][k].num);
                }
            }
            p = new_p;
        }
        cout << "Finish! \n";
        print_puzzle(p);
    }
    return p;
}

int CMD_count(puzzle p){
    int count = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(p.B[i][j].num != 0) count += 1;
        }
    }
    return count;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    init_cmd_map();
    puzzle current_puzzle = init_puzzle();
    puzzle current_solution;
    vector<pair<puzzle, puzzle>> current_status;

    cout << "What you want to do?\n";
    help("summary");
    
    int exit_code = 0;
    while(exit_code == 0){
        vector<string> cmd = read_cmd();
        int len = cmd.size();
        if(cmd[0] == "create"){
            if(len == 1){
                current_puzzle = CMD_create();
                current_solution = current_puzzle;
                current_status.push_back(make_pair(current_puzzle, current_solution));
            }
            else if(len == 3){
                if(cmd[1] == "-c" && stoi(cmd[2])){
                    current_puzzle = CMD_create_c(stoi(cmd[2]));
                    current_solution = CMD_solve(current_puzzle, 2);
                    current_status.push_back(make_pair(current_puzzle, current_solution));
                }
                else if(cmd[1] == "-p"){
                    current_puzzle = CMD_create_p(cmd[2]);
                    current_solution = CMD_solve(current_puzzle, 2);
                    current_status.push_back(make_pair(current_puzzle, current_solution));
                }
                else argument_error();
            }
            else argument_error();
        }
        else if(cmd[0] == "load"){
            if(len == 2){
                current_puzzle = CMD_load(cmd[1]);
                current_solution = CMD_solve(current_puzzle, 0);
                current_status.push_back(make_pair(current_puzzle, current_solution));
            }
            else argument_error();
        }
        else if(cmd[0] == "help"){
            if(len == 1) help("summary");
            else if(len == 2) help(cmd[1]);
            else argument_error();
        }
        else if(cmd[0] == "save"){
            if(len == 1) CMD_save(get_filename(), current_puzzle);
            else if(len == 2) CMD_save(cmd[1], current_puzzle);
            else argument_error();
        }
        else if(cmd[0] == "exit"){
            exit_code = 1;
            break;
        }
        else if(cmd[0] == "add"){
            if(len == 1) argument_error();
            else{
                vector<pair<int, int>> rc_vec = turn_string_to_pair(cmd, 0);
                current_puzzle = CMD_add(current_puzzle, current_solution, rc_vec);
                current_status.push_back(make_pair(current_puzzle, current_solution));
            } 
        }
        else if(cmd[0] == "remove"){
            if(len == 1) argument_error();
            else{
                vector<pair<int, int>> rc_vec = turn_string_to_pair(cmd, 0);
                current_puzzle = CMD_remove(current_puzzle, rc_vec);
                current_status.push_back(make_pair(current_puzzle, current_solution));
            } 
        }
        else if(cmd[0] == "swap"){
            if(len == 1) argument_error();
            else{
                vector<pair<int, int>> rc_vec = turn_string_to_pair(cmd, 1);
                current_puzzle = CMD_swap(current_puzzle, rc_vec);
                current_solution = CMD_solve(current_puzzle, 0);
                current_status.push_back(make_pair(current_puzzle, current_solution));
            } 
        }
        else if(cmd[0] == "solve"){
            CMD_solve(current_puzzle, 1);
        }
        else if(cmd[0] == "show"){
            print_puzzle(current_puzzle);
        }
        else if(cmd[0] == "count"){
            cout << "There exist " << CMD_count(current_puzzle) << " of non-zero blocks. \n\n";
        }
        else if(cmd[0] == "undo"){
            if(len > 2) argument_error();
            else{
                int round = 1;
                if(len == 2) round = stoi(cmd[1]);
                for(int i = 0; i < round; i++){
                    if(current_status.size() > 1) current_status.pop_back();
                    else{
                        cout << "This is the oldest version. \n";
                        break;
                    }
                }
                int tmp = current_status.size() - 1;
                current_puzzle = current_status[tmp].first;
                current_solution = current_status[tmp].second;
                cout << "Finish!\n\n";
                print_puzzle(current_puzzle);
            }
        }
        else command_not_found_error();
    }
    return 0;
}
