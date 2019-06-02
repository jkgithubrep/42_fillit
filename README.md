# Fillit

The __*fillit*__ project at [42](https://www.42.fr/) is the first group project and consists in writing a program that will find a way to assemble a given set of *Tetrominoes* altogether in the smallest possible square.

A *tetromino* is a geometric shape composed of four squares connected orthogonally which became popular with the famous *tetris* game (see picture below).  

![tetrominoes](https://upload.wikimedia.org/wikipedia/commons/thumb/5/50/All_5_free_tetrominoes.svg/320px-All_5_free_tetrominoes.svg.png "5 tetrominoes")
## Instructions

Your program will take a file containing a list of tetrominoes and has to find the **smallest square** in a **minimal amount of time**.

Only the following functions from the libc are allowed: `exit`, `open`, `close`, `write`, `read`, `malloc` and `free`.

### Program input

The program must take only one parameter, a file with the following format:
- every tetromino must exactly fit in a 4 by 4 chars square
- all tetrominoes are separated by a newline
- the file can contain between 1 and 26 tetrominoes

```
$ cat valid_input.txt
...#
...#
...#
...#

....
####
....
....

#...
###.
....
....
$
```
 
 It is possible to describe the same tetromino in multiple ways:
 ```
 ##..	....	..##
 #...	.##.	..#.
 #...	.#..	..#.
 ....	.#..	....
 ```
 
 ### Program output
 
The program must display the smallest assembled square on the standard output. To identify each tetromino in the square solution, you will assign a capital letter to each of them, starting with `A` and increasing for each new tetromino.

If the file contains at least one error, your program must display `error` on the standard output followed by a newline and has to exit properly.

Tetrominoes are ordered according to their order in the file. 

Among all the possible solutions for the smallest square, the one accepted is the one where the tetrominoes are placed on their most upper-left position.

*Example*:
With the following input...
```
A...
A...
A...
A...

....
..BB
..BB
....
```
...the accepted solution is
```
ABB.
ABB.
A... 
A...
```
...even if the following solutions are equivalent
```
.ABB	...A
.ABB	.BBA
.A.. 	.BBA
.A..	...A
```

## Additional features

We decided to include a more detailed error handling system which covers:
- invalid tetrominoes
- invalid characters in a tetromino
- invalid file (column > 4 characters)
- invalid file (too long)
- file cannot be open
- error when reading the file


## Key learnings

- Implementation of a **backtracking algorithm** 
- Use of **bitwise operations** (our tetrominoes are stored as *unsigned short* and we use bitwise operations to manipulate them)
