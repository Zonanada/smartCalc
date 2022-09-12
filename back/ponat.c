#include "ponat.h"

int is_num(char symbol) {
    return symbol == '.' || (symbol  > 47 && symbol < 58) ;
}

int is_letter(char symbol) {
    return symbol > 96 && symbol < 123;
}

int is_sign(char symbol) {
    return (symbol > 39 && symbol < 44) || symbol == 45 || symbol == 47 || symbol == 94;
}

char *typeOper(char *str, stack_st *stack) {
    char *result = NULL;
    if (!result && !strcmp(str, (char*)PLUS)) result = (char*)PLUS;
    if (!result && !strcmp(str, (char*)MINUS)) result = (char*)MINUS;
    if (!result && !strcmp(str, (char*)MULTIPLAY)) result = (char*)MULTIPLAY;
    if (!result && !strcmp(str, (char*)DIVIDE)) result = (char*)DIVIDE;
    if (!result && !strcmp(str, (char*)BKTL)) result = (char*)BKTL;
    if (!result && !strcmp(str, (char*)BKTR)) result = (char*)BKTR;
    if (!result && !strcmp(str, (char*)STAGE)) result = (char*)STAGE;
    if (!result && !strcmp(str, (char*)MOD)) result = (char*)MOD;
    if (!result && !strcmp(str, (char*)COS)) result = (char*)COS;
    if (!result && !strcmp(str, (char*)SIN)) result = (char*)SIN;
    if (!result && !strcmp(str, (char*)TAN)) result = (char*)TAN;
    if (!result && !strcmp(str, (char*)ACOS)) result = (char*)ACOS;
    if (!result && !strcmp(str, (char*)ASIN)) result = (char*)ASIN;
    if (!result && !strcmp(str, (char*)ATAN)) result = (char*)ATAN;
    if (!result && !strcmp(str, (char*)SQRT)) result = (char*)SQRT;
    if (!result && !strcmp(str, (char*)LN)) result = (char*)LN;
    if (!result && !strcmp(str, (char*)LOG)) result = (char*)LOG;

    if (!result) {
        printf("36 %s\n", str);
        stack->incorrectInput = 1;
    }
    return result;

}

int priority(char *str) {
    int result = 0;
    if (!result && !strcmp(str, (char*)PLUS)) result = 1;
    if (!result && !strcmp(str, (char*)MINUS)) result = 1;
    if (!result && !strcmp(str, (char*)MULTIPLAY)) result = 2;
    if (!result && !strcmp(str, (char*)DIVIDE)) result = 2;
    if (!result && !strcmp(str, (char*)STAGE)) result = 3;
    if (!result && !strcmp(str, (char*)MOD)) result = 2;
    if (!result && !strcmp(str, (char*)COS)) result = 4;
    if (!result && !strcmp(str, (char*)SIN)) result = 4;
    if (!result && !strcmp(str, (char*)TAN)) result = 4;
    if (!result && !strcmp(str, (char*)ACOS)) result = 4;
    if (!result && !strcmp(str, (char*)ASIN)) result = 4;
    if (!result && !strcmp(str, (char*)ATAN)) result = 4;
    if (!result && !strcmp(str, (char*)SQRT)) result = 4;
    if (!result && !strcmp(str, (char*)LN)) result = 4;
    if (!result && !strcmp(str, (char*)LOG)) result = 4;

    return result;
}

void printLeksems(arrLecsem *leksems) {
    for (int i = 0; i < leksems->index; i++) {
        printf("[%d]\nvalue = %f\npriority = %d\ntypeOper = %s\n", i, leksems->arr[i].value, leksems->arr[i].priority, leksems->arr[i].typeOper);
    }
}

void printOutStr(stack_st *outStr) {
    for (int i = 0; i < outStr->index; i++) {
        if (outStr->arr[i].value > 0) {
            printf("%.1f ", outStr->arr[i].value);
        } else {
            printf("%s ", outStr->arr[i].typeOper);
        }
    }
     printf("\n");
}

void printStack(stack_st *stack) {
    for (int i = 0; i < stack->index; i++) {
        if (stack->arr[i].value) {
            printf("%.1f ", stack->arr[i].value);
        } else {
            printf("%s ", stack->arr[i].typeOper);
        }
        
    }
    printf("\n");
}

int parse(char *str, arrLecsem *leksems, stack_st *stack) {
    char leksem[255];
    clningStr(leksem);
    int indexStr = 0;
    int flag = 1;
    int negative = 0;
    while (flag) {
        if (*str != 32) {
            if (is_num(*str)) { // пришла цифра или точка
                leksem[indexStr] = *str;
                indexStr++;
                if (!is_num(*(str+1))) {  // если цифра закончилась выгружаем в лексему
                    indexStr = 0;
                    leksems->arr[leksems->index].value = myAtof(leksem);
                    if (negative)  {
                        leksems->arr[leksems->index].value = leksems->arr[leksems->index].value * -1;
                        negative = 0;
                    }
                    leksems->arr[leksems->index].typeOper = (char*)NUM;
                    leksems->arr[leksems->index].priority = 0;
                    leksems->index++;
                    clningStr(leksem);
                }
            }

            if (is_letter(*str)) { // пришла буква
                leksem[indexStr] = *str;
                indexStr++;
                if (!is_letter(*(str+1))) {  // если буквы закончились выгружаем в лексему
                    indexStr = 0;
                    leksems->arr[leksems->index].typeOper = typeOper(leksem, stack);
                    leksems->arr[leksems->index].priority = priority(leksem);
                    leksems->arr[leksems->index].value = 0;
                    leksems->index++;
                    clningStr(leksem);
                }
            }

            if (is_sign(*str)) { // если односимвольный знак
                if ( (!is_num(*(str-1))) && *str == '-' && is_num(*(str+1))) {
                    negative = 1;
                } else {
                    leksem[0] = *str;
                    leksem[1] = '\0';
                    leksems->arr[leksems->index].typeOper = typeOper(leksem, stack);
                    leksems->arr[leksems->index].priority = priority(leksem);
                    leksems->arr[leksems->index].value = 0;
                    leksems->index++;
                    clningStr(leksem);
                }
            }

            if (*str == '\0') flag = 0;
        }
       str++;
    }

    return 0;
}

void pushSteck(leksem obj, stack_st *stack) {
    stack->arr[stack->index] = obj;
    stack->index+=1;
}

struct leksem popSteck(stack_st *stack) {
    leksem result;
    if (stack->index > 0) {
        stack->index-=1;
        result = stack->arr[stack->index];
    } else {
        stack->incorrectInput=1;
    }
    return result;
}

struct leksem peecStack(stack_st *stack) {
    return stack->arr[stack->index - 1];
}

void pushOutStr(leksem obj, stack_st *outStr) {
    outStr->arr[outStr->index] = obj;
    outStr->index++;
}

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
                    if (peecStack(steck).priority == leksems->arr[i].priority && leksems->arr[i].priority == 3) {
                        pushSteck(leksems->arr[i], steck);
                    } else if (peecStack(steck).priority >= leksems->arr[i].priority) {
                        while (steck->index > 0 && peecStack(steck).priority >= leksems->arr[i].priority){
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

leksem produkt(leksem *act, char *typeOper) {
    leksem result = {0, 0, (char*)NUM};
    if (!result.value && !strcmp(typeOper, (char*)PLUS)) result.value = act[0].value + act[1].value;
    if (!result.value && !strcmp(typeOper, (char*)MINUS)) result.value = act[0].value - act[1].value;
    if (!result.value && !strcmp(typeOper, (char*)MULTIPLAY)) result.value = act[0].value * act[1].value;
    if (!result.value && !strcmp(typeOper, (char*)DIVIDE)) result.value = act[0].value / act[1].value;    
    if (!result.value && !strcmp(typeOper, (char*)STAGE)) result.value = pow(act[0].value, act[1].value);
    if (!result.value && !strcmp(typeOper, (char*)MOD)) result.value = fmod(act[0].value, act[1].value);
    if (!result.value && !strcmp(typeOper, (char*)COS)) result.value = cos(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)SIN)) result.value = sin(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)TAN)) result.value = tan(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)ACOS)) result.value = acos(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)ASIN)) result.value = asin(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)ATAN)) result.value = atan(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)SQRT)) result.value = sqrt(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)LN)) result.value = log10(act[0].value);
    if (!result.value && !strcmp(typeOper, (char*)LOG)) result.value = log(act[0].value);

    return result;

}

double myAtof(char *s) {
    double a = 0.0;
    int e = 0;
    int c;
    while ((c = *s++) != '\0' && isdigit(c)) {
            a = a*10.0 + (c - '0');
    }
    if (c == '.') {
            while ((c = *s++) != '\0' && isdigit(c)) {
                    a = a*10.0 + (c - '0');
                    e = e-1;
            }
    }
    if (c == 'e' || c == 'E') {
            int sign = 1;
            int i = 0;
            c = *s++;
            if (c == '+')
                    c = *s++;
            else if (c == '-') {
                    c = *s++;
                    sign = -1;
            }
            while (isdigit(c)) {
                    i = i*10 + (c - '0');
                    c = *s++;
            }
            e += i*sign;
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



void clningStr(char *str) {
    for (int i = 0; i < 255; i++) {
        *(str+i) = '\0';
    }
}

int lengthStr(char *str) {
    int count = 0;
    while (*str != 0) {
        count++;
        str++;
    }
    return count;
    
}

void toStringResFunk(char *str, stack_st *stack) {
    char *error = "Incorrect input";
    if (stack->index > 1 || stack->index == 0 || stack->incorrectInput || isnan(stack->arr[0].value) || isinf(stack->arr[0].value)) {
        strcpy(str, error);
    } else {
        char localStr[30];
        printf("323 %f\n", stack->arr[0].value);
        sprintf(localStr, "%.11lf", stack->arr[0].value);
        printf("325 %s\n", localStr);
        int num = 1;
        for (int i = lengthStr(localStr)-1; i > 0; i--) {
            if (localStr[i] == 48) {
                localStr[i] = '\0';
            } else {
                if (localStr[i] < 48 || localStr[i] > 57) localStr[i] = '\0';
                if (localStr[i - 1] == 44) localStr[i - 1] = 46;
                i = 1;
            }
        }
        for (int i = lengthStr(localStr)-1; i > 0; i--) {
            if (localStr[i] == 44) localStr[i] = 46;
        }
        strcpy(str, localStr);
    }
}


void ponat(char *str) {
    printf("282 %s\n", str);
    arrLecsem leksems;
    stack_st stack, outStr;
    leksems.index = 0;
    stack.index = 0;
    outStr.index = 0;
    stack.incorrectInput = 0;
    outStr.incorrectInput = 0;
    parse(str, &leksems, &stack);
    printLeksems(&leksems);
    transPolNat(&leksems, &stack, &outStr);
    printOutStr(&outStr);
    calculation(&stack, &outStr);
    toStringResFunk(str, &stack);
    printf("350 %s\n", str);
}



// int main() {
//     char str[30] = {'3', '.', '3', '/', '3'};
//     arrLecsem leksems;
//     stack_st stack, outStr;
//     leksems.index = 0;
//     stack.index = 0;
//     outStr.index = 0;

//     parse(&str[0], &leksems, &stack);
//     printLeksems(&leksems);
//     transPolNat(&leksems, &stack, &outStr);
//     // printOutStr(&outStr);
//     // calculation(&stack, &outStr);
//     // for (int i = 0; i < strlen(str); i++) {
//     //     *(str+i) = '\0';
//     // }


//     // toStringResFunk(str, &stack);
//     // printf("320 %s", str);
    
//     return 0;
// }
