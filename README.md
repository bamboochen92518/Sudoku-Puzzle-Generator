# Let's play sudoku together!

This program can help you create and solve classic sudoku puzzle. 

## Compile and Execute

```
$ g++ -o sudoku new_sudoku.cpp
$ ./sudoku
```

## Command you can use


### About helping
`help`
Show all the command you can use. 

`help {command}`
Get the detail of the command. 

`exit`
Exit. 

### About creating puzzle
`create`
Create a new sudoku puzzle. 

`create -c {count}`
Create a new sudoku puzzle with specific non-empty blocks. 

`create -p {pattern_filename}`
Create a new sudoku puzzle with specific pattern. 

`add {row1}{column1} {row2}{column2} ...`
Filled the answer in those empty blocks.

`remove {row1}{column1} {row2}{column2} ...`
Remove the answer of those blocks.

`swap {row1}{row2} {column1}{column2} ...`
Swap two rows or columns.

**Note that the number of row should be `a` to `i` and the number of column should be `1` to `9`.**

`show`
Show current puzzle.

`undo {round}`
Resume the puzzle before specific steps. (default = 1)

`save {filename}`
Save current sudoku puzzle.
If the filename is not given, the defalut filename is 'yy-MM-dd_hh:mm:ss_puzzle'. 


### About solving puzzle
`load {filename}`
Load a sudoku puzzle and check if there are unique solution.

`solve`
Solve current puzzle. 

## TODO
1. Add human algorithm.
2. Add variants sudoku puzzle rules.
3. Develop GUI. 
