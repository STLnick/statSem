# Parser

## Compilers - P2

**Version Control**:
GitHub repo: https://github.com/STLnick/parser

Cloned from [scanner](https://github.com/STLnick/parser) to get all of that code to begin.

---

**To run the program**:
- Run `make` in the root of the project to build `frontEnd`
    - The executable `frontEnd` is built and placed in `/bin`.
- Execute `cd ./bin`
- Run `./frontEnd` with a file containing the `.fs` extension (example below)

**Run command structure**:

> `[file]` _must have the extension of_ `.fs` or no extension at all.
> - for example `test1.fs`, `text.fs`, `whatever.fs`, `filename`

`./frontEnd [file]` or `./frontEnd [file].fs`
    - **NOTE**: The files to be read from _MUST BE IN THE_ `/bin` directory with the executable

`./frontEnd -h`

- help


### Simple example of a valid, parsable program
`p2g1.fs` of provided test files

```
$$ p2g1 $$
main
begin
getter x ;
end
```

### Complex example of a valid, parsable program
`p2g6.fs` of provided test files

```
$$ p2g6 $$
data a := 5 ;
data b := 6 ;
data c := 7 ;
main
begin
    outter ( 2 * 3 / 5 + 7 - * 11 + ( 13 * * 17 ) ) ;
end
```


---

**What Works**:
- Parses file correctly
- Displays proper error if there is one in parsing
- Creates a tree from parsing
- Displays tree nodes with associated terminals and nonterminals

**What Doesn't Work**:
- Nothing that I'm aware of!

---
### Commit Log
b1ebb15 Silence compiler warnings
6dcf577 Update README.md
eedb6be Final changes for submission on delmar - mainly include <cstdlib>
2012efb Add nonterminals to strings on node for display purposes
e5a9af4 Merge branch 'dev' of https://github.com/STLnick/parser into dev
fbe7a27 Print tree in preorder traversal
983de85 Fix storing of tokens on node
80226b4 Fix printing of tokens on node
304194e Add manually processed tokens to node vector
94cb0e2 Add missing default value to function declaration
447e246 Change label for node on nonterminals with leftover text from copy/paste
9670534 Change tree and node struct to fit parser needs
7b21575 Print tree in preorder traversal
9b7090f Fix storing of tokens on node
90e21f3 Fix printing of tokens on node
03e9db1 Add manually processed tokens to node vector
944e7bd Add missing default value to function declaration
481774c Change label for node on nonterminals with leftover text from copy/paste
e93deb2 Changes to tree and node struct to fit parser needs
8485763 Refactor consume function to take in node and store token string
9d185b3 Refactor nonterminals and parser to return a node struct or null for ε
502c487 Bring in tree code from P0
7455408 Remove TODO comments
580e66e Parse R0 nonterminal
aebca65 FIx parsing of M nonterminal
8d36708 Fix parsing of colon equals operator
d76487d Write out rest of nonterminal functions - most still need testing
e18491f Parse goto and label nonterminals
86f5ed9 Check and consume terminals with function
448932a Improve error message with token literals and line numbers
5081a12 Correctly parse the most basic program valid for our language
f50e12e WIP with problems - segfault introduced somewhere
a0e530e Update text in init.cpp to reflect parser instead of scanner
7a6e8bc Build utility function to determine if tokenId is in the first of stat
67d2617 Update text of showHelp to reflect parser instead of scanner
210a177 Add first sets in comments
4d2c2ca Add grammar nonterminal production rules as comments
c885ec4 Remove dead code and comments
00301b8 Establish program, block, and vars nonterminal functions
80c9132 Stub out other nonterminal functions
d958d6a Rename grandpappy nonterminal to reflect naming pattern to be used going forward
002c387 Setup super basic nonterminal parser processing
b2a3ea9 Change executable name
028d3a0 Update README with P2 info in place of P1 info

**All other commits preceding are from `scanner` project and can be accessed at that repo linked above**
