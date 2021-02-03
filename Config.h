#ifndef DIFFERENTIATOR_CONFIG_H
#define DIFFERENTIATOR_CONFIG_H

const int CONST = 1;
const int VAR = 2;
const int OPERATORCODE = 3;
const int VARMEAN = 4;
const int OPERATORS = 5;
const int FUNCTION = 6;
const int BRACKET = 7;
const int COMPARATOR = 8;
const int FUNC = 9;

const int STR_MAX = 50;
const int VAR_MAX = 50;
const int INIT_SIZE = 20;
const int MULTIPLIER = 2;
const int END = 0;

const int VAR_NUM = 15;
const int MAX_FUNC_NUM = 100;

const int READ = 10000;

enum Brackets
{
    LEFTBRACKET = 1,
    RIGHTBRACKET
};

enum VarMean
{
    EQUAL = 1,
    EQUALPLUS,
    EQUALMINUS,
    EQUALMUL,
    EQUALDIV
};

enum Operators
{
    PLUS = 1,
    MINUS,
    MUL,
    DIV,
    SINE,
    COSINE,
    DEG,
    LN,
    SQRT,
    TG,
    CTG,
    SH,
    CH,
    TH,
    CTH
};

enum Comparator
{
    EQUALITY = 1,
    NOTEQUAL,
    MORE,
    NOTLESS,
    LESS,
    NOTMORE
};

enum Operator
{
    BEGIN = 1,
    WHILE,
    IF,
    INPUT,
    OUTPUT,
    RETURN,
    CALL,
    ENDPROGRAM,
    SETWINDOW,
    SETPIXEL,
    HLINE,
    VLINE,
    LINE,
    CIRCLE,
    RECTANGLE,
    SHOW,
    PARTCLEAR,
    CLEARWINDOW
};

enum Function
{
    START = 1,
    OPERATE,
    VARS,
    FINISH,
    FINISHPROGRAM,
    NEWFUNC,
    EMPTY
};
#endif //DIFFERENTIATOR_CONFIG_H
