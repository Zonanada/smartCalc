#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

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

typedef struct STACK_st {
    leksem arr[100];
    int index;
    int incorrectInput;
} stack_st;



int is_num(char *symbol);
int is_sign(char symbol);
int is_letter(char symbol);
char *typeOper(char *str, stack_st *stack);
int is_num(char *symbol);
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
char *ponat(char *str);
void clningStr(char *str);
double myAtof(char *s);
void stringAddition(char *str1, char *str2);
char *changeXOnDouble(char *str, double num);
// void hello(char* str);
