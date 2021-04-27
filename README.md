# Static Semantics

## Compilers - P3 - Local Option

**Version Control**:
GitHub repo: https://github.com/STLnick/statSem

Cloned from [parser](https://github.com/STLnick/parser) to get all of that code to begin.

---

**To run the program**:
- Run `make` in the root of the project to build `statSem`
    - The executable `statSem` is built and placed in `/bin`.
- Execute `cd ./bin`
- Run `./statSem` with a file containing the `.fs` extension (example below)

**Run command structure**:

> `[file]` _must have the extension of_ `.fs` or no extension at all.
> - for example `test1.fs`, `text.fs`, `whatever.fs`, `filename`

`./statSem [file]` or `./statSem [file].fs`
    - **NOTE**: The files to be read from _MUST BE IN THE_ `/bin` directory with the executable

`./statSem -h`

- help


### Simple example of a valid, parsable program
`p2g1.fs` of provided test files

```
$$ p3g1 $$
data x := 5 ;
main
begin
data y := 67 ;
outter y ;
assign x := y ;
end
```

### Complex example of a valid, parsable program
`p2g6.fs` of provided test files

```
$$ p3g2 $$
data z := 321 ;
data y := 567 ;
main
begin
data x := 5 ;
loop [ y => z ]
  begin
  data c := 3 ;
     begin
     proc c ; 
     end
  end ;
outter x ;
end
```

### Semantics
Essentially following the rules of `C` for semantic rules.


---

**What Works**:
- Semantics are enforced locally
    - Define variables once
    - Follows C-like rules of scoping
- Errors output helpful messages
- Displays awesome messages on successful parsing

**What Doesn't Work**:
- We'll find out...

---
### Commit Log


b0926f2 Remove unused/dead code
7641996 Fixes and changes for delmar
7de02cf Update README
3da39f0 Have fun with the success message
5e1ae04 Enforce local static semantics for variables
ab87001 Remove duplicate tokens being pushed on nodes
5a33edf Successfully use a stack while traversing tree and pass global tests
923f62c Remove old comments
c9d2b1e Store entire token instead of just string on node
7127b0d Change exe name
503c1d3 Correct function that made it obvious I do not code in C++ enough
90c394a Update README with new project info to start
d4082ee Initial commit with code from parser
**All other commits and associated code preceding are from `parser` project and can be accessed at that repo linked above**

