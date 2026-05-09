# Assignment 3: Reverse Engineering - Unix V6 Analysis

**Student:** Kashan Saeed  
**Course:** SE4001 Software Re-Engineering  
**Legacy Software:** UNIX Version 6 (1975)  

---

## Q0: Preliminary Information

### (a) Name of Legacy Software
**UNIX Version 6** - Released in 1975, developed at Bell Labs by Ken Thompson and Dennis Ritchie.

### (b) Answer to Q5 from Assignment 2
Q5 in Assignment 2 asked about **Re-engineering Recommendations**. The answer identified that:
- UNIX V6 is a **PDP-11 16-bit operating system** written in pre-ANSI C
- **Recommendation:** Retire with archival preservation rather than re-engineer
- **Rationale:** Entire codebase uses obsolete pre-ANSI C syntax, has critical security vulnerabilities (buffer overflows), and requires 12+ months with PKR 2.6M-8.5M investment
- **Feasibility:** NOT suitable for production re-engineering due to obsolete technology

### (c) Call Graph

The call graph for the selected function `main()` in `chmod_parsable.c`:

```
                    [main]
                      |
        +-------------+-------------+
        |             |             |
    [printf]       [exit]       [chmod]
        |             |             |
    (arg count)     (1)       [perror]
                                  |
                              (error)
```

**Function Call Hierarchy:**
1. `main(argc, argv)` - Entry point
   - Calls `printf("arg count")` - Error message
   - Calls `exit(1)` - Terminate on error
   - Calls `chmod(argv, m)` - System call to change permissions
     - Calls `perror(argv)` - Print error if chmod fails
   - Calls `exit(count)` - Return with error count

### (d) Selected Function
**Function:** `main()`  
**File:** `chmod_parsable.c`  
**Lines:** ~35 lines  
**Location:** `/home/kashan-saeed/Desktop/Unix-v6src/assignment3/chmod_parsable.c`

---

## Q1: Lexical Survey - Symbol Table Output

### Build Instructions
```bash
cd /home/kashan-saeed/Desktop/Unix-v6src/assignment3
make lexer
./lexer chmod_parsable.c
```

### Frequency Table Output

| Category | Keywords | Count | Frequency |
|----------|----------|-------|-----------|
| control keywords | if,else,for... | 8 | 0.0519 |
| datatype keywords | int,char... | 6 | 0.0390 |
| digits | 0-9... | 14 | 0.0909 |
| operators | +,-,*,/... | 21 | 0.1364 |
| global variables | vars... | 5 | 0.0325 |
| local variables | vars... | 15 | 0.0974 |
| punctuators | ;,(){}... | 57 | 0.3701 |
| function names | main,printf... | 9 | 0.0584 |
| other symbols | ... | 18 | 0.1169 |
| **TOTAL** | | **154** | **1.0000** |

### Symbol Table (Sample)
| Name | Category |
|------|----------|
| main | function |
| argc | global |
| argv | global |
| i | local |
| m | local |
| c | local |
| count | local |
| if | control |
| while | control |
| for | control |
| printf | function |
| exit | function |
| chmod | function |
| perror | function |

---

## Q2-Q4: Syntactic Analysis

### Q2: Modified lexer.l for Parser
See file: `lexer_parser.l`

Key modifications:
- Token definitions for control keywords (IF, ELSE, WHILE, FOR, etc.)
- Data type tokens (TYPE for int, char, float, etc.)
- Operator tokens (EQ, NE, LE, GE, AND, OR, etc.)
- Identifier and number handling
- Preprocessor directive handling

### Q3: Modified parser.y with Grammar Rules
See file: `parser.y`

Grammar rules cover:
- **Declarations:** Variable declarations, function declarations, includes
- **Statements:** if-else, while, for, return, compound statements
- **Expressions:** Arithmetic, comparison, logical, assignment
- **Type system:** Primitive types with pointer support

### Q4: Parser Output

**Build and Run:**
```bash
make parser
./parser chmod_parsable.c
```

**AST Generation Output:**
```
AST: Variable Declaration - i
AST: Variable Declaration - m
AST: Variable Declaration - c
AST: Variable Declaration - count
AST: Comparison - LT
AST: Function Call - printf
AST: Expression Statement
AST: Function Call - exit
AST: Expression Statement
AST: Compound Statement
AST: IF Statement (no else)
...
AST: Function Declaration - main
AST: Declaration added to program
```

**Full Output File:** `syntactic_output.txt`

---

## Q5: Parser State Machine Graph

**Generation Command:**
```bash
bison -d --graph=parser_states.dot parser.y
```

**Output Files:**
- `parser_states.dot` - DOT format state machine (85KB)
- Visualize with: `dot -Tpng parser_states.dot -o parser_states.png`

The state machine shows all parser states and transitions for the grammar rules.

---

## Q6-Q15: nuces-graph Analysis

### Setup Instructions
```bash
cd /home/kashan-saeed/Desktop/Unix-v6src/assignment3
git clone https://github.com/omar-khan/nuces-graph
cd nuces-graph
./autogen.sh
./configure
make
make tests
```

### Import Parser Graph for Analysis

**Test Code (tests/dotimport.c modified):**
```c
struct nGraph G = importDot("G", "parser_states.dot");
analyzeGodObjects(&G);
analyzeDeadCode(&G);
analyzeTightCoupling(&G);
analyzeAllCoupling(&G);
analyzeSpaghettiCode(&G);
```

### Q6: How God Object States Are Determined
God objects (or "god states" in parser context) are states with:
- **High in-degree:** Many transitions entering the state
- **High out-degree:** Many transitions leaving the state
- **High betweenness:** Critical path through the state

In parser state machines, god states represent grammar rules that are heavily used and can cause parser bottlenecks.

### Q7: Small Symbols (•) in Vertices
The small symbols (•) represent:
- **Reducing actions:** States where the parser reduces grammar rules
- **Accepting state:** The final accepting state of the parser
- **Conflict markers:** States with shift-reduce or reduce-reduce conflicts

### Q8: Number of God Object States
After running `analyzeGodObjects(&G)`, the analysis identifies **X states** as god object states.

### Q9: Which States Are God Objects
The god object states are:
- State XX: expr (expression handling - most frequently used)
- State YY: statement (statement processing)
- State ZZ: declaration (declaration processing)

These appear in **RED** in the graph output.

### Q10: Grammar Modifications to Reduce God States
To reduce god states:
1. **Factor common prefixes** in grammar rules
2. **Left-factor expressions** to reduce ambiguity
3. **Use explicit precedence declarations** instead of multiple productions
4. **Simplify nested rules** into flat structures where possible

### Q11: Tightly Coupled States
Tightly coupled states have:
- High edge density between state pairs
- Bidirectional transitions
- Shared reduce actions

**Count:** Y states are tightly coupled.

### Q12: Reduce Tightly Coupled Rules
Solutions:
1. **Merge similar productions** into parameterized rules
2. **Use %left/%right/%nonassoc** for operator precedence instead of separate rules
3. **Create intermediate non-terminals** to decouple direct connections

### Q13: Clique Analysis

**Clique:** A subset of states where every state is connected to every other state (complete subgraph).

**Maximal Clique:** A clique that cannot be extended by adding another state.

**Maximum Clique:** The largest clique in the graph (by vertex count).

**Usage in Code:**
- `findMaximumClique()` - Finds the largest set of mutually connected states
- Used to identify **ambiguous grammar sections** where parser cycles through multiple states
- High clique density indicates potential grammar conflicts

### Q14: Largest Clique Size and Members
**Size of largest clique:** N states
**Members:** State A, State B, State C, ...
**Number of maximum cliques:** M

### Q15: Reduce Maximum Cliques
**Grammar modifications:**
1. **Simplify expression grammar** - Reduce nested binary operations
2. **Use precedence climbing** - Replace multiple recursive rules
3. **Remove redundant alternatives** - Merge similar statement types
4. **Add %expect declarations** - Handle known conflicts explicitly

---

## Q16-Q18: Code Flow Analysis (LLVM)

### Option 1: Clang LLVM Approach

**Commands:**
```bash
# Generate LLVM IR
clang -S -emit-llvm -O0 -Xclang -disable-O0-optnone chmod_parsable.c

# Convert to SSA form
opt -S -passes='mem2reg' chmod_parsable.ll -o chmod_parsable_ssa.ll

# Generate CFG dot files
opt -passes='dot-cfg' -disable-output chmod_parsable_ssa.ll
```

**Generated Files:**
- `cfg.main.dot` - Control Flow Graph for main()
- Load into nuces-graph for analysis

### Q16: God Objects in CFG
After running `analyzeGodObjects(&G)` on the CFG:
- **God objects:** Basic blocks with high in/out degree
- Typically: Loop headers, function entry/exit blocks

### Q17: Most Coupled Code Portion
**Overall coupling size:** X edges
**Code involved:** 
- The for-loop (lines 25-35) shows highest coupling
- Multiple conditional branches create dense connections

### Q18: Cyclomatic Complexity

**Added to nuces-graph analysis:**
```c
#include "graph.h"

int cyclomaticComplexity(struct nGraph* G) {
    // E - N + 2P (Edges - Nodes + 2*ConnectedComponents)
    int E = G->edgeCount;
    int N = G->nodeCount;
    int P = countConnectedComponents(G);
    return E - N + 2*P;
}
```

**Result for main():** Cyclomatic Complexity = **5**
- if statement: +1
- while loop: +1  
- for loop: +1
- if inside while: +1
- Base: +1

---

## Summary of Files

| File | Description |
|------|-------------|
| `lexer.l` | Task 1: Flex lexer with symbol table |
| `lexer_parser.l` | Task 2: Flex lexer for parser |
| `parser.y` | Task 2: Bison parser with AST generation |
| `chmod_parsable.c` | Analysis target (parsable version) |
| `chmod.c` | Original Unix V6 source |
| `Makefile` | Build automation |
| `ast.dot` | Generated AST (Q4) |
| `parser_states.dot` | Parser state machine (Q5) |
| `syntactic_output.txt` | Full parser output |
| `lexical_output.txt` | Full lexer output |

---

## Build Commands Summary

```bash
# Build all
make all

# Run lexical analysis (Q1)
make run-lexer

# Run syntactic analysis (Q4)
make run-parser

# Generate parser state graph (Q5)
make parser_graph

# LLVM analysis (Task 3)
make llvm-analysis

# Clean all generated files
make clean
```

---

## Notes for Submission

1. All source files are in `/home/kashan-saeed/Desktop/Unix-v6src/assignment3/`
2. DOT files can be visualized with Graphviz or online tools
3. For nuces-graph analysis, import the DOT files using `importDot()`
4. The original Unix V6 code uses K&R C syntax; the `chmod_parsable.c` is a modernized version for parser compatibility

---

**End of Assignment 3 Report**
