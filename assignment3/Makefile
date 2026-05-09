# Makefile for Assignment 3 - Reverse Engineering
# Unix V6 Analysis - Lexical and Syntactic Analysis

CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -g

# Targets
all: lexer parser

# Task 1: Lexical Analysis
lexer: lexer.l
	$(FLEX) -o lexer.yy.c lexer.l
	$(CC) $(CFLAGS) -o lexer lexer.yy.c -lfl

# Task 2: Syntactic Analysis (requires bison and flex)
parser: lexer_parser.l parser.y
	$(BISON) -d parser.y
	$(FLEX) -o lexer_parser.yy.c lexer_parser.l
	$(CC) $(CFLAGS) -o parser parser.tab.c lexer_parser.yy.c -lfl

# Generate parser state machine graph (Q5)
parser_graph: parser.y
	$(BISON) -d --graph=parser.dot parser.y
	dot -Tpng parser.dot -o parser_states.png
	dot -Tpdf parser.dot -o parser_states.pdf

# Generate AST dot file (run parser first)
ast_graph: parser chmod_clean.c
	./parser chmod_clean.c 2>&1 | head -100
	dot -Tpng ast.dot -o ast.png 2>/dev/null || echo "Note: AST dot generated but may need manual rendering"

# Run lexical analysis (Q1)
run-lexer: lexer
	./lexer chmod_clean.c

# Run syntactic analysis (Q4)
run-parser: parser
	./parser chmod_clean.c

# Run all analysis steps
analyze: all
	@echo "=== Running Lexical Analysis ==="
	./lexer chmod_clean.c > lexical_output.txt 2>&1
	@echo "=== Running Syntactic Analysis ==="
	./parser chmod_clean.c > syntactic_output.txt 2>&1
	@echo "=== Analysis Complete ==="
	@echo "Outputs saved to: lexical_output.txt, syntactic_output.txt"

# LLVM Analysis (Task 3)
llvm-analysis:
	@echo "=== LLVM Control Flow Analysis ==="
	clang -S -emit-llvm -O0 -Xclang -disable-O0-optnone chmod_clean.c
	opt -S -passes='mem2reg' chmod_clean.ll -o chmod_clean_ssa.ll
	opt -passes='dot-cfg' -disable-output chmod_clean_ssa.ll
	@echo "DOT files generated: cfg.main.dot"

dot-cfg:
	opt -passes='dot-cfg' -disable-output chmod_clean_ssa.ll 2>&1

# Generate PNG from DOT files
dot-to-png:
	for f in *.dot; do \
		[ -f "$$f" ] && dot -Tpng "$$f" -o "$${f%.dot}.png"; \
	done

# Clean build files
clean:
	rm -f lexer parser
	rm -f *.yy.c *.tab.c *.tab.h
	rm -f *.dot *.png *.pdf
	rm -f *.ll *.s
	rm -f lexical_output.txt syntactic_output.txt
	rm -f parser.output

# Help
help:
	@echo "Assignment 3 - Reverse Engineering Build System"
	@echo ""
	@echo "Targets:"
	@echo "  make all          - Build lexer and parser"
	@echo "  make lexer        - Build lexical analyzer (Task 1)"
	@echo "  make parser       - Build syntactic analyzer (Task 2)"
	@echo "  make run-lexer    - Run lexical analysis on chmod_clean.c (Q1)"
	@echo "  make run-parser   - Run syntactic analysis on chmod_clean.c (Q4)"
	@echo "  make parser_graph - Generate parser state machine graph (Q5)"
	@echo "  make ast_graph    - Generate AST visualization"
	@echo "  make llvm-analysis- Run LLVM CFG analysis (Task 3)"
	@echo "  make clean        - Remove all generated files"

.PHONY: all clean help run-lexer run-parser parser_graph ast_graph llvm-analysis dot-to-png analyze
