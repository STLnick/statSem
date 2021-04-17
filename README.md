# Static Semantics

## Compilers - P3

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


**What Doesn't Work**:


---
### Commit Log


**All other commits and associated code preceding are from `parser` project and can be accessed at that repo linked above**
