# Let's play sudoku together!

This program can help you create and solve classic sudoku puzzle. 

### Compile and Execute

```
$ g++ -o sudoku new_sudoku.cpp
$ ./sudoku
```

### Command you can use


#### About helping
`help`
Show all the command you can use. 

`help {command}`
Get the detail of the command. 

`exit`
Exit. 

#### About creating puzzle
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

`show`
Show current puzzle.

`undo {round}`
Resume the puzzle before specific steps. (default = 1)

`save {filename}`
Save current sudoku puzzle.
If the filename is not given, the defalut filename is 'yy-MM-dd_hh:mm:ss_puzzle'. 

**Note that row should be `a` to `i` and column should be `1` to `9`. **

#### About solving puzzle
`load {filename}`
Load a sudoku puzzle and check if there are unique solution.

`solve`
Solve current puzzle. 
