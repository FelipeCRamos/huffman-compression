# Huffman Coding Project
The implementation of the Huffman Coding Concept using `C++14`, aiming to achieve
a stable compression/uncompression algorithm.

## Compilation
In order to compile this project, you just need the bare `gcc/clang` packages
installed in your computer.

You can compile by typing onto your favorite terminal:
```bash
# once already in project root folder
make
```

## Execution
After compiled, you can execute the project by running a simple command, like:
```bash
./huf [input] [output]
```
Making sure that:
+ `input` file exists
+ You have permissions to write on `output` file

## Details of implementation
This project uses concepts of tries to generate the shorter
possible binary path to a given char, based on how many occurrences it has on
the given input. With this being done, we can represent a normal 8 bits `char`
with 4~5 bits (depending on the input).

Here's a briefly explanation about how the prefixed tree (trie):
```
Suppose we have a small text like: "bom esse bombom", we can extract the following info:
    char 'b' appears 3 times
    char 'o' appears 3 times
    char 'm' appears 3 times
    char 'e' appears 2 times
    char 's' appears 2 times
    char ' ' appears 2 times

And then, we can create a Prefixed Digital Tree like this:
                        ( *)
                       /    \
                      /      \
                   ( *)      ( *)
                  /   \        /\
                 /     \      /  \          ( sorry for the bad ascii art )
              ( *)     ( *) ('o') ('m')
              /  \     /  \  
             /   |     |   \
          ('b') ('s') ('e')(' ')

Where the path for i.e. char 'o' from the root can be represented by 2 bits,
one bit for first direction and another for second direction, like '10'
(
    1: dig right sub-tree
    0: dig left sub-tree
)

With that in mind, how the 'm' char would be coded? :P
```
So the 'key' to use this compression method is to have the tree and their paths.

That's why we will store on the compressed file our tree by pre-order traversal
path, with the following syntax:
```
0001b1s01e1_01o1m

Where:
    Each '0' is an internal node of the tree
    Each '1' represent that the next byte will be read as a char
```

`to be continued...`

## Other things
This was a project made by me for the Basic Data Structure II course on [UFRN](https://ufrn.br).
This is far from being 100% polished, but i'll be very happy if you can contribute
with anything to this project.

## Authorship
Project made by Felipe Ramos with the **MIT** License.
