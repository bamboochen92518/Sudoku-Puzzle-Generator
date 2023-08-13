#include <bits/stdc++.h>
#include <cstdio>
#include <string>
#include <map>
#include "myerror.h"

using namespace std;

#ifndef HELP
#define HELP

typedef struct _CMD{
    string usage;
    string description;
}CMD;

map<string, CMD> cmd_map;

void init_cmd_map(){
    cmd_map["create"] = {"create / -c {count} / -p {pattern filename}", "Create a new sudoku puzzle with specific non-empty blocks or given pattern. "};
    cmd_map["load"] = {"load {filename}", "Load a sudoku puzzle and check if there are unique solution. "};
    cmd_map["help"] = {"help {command}", "Get the detail of the command. "};
    cmd_map["save"] = {"save {filename}", "Save current sudoku puzzle. "};
    cmd_map["exit"] = {"exit", "Exit. "};
    cmd_map["add"] = {"add {row1}{column1} {row2}{column2} ...", "Filled the answer in those empty blocks. "};
    cmd_map["remove"] = {"remove {row1}{column1} {row2}{column2} ...", "Remove the answer of those blocks. "};
    cmd_map["swap"] = {"swap {row1}{row2} {column1}{column2} ...", "Swap two rows or columns. "};
    cmd_map["solve"] = {"solve", "Solve current puzzle. "};
    cmd_map["show"] = {"show", "Show current puzzle. "};
    cmd_map["undo"] = {"undo {round}", "Resume the puzzle before {round} steps. (default = 1)"};
}

void help(string command){
    if(command == "summary"){
        cout << "Here are the commands you can use. \n\n";
        int counter = 0;
        for(const auto& c : cmd_map){
            cout << left << setw(15) << c.first;
            counter += 1;
            if(counter % 5 == 0) cout << "\n";
        }
        if(counter % 5 != 0) cout << "\n";
        cout << "\nType \"help {command}\" to get the detail of these command. \n";
    }
    else{
        if(!cmd_map[command].usage.empty())
            cout << "[usage] " << cmd_map[command].usage << "\n\n" << "[description] " << cmd_map[command].description << "\n\n";
        else command_not_found_error();
    }
    return;
}

#endif
