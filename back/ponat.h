#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

const char PLUS[] = "+";
const char MINUS[] = "-";
const char MULTIPLAY[] = "*";
const char DIVIDE[] = "/";
const char BKTL[] = "(";
const char BKTR[] = ")";
const char STAGE[] = "^";
const char MOD[] = "mod";
const char COS[] = "cos";
const char SIN[] = "sin";
const char TAN[] = "tan";
const char ACOS[] = "acos";
const char ASIN[] = "asin";
const char ATAN[] = "atan";
const char SQRT[] = "sqrt";
const char LN[] = "ln";
const char LOG[] = "log";
const char NUM[] = "num";

// Qt
// CMake

typedef struct leksem {
    double value;
    int priority;
    char *typeOper;
} leksem;

typedef struct arrLecsem {
    struct leksem arr[255];
    int index;
} arrLecsem;
// } leksems;

typedef struct STACK_st {
    leksem arr[100];
    int index;
    int incorrectInput;
} stack_st;
// } steck, outStr;



char *typeOper(char *str, stack_st *stack);
int is_num(char symbol);
int is_letter(char symbol);
int is_sign(char symbol);
int priority(char *str);
int parse(char *str, arrLecsem *leksems, stack_st *stack);
void transPolNat(arrLecsem *leksems, stack_st *steck, stack_st *outStr);
leksem produkt(leksem *act, char *typeOper);
void toStringResFunk(char *buf, stack_st *stack);
void calculation(stack_st *steck, stack_st *outStr);
void pushSteck(leksem obj, stack_st *stack);
struct leksem popSteck(stack_st *stack);
struct leksem peecStack(stack_st *stack);
void pushOutStr(leksem obj, stack_st *outStr);
void ponat(char *str);
void clningStr(char *str);
double myAtof(char *s);
// void hello(char* str);
