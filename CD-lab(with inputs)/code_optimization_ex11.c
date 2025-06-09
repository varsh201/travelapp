#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum { ADD, SUB, MUL, DIV, NONE } OpType;

typedef struct {
    char result[10];
    char arg1[10];
    char op[3];
    char arg2[10];
} Quad;

OpType getOpType(const char* op) {
    if (strcmp(op, "+") == 0) return ADD;
    if (strcmp(op, "-") == 0) return SUB;
    if (strcmp(op, "*") == 0) return MUL;
    if (strcmp(op, "/") == 0) return DIV;
    return NONE;
}

int isNumber(const char* str) {
    if (*str == '-') str++; // Handle negative numbers
    for (int i = 0; str[i]; ++i) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int evaluate(int a, int b, OpType op) {
    switch (op) {
        case ADD: return a + b;
        case SUB: return a - b;
        case MUL: return a * b;
        case DIV: return b != 0 ? a / b : 0;
        default: return 0;
    }
}

void optimize(Quad* code, int n) {
    printf("\nOptimized Code:\n");
    for (int i = 0; i < n; ++i) {
        int isOptimized = 0;
        OpType optype = getOpType(code[i].op);

        if (isNumber(code[i].arg1) && isNumber(code[i].arg2)) {
            int val = evaluate(atoi(code[i].arg1), atoi(code[i].arg2), optype);
            printf("%s = %d\n", code[i].result, val);
            isOptimized = 1;
        }
        else if (optype == ADD && (strcmp(code[i].arg1, "0") == 0 || strcmp(code[i].arg2, "0") == 0)) {
            printf("%s = %s\n", code[i].result,
                strcmp(code[i].arg1, "0") == 0 ? code[i].arg2 : code[i].arg1);
            isOptimized = 1;
        }
        else if (optype == SUB && strcmp(code[i].arg2, "0") == 0) {
            printf("%s = %s\n", code[i].result, code[i].arg1);
            isOptimized = 1;
        }
        else if (optype == MUL && (strcmp(code[i].arg1, "1") == 0 || strcmp(code[i].arg2, "1") == 0)) {
            printf("%s = %s\n", code[i].result,
                strcmp(code[i].arg1, "1") == 0 ? code[i].arg2 : code[i].arg1);
            isOptimized = 1;
        }
        else if (optype == MUL && !isNumber(code[i].arg1) && !isNumber(code[i].arg2) &&
                (strcmp(code[i].arg1, "2") == 0 || strcmp(code[i].arg2, "2") == 0)) {
            char* x = strcmp(code[i].arg1, "2") == 0 ? code[i].arg2 : code[i].arg1;
            printf("%s = %s + %s\n", code[i].result, x, x);
            isOptimized = 1;
        }
        else if (optype == DIV && strcmp(code[i].arg2, "1") == 0) {
            printf("%s = %s\n", code[i].result, code[i].arg1);
            isOptimized = 1;
        }
        else if (optype == MUL && (strcmp(code[i].arg1, "0") == 0 || strcmp(code[i].arg2, "0") == 0)) {
            printf("%s = 0\n", code[i].result);
            isOptimized = 1;
        }

        if (!isOptimized) {
            printf("%s = %s %s %s\n", code[i].result, code[i].arg1, code[i].op, code[i].arg2);
        }
    }
}

int main() {
    int n;
    printf("Enter number of expressions: ");
    scanf("%d", &n);
    getchar(); // Consume newline left by scanf

    Quad code[n];
    printf("Enter expressions in format: result = arg1 op arg2 (e.g., t1 = 1 + 1)\n");

    for (int i = 0; i < n; ++i) {
        char line[100];
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%s = %s %s %s", code[i].result, code[i].arg1, code[i].op, code[i].arg2);
    }

    printf("\nOriginal Code:\n");
    for (int i = 0; i < n; ++i) {
        printf("%s = %s %s %s\n", code[i].result, code[i].arg1, code[i].op, code[i].arg2);
    }

    optimize(code, n);
    return 0;
}