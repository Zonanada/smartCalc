#include "s21_smart_calc.h"

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


/**
 * @brief checking for num and dot
 * 
 * @param symbol 
 * @return int 
 */
int is_num(char *symbol) {
    if (*symbol == ',') *symbol = '.';
    return *symbol == '.' || (*symbol > 47 && *symbol < 58);
}


/**
 * @brief checking for letter
 * 
 * @param symbol 
 * @return int 
 */
int is_letter(char symbol) {
    int result = symbol > 96 && symbol < 123;
    return result;
}

/**
 * @brief cheking for sign
 * 
 * @param symbol 
 * @return int 
 */
int is_sign(char symbol) {
    return (symbol > 39 && symbol < 44) || symbol == 45 || symbol == 47 || symbol == 94;
}

/**
 * @brief type operators leksem
 * 
 * @param str 
 * @param stack 
 * @return char* 
 */
char *typeOper(char *str, stack_st *stack) {
    char *result = NULL;
    if (!strcmp(str, (char *)PLUS)) result = (char *)PLUS;
    if (!result && !strcmp(str, (char *)MINUS)) result = (char *)MINUS;
    if (!result && !strcmp(str, (char *)MULTIPLAY)) result = (char *)MULTIPLAY;
    if (!result && !strcmp(str, (char *)DIVIDE)) result = (char *)DIVIDE;
    if (!result && !strcmp(str, (char *)BKTL)) result = (char *)BKTL;
    if (!result && !strcmp(str, (char *)BKTR)) result = (char *)BKTR;
    if (!result && !strcmp(str, (char *)STAGE)) result = (char *)STAGE;
    if (!result && !strcmp(str, (char *)MOD)) result = (char *)MOD;
    if (!result && !strcmp(str, (char *)COS)) result = (char *)COS;
    if (!result && !strcmp(str, (char *)SIN)) result = (char *)SIN;
    if (!result && !strcmp(str, (char *)TAN)) result = (char *)TAN;
    if (!result && !strcmp(str, (char *)ACOS)) result = (char *)ACOS;
    if (!result && !strcmp(str, (char *)ASIN)) result = (char *)ASIN;
    if (!result && !strcmp(str, (char *)ATAN)) result = (char *)ATAN;
    if (!result && !strcmp(str, (char *)SQRT)) result = (char *)SQRT;
    if (!result && !strcmp(str, (char *)LN)) result = (char *)LN;
    if (!result && !strcmp(str, (char *)LOG)) result = (char *)LOG;

    if (!result) {
        printf("36 %s\n", str);
    }
    return result;
}
/**
 * @brief prioritization leksems
 * 
 * @param str 
 * @return int 
 */
int priority(char *str) {
    int result = 0;
    if (!strcmp(str, (char *)PLUS)) result = 1;
    if (!result && !strcmp(str, (char *)MINUS)) result = 1;
    if (!result && !strcmp(str, (char *)MULTIPLAY)) result = 2;
    if (!result && !strcmp(str, (char *)DIVIDE)) result = 2;
    if (!result && !strcmp(str, (char *)STAGE)) result = 3;
    if (!result && !strcmp(str, (char *)MOD)) result = 2;
    if (!result && !strcmp(str, (char *)COS)) result = 4;
    if (!result && !strcmp(str, (char *)SIN)) result = 4;
    if (!result && !strcmp(str, (char *)TAN)) result = 4;
    if (!result && !strcmp(str, (char *)ACOS)) result = 4;
    if (!result && !strcmp(str, (char *)ASIN)) result = 4;
    if (!result && !strcmp(str, (char *)ATAN)) result = 4;
    if (!result && !strcmp(str, (char *)SQRT)) result = 4;
    if (!result && !strcmp(str, (char *)LN)) result = 4;
    if (!result && !strcmp(str, (char *)LOG)) result = 4;

    return result;
}


/**
 * @brief parse input str to leksems
 * 
 * @param str 
 * @param leksems 
 * @param stack 
 * @return int 
 */
int parse(char *str, arrLecsem *leksems, stack_st *stack) {
    char *leksem = calloc(50, sizeof(char));
    int indexStr = 0;
    int flag = 1;
    int negative = 0;
    while (flag) {
        if (*str != 32) {
            if (is_num(str)) {
                leksem[indexStr] = *str;
                indexStr++;
                if (!is_num((str + 1))) {
                    leksem[indexStr] = '\0';
                    indexStr = 0;
                    leksems->arr[leksems->index].value = myAtof(leksem);
                    if (negative) {
                        leksems->arr[leksems->index].value = leksems->arr[leksems->index].value * -1;
                        negative = 0;
                    }
                    leksems->arr[leksems->index].typeOper = (char *)NUM;
                    leksems->arr[leksems->index].priority = 0;
                    leksems->index++;
                    *leksem = '\0';
                }
            }

            if (is_letter(*str)) {
                leksem[indexStr] = *str;
                indexStr++;
                if (!is_letter(*(str + 1))) {
                    leksem[indexStr] = '\0';
                    indexStr = 0;
                    leksems->arr[leksems->index].typeOper = typeOper(leksem, stack);
                    leksems->arr[leksems->index].priority = priority(leksem);
                    leksems->arr[leksems->index].value = 0;
                    leksems->index++;
                    *leksem = '\0';
                }
            }

            if (is_sign(*str)) {
                if ((!is_num((str - 1))) && *str == '-' && is_num((str + 1))) {
                    negative = 1;
                } else {
                    leksem[0] = *str;
                    leksem[1] = '\0';
                    leksems->arr[leksems->index].typeOper = typeOper(leksem, stack);
                    leksems->arr[leksems->index].priority = priority(leksem);
                    leksems->arr[leksems->index].value = 0;
                    leksems->index++;
                    *leksem = '\0';
                }
            }
            if (*str == '\0') flag = 0;
        }
        str++;
    }
    free(leksem);

    return 0;
}


/**
 * @brief push leksem in stack
 * 
 * @param obj 
 * @param stack 
 */
void pushSteck(leksem obj, stack_st *stack) {
    stack->arr[stack->index] = obj;
    stack->index += 1;
}


/**
 * @brief pop the last leksem of the stack
 * 
 * @param stack 
 * @return struct leksem 
 */
struct leksem popSteck(stack_st *stack) {
    leksem result = {0};
    if (stack->index > 0) {
        stack->index -= 1;
        result = stack->arr[stack->index];
    } else {
        stack->incorrectInput = 1;
    }
    return result;
}


/**
 * @brief view last stack leksem
 * 
 * @param stack 
 * @return struct leksem 
 */
struct leksem peecStack(stack_st *stack) {
    return stack->arr[stack->index - 1];
}


/**
 * @brief push leksem in out str
 * 
 * @param obj 
 * @param outStr 
 */
void pushOutStr(leksem obj, stack_st *outStr) {
    outStr->arr[outStr->index] = obj;
    outStr->index++;
}


/**
 * @brief translate to reverce polish notation
 * 
 * @param leksems 
 * @param steck 
 * @param outStr 
 */
void transPolNat(arrLecsem *leksems, stack_st *steck, stack_st *outStr) {
    for (int i = 0; i < leksems->index; i++) {
        if (leksems->arr[i].typeOper == NUM) {
            outStr->arr[outStr->index] = leksems->arr[i];
            outStr->index++;
        } else {
            if (leksems->arr[i].typeOper == BKTL) pushSteck(leksems->arr[i], steck);
            if (leksems->arr[i].typeOper == BKTR) {
                int flag = 1;
                while (flag) {
                    if (peecStack(steck).typeOper != BKTL) {
                        pushOutStr(popSteck(steck), outStr);
                    } else {
                        flag = 0;
                        popSteck(steck);
                    }
                }
            }

            if (leksems->arr[i].priority > 0) {
                if (steck->index == 0) {
                    pushSteck(leksems->arr[i], steck);
                } else {
                    if (peecStack(steck).priority == 3 && leksems->arr[i].priority == 3) {
                        pushSteck(leksems->arr[i], steck);
                    } else if (peecStack(steck).priority >= leksems->arr[i].priority) {
                        while (steck->index > 0 && peecStack(steck).priority >= leksems->arr[i].priority) {
                            pushOutStr(popSteck(steck), outStr);
                        }
                        pushSteck(leksems->arr[i], steck);
                    } else {
                        pushSteck(leksems->arr[i], steck);
                    }
                }
            }
        }
    }
    while (steck->index > 0) {
        pushOutStr(popSteck(steck), outStr);
    }
}


/**
 * @brief calculating reverse polish notation
 * 
 * @param stack 
 * @param outStr 
 */
void calculation(stack_st *stack, stack_st *outStr) { 
    for (int i = 0; i < outStr->index; i++) {
        if (outStr->arr[i].typeOper == NUM) pushSteck(outStr->arr[i], stack);
        if (outStr->arr[i].priority > 0 && outStr->arr[i].priority < 4) {
            leksem act[2];
            act[1] = popSteck(stack);
            act[0] = popSteck(stack);

            pushSteck(produkt(act, outStr->arr[i].typeOper), stack);
        }
        if (outStr->arr[i].priority > 3) {
            struct leksem act[2];
            act[0] = popSteck(stack);
            pushSteck(produkt(act, outStr->arr[i].typeOper), stack);
        }
        if (outStr->arr[i].typeOper == BKTL || outStr->arr[i].typeOper == BKTR) stack->incorrectInput = 1;
    }
}

/**
 * @brief finding out the type of operator
 * 
 * @param act 
 * @param typeOper 
 * @return leksem 
 */
leksem produkt(leksem *act, char *typeOper) { 
    leksem result = {0, 0, (char *)NUM};
    if (!strcmp(typeOper, (char *)PLUS)) result.value = act[0].value + act[1].value;
    if (!result.value && !strcmp(typeOper, (char *)MINUS)) result.value = act[0].value - act[1].value;
    if (!result.value && !strcmp(typeOper, (char *)MULTIPLAY)) result.value = act[0].value * act[1].value;
    if (!result.value && !strcmp(typeOper, (char *)DIVIDE)) result.value = act[0].value / act[1].value;
    if (!result.value && !strcmp(typeOper, (char *)STAGE)) result.value = pow(act[0].value, act[1].value);
    if (!result.value && !strcmp(typeOper, (char *)MOD)) result.value = fmod(act[0].value, act[1].value);
    if (!result.value && !strcmp(typeOper, (char *)COS)) result.value = cos(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)SIN)) result.value = sin(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)TAN)) result.value = tan(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)ACOS)) result.value = acos(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)ASIN)) result.value = asin(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)ATAN)) result.value = atan(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)SQRT)) result.value = sqrt(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)LN)) result.value = log10(act[0].value);
    if (!result.value && !strcmp(typeOper, (char *)LOG)) result.value = log(act[0].value);
    return result;
}


/**
 * @brief from string to double
 * 
 * @param s 
 * @return double 
 */
double myAtof(char *s) {
    double a = 0.0;
    int e = 0;
    int c;
    while ((c = *s++) != '\0' && isdigit(c)) {
        a = a * 10.0 + (c - '0');
    }
    if (c == '.') {
        while ((c = *s++) != '\0' && isdigit(c)) {
            a = a * 10.0 + (c - '0');
            e = e - 1;
        }
    }
    if (c == 'e' || c == 'E') {
        int sign = 1;
        int i = 0;
        c = *s++;
        if (c == '+') {
            c = *s++;
        } else if (c == '-') {
            c = *s++;
            sign = -1;
        }
        while (isdigit(c)) {
            i = i * 10 + (c - '0');
            c = *s++;
        }
        e += i * sign;
    }
    while (e > 0) {
        a *= 10.0;
        e--;
    }
    while (e < 0) {
        a *= 0.1;
        e++;
    }
    return a;
}

/**
 * @brief correctness check and remove excess zeros
 * 
 * @param str 
 * @param stack 
 */
void toStringResFunk(char *str, stack_st *stack) {
    int haveError = stack->index != 1 || stack->incorrectInput == 1;
    haveError += isnan(stack->arr[0].value) == 1 || isinf(stack->arr[0].value) == 1;
    if (haveError) {
        strcpy(str, "Incorrect input");
    } else {
        sprintf(str, "%.11lf", stack->arr[0].value);
        for (int i = 49; i > 0; i--) {
            if (str[i] == '0') {
                str[i] = '\0';
            } else if (str[i] == '.' || str[i] == ',') {
                str[i] = '\0';
                i = 0;
            } else {
                if (str[i] > 47 && str[i] < 58) i = 0;
            }
        }
    }
}


/**
 * @brief translete in reverse polish notation
 * 
 * @param str 
 * @return char* 
 */
char *ponat(char *str) {
    char *result = calloc(50, sizeof(char));
    arrLecsem leksems;
    stack_st stack, outStr;
    leksems.index = 0;
    stack.index = 0;
    outStr.index = 0;
    stack.incorrectInput = 0;
    outStr.incorrectInput = 0;
    parse(str, &leksems, &stack);
    transPolNat(&leksems, &stack, &outStr);
    calculation(&stack, &outStr);
    toStringResFunk(result, &stack);
    return result;
}



/**
 * @brief string concatenation
 * 
 * @param str1 
 * @param str2 
 */
void stringAddition(char *str1, char *str2) {
    while (*str1 != 0) {
        str1++;
    }
    while (*str2 != 0) {
        *str1 = *str2;
        str1++;
        str2++;
    }
}


/**
 * @brief serch "X" in string, and replace for num
 * 
 * 
 * @param str 
 * @param num 
 * @return char* 
 */
char *changeXOnDouble(char *str, double num) {
    char *strData = calloc(255, sizeof(char));
    char *strNum = calloc(50, sizeof(char));
    if (strData && strNum) {
        sprintf(strNum, "%.11lf", num);
        int symbol = strchr(str, 'X') - &str[0];
        strncat(strData, str, symbol);
        stringAddition(strData, strNum);
        stringAddition(strData, &str[symbol + 1]);
        free(strNum);
    }
    return *strData ? strData : NULL;
}
