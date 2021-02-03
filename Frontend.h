#ifndef CATLANGUAGE_FRONTEND_H
#define CATLANGUAGE_FRONTEND_H
#define LETTER ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
#define NUM (str[i] >= '0' && str[i] <= '9')
#define COMP (str[i] == '>' || str[i] == '<' || str[i] == '=')
#define SKIP (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
#define OP (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
#define BRACKETS (str[i] == '(' || str[i] == ')')


void TokenResize(node_t** tokens, int* size)
{
    tokens = (node_t**) realloc(tokens, sizeof(node_t*) * (*size) * MULTIPLIER);

    if (!tokens)
    {
        printf("Reallocation error");
        return;
    }

    (*size) *= MULTIPLIER;
}

///----------------------------------------------------------------------------------------------------------------///

#define DEF_OP(name, num) if (strcmp(temp, #name) == 0)\
    node[num++] = NodeCreate(num, VARMEAN);

node_t** Tokens(char* str, int* ptr, char** vars, int varnum, char** func, int funcnum)
{
    node_t** node = (node_t**) calloc(INIT_SIZE, sizeof(node_t*));
    int size = INIT_SIZE;
    int num = 1;
    int i = *ptr;

    for (int i = (*ptr); i < strlen(str); i++)
    {
        if (num >= size)
        {
            printf("Size\t%d\n", size);
            auto** data = (node_t**) realloc(node, sizeof(node_t*) * size * MULTIPLIER);

            if (!data)
            {
                printf("Allocation error\n");
                return nullptr;
            }

            node = data;

            size *= MULTIPLIER;
        }

        if (LETTER)
        {
            char temp[STR_MAX] = "";
            int tmpnum = 0;

            while (LETTER)
            {
                temp[tmpnum++] = str[i];
                i++;
            }

            i--;

            for (int i = 0; i < varnum; i++)
            {
                if (strcmp(temp, vars[i]) == 0)
                {
                    node[num] = NodeCreate(i, VAR);
                    num++;
                }
            }

            for (int i = 0; i < funcnum; i++)
            {
                if (strcmp(temp, func[i]) == 0)
                {
                    printf("FUNCTION");
                    node[num] = NodeCreate(i, FUNC);
                    num++;
                }
            }

            if (strcmp(temp, "cos") == 0)
                node[num++] = NodeCreate(COSINE, OPERATORCODE);

            if (strcmp(temp, "sin") == 0)
                node[num++] = NodeCreate(SINE, OPERATORCODE);

            if (strcmp(temp, "ln") == 0)
                node[num++] = NodeCreate(LN, OPERATORCODE);

            if (strcmp(temp, "sqrt") == 0)
                node[num++] = NodeCreate(SQRT, OPERATORCODE);

            if (strcmp(temp, "begin") == 0)
                node[num++] = NodeCreate(BEGIN, OPERATORS);

            if (strcmp(temp, "while") == 0)
                node[num++] = NodeCreate(WHILE, OPERATORS);

            if (strcmp(temp, "if") == 0)
                node[num++] = NodeCreate(IF, OPERATORS);

            if (strcmp(temp, "input") == 0)
                node[num++] = NodeCreate(INPUT, OPERATORS);

            if (strcmp(temp, "output") == 0)
                node[num++] = NodeCreate(OUTPUT, OPERATORS);

            if (strcmp(temp, "call") == 0)
                node[num++] = NodeCreate(CALL, OPERATORS);

            if (strcmp(temp, "func") == 0)
                node[num++] = NodeCreate(NEWFUNC, FUNCTION);

            if (strcmp(temp, "return") == 0)
                node[num++] = NodeCreate(RETURN, OPERATORS);

            if (strcmp(temp, "setwindow") == 0)
            {
                printf("URA!\n");
                node[num++] = NodeCreate(SETWINDOW, OPERATORS);
            }

            if (strcmp(temp, "setpixel") == 0)
                node[num++] = NodeCreate(SETPIXEL, OPERATORS);

            if (strcmp(temp, "hline") == 0)
                node[num++] = NodeCreate(HLINE, OPERATORS);

            if (strcmp(temp, "vline") == 0)
                node[num++] = NodeCreate(VLINE, OPERATORS);

            if (strcmp(temp, "line") == 0)
                node[num++] = NodeCreate(LINE, OPERATORS);

            if (strcmp(temp, "circle") == 0)
                node[num++] = NodeCreate(CIRCLE, OPERATORS);

            if (strcmp(temp, "rectangle") == 0)
                node[num++] = NodeCreate(RECTANGLE, OPERATORS);

            if (strcmp(temp, "show") == 0)
                node[num++] = NodeCreate(SHOW, OPERATORS);

            if (strcmp(temp, "partclear") == 0)
                node[num++] = NodeCreate(PARTCLEAR, OPERATORS);

            if (strcmp(temp, "clearwindow") == 0)
                node[num++] = NodeCreate(CLEARWINDOW, OPERATORS);

            if (strcmp(temp, "end") == 0)
                node[num++] = NodeCreate(END, OPERATORS);

            if (strcmp(temp, "finish") == 0)
            {
                printf("FINISH\t%d\n", num);
                node[num++] = NodeCreate(ENDPROGRAM, OPERATORS);

            }

            continue;
        }

        if (NUM)
        {
            int tempnum = 0;

            while (NUM)
            {
                tempnum = tempnum * 10 + str[i] - '0';
                i++;
            }

            i--;

            node[num++] = NodeCreate(tempnum, CONST);
            continue;
        }

        if (SKIP)
            continue;

        if (OP)
        {
            switch (str[i]) {
                case '+':
                    node[num++] = NodeCreate(PLUS, OPERATORCODE);
                    break;

                case '-':
                    node[num++] = NodeCreate(MINUS, OPERATORCODE);
                    break;

                case '*':
                    node[num++] = NodeCreate(MUL, OPERATORCODE);
                    break;

                case '/':
                    node[num++] = NodeCreate(DIV, OPERATORCODE);
                    break;

                case '^':
                    node[num++] = NodeCreate(DEG, OPERATORCODE);
                    break;
            }

            continue;
        }


        if (str[i] == '=')
        {
            i++;

            switch (str[i])
            {
                case ':':
                    node[num++] = NodeCreate(EQUAL, VARMEAN);
                    break;

                case '+':
                    node[num++] = NodeCreate(EQUALPLUS, VARMEAN);
                    break;

                case '-':
                    node[num++] = NodeCreate(EQUALMINUS, VARMEAN);
                    break;

                case '*':
                    node[num++] = NodeCreate(EQUALMUL, VARMEAN);
                    break;

                case '/':
                    node[num++] = NodeCreate(EQUALDIV, VARMEAN);
                    break;

                case '=':
                    node[num++] = NodeCreate(EQUALITY, COMPARATOR);
            }
            continue;
        }

        if (str[i] == ';')
        {
            node[num++] = NodeCreate(END, OPERATORCODE);
            continue;
        }

        if (BRACKETS)
        {
            switch (str[i])
            {
                case '(':
                    node[num++] = NodeCreate(LEFTBRACKET, BRACKET);
                    break;

                case ')':
                    node[num++] = NodeCreate(RIGHTBRACKET, BRACKET);
                    break;
            }
            continue;
        }

        if (str[i] == '<' || str[i] == '>')
        {
            char temp[STR_MAX] = "";
            int len = 0;

            while (str[i] == '<' || str[i] == '>' || str[i] == '=')
            {
                temp[len] = str[i];
                i++;
                len++;
            }

            if (strcmp(temp, "<>") == 0)
                node[num++] = NodeCreate(NOTEQUAL, COMPARATOR);

            if (strcmp(temp, ">") == 0)
                node[num++] = NodeCreate(MORE, COMPARATOR);

            if (strcmp(temp, ">=") == 0)
                node[num++] = NodeCreate(NOTLESS, COMPARATOR);

            if (strcmp(temp, "<") == 0)
                node[num++] = NodeCreate(LESS, COMPARATOR);

            if (strcmp(temp, "<=") == 0)
                node[num++] = NodeCreate(NOTLESS, COMPARATOR);

            continue;
        }
    }

    node[0] = NodeCreate(num - 1, 0);

    (*ptr) = i;

    return node;

}

#undef DEF_OP
///----------------------------------------------------------------------------------------------------------------///

#define TOKENNUM (token[i]->data.type == CONST || token[i]->data.type == VAR)
#define TOKENMUL (token[i]->data.type == OPERATORCODE && (token[i]->data.data == MUL || token[i]->data.data == DIV))
#define TOKENPLUS (token[i]->data.type == OPERATORCODE && (token[i]->data.data == PLUS || token[i]->data.data == MINUS))
#define TOKENBRACKETS (token[i]->data.type == BRACKET && token[i]->data.data == LEFTBRACKET)
#define TOKENEND (token[i]->data.type == OPERATORCODE && token[i]->data.data == END)
#define TOKENDEG (token[i]->data.type == OPERATORCODE && token[i]->data.data == DEG)
#define TOKENSCL (token[i]->data.type == OPERATORCODE && (token[i]->data.data == SINE || token[i]->data.data == COSINE || token[i]->data.data == LN || token[i]->data.data == SQRT))


node_t* GetExpressionNode(node_t** token, int* ptr);

node_t* GetNumNode(node_t** token, int* ptr)
{
    int i = *ptr;
    if (TOKENNUM)
    {
        i++;
        (*ptr) = i;
        return token[i-1];
    }

    return nullptr;
}

node_t* GetSCLNode(node_t** token, int* ptr)
{
    node_t* temp1 = nullptr;
    node_t* temp2 = nullptr;
    node_t* tempnode = nullptr;
    int i = *ptr;

    if (TOKENNUM || TOKENBRACKETS) {
        temp1 = GetExpressionNode(token, &i);
    }

    while (TOKENNUM || TOKENSCL || TOKENBRACKETS)
    {
        if (token[i]->data.type == OPERATORCODE)
        {
            switch (token[i]->data.data)
            {
                case SINE:
                    tempnode = NodeCreate(SINE, OPERATORCODE);
                    i++;
                    temp2 = GetExpressionNode(token, &i);
                    NodeLeft(tempnode, temp2);
                    temp1 = tempnode;
                    break;

                case COSINE:
                    tempnode = NodeCreate(COSINE, OPERATORCODE);
                    i++;
                    temp2 = GetExpressionNode(token, &i);
                    NodeLeft(tempnode, temp2);
                    temp1 = tempnode;
                    break;

                case LN:
                    tempnode = NodeCreate(LN, OPERATORCODE);
                    i++;
                    temp2 = GetExpressionNode(token, &i);
                    NodeLeft(tempnode, temp2);
                    temp1 = tempnode;
                    break;

                case SQRT:
                    tempnode = NodeCreate(SQRT, OPERATORCODE);
                    i++;
                    temp2 = GetExpressionNode(token, &i);
                    NodeLeft(tempnode, temp2);
                    temp1 = tempnode;
                    break;
            }
        }
    }

    *ptr = i;
    if (!temp1)
        temp1 = temp2;
    return temp1;
}

node_t* GetDegNode(node_t** token, int* ptr)
{
    node_t* temp1 = nullptr;
    node_t* temp2 = nullptr;
    node_t* tempnode = nullptr;
    int i = *ptr;

    if (TOKENNUM || TOKENBRACKETS || TOKENSCL) {
        temp1 = GetSCLNode(token, &i);
    }

    while (TOKENNUM || TOKENDEG || TOKENSCL || TOKENBRACKETS)
    {

        if (TOKENDEG)
        {
            tempnode = NodeCreate(DEG, OPERATORCODE);
            NodeLeft(tempnode, temp1);
            i++;
            temp2 = GetExpressionNode(token, &i);
            NodeRight(tempnode, temp2);
            temp1 = tempnode;
            continue;
        }
    }

    *ptr = i;
    if (!temp1)
        temp1 = temp2;
    return temp1;
}


node_t* GetMulNode(node_t** token, int* ptr)
{
    node_t* temp1 = nullptr;
    node_t* temp2 = nullptr;
    node_t* tempnode = nullptr;
    int i = *ptr;

    if (TOKENNUM || TOKENBRACKETS || TOKENDEG || TOKENSCL) {
        temp1 = GetDegNode(token, &i);
    }

    while (TOKENNUM || TOKENMUL || TOKENDEG || TOKENSCL || TOKENBRACKETS)
    {

        if (TOKENMUL && token[i]->data.data == MUL)
        {
            tempnode = NodeCreate(MUL, OPERATORCODE);
            NodeLeft(tempnode, temp1);
            i++;
            temp2 = GetExpressionNode(token, &i);
            NodeRight(tempnode, temp2);
            temp1 = tempnode;
            continue;
        }

        if (TOKENMUL && token[i]->data.data == DIV)
        {
            tempnode = NodeCreate(DIV, OPERATORCODE);
            NodeLeft(tempnode, temp1);
            i++;
            temp2 = GetExpressionNode(token, &i);
            NodeRight(tempnode, temp2);
            temp1 = tempnode;
            continue;
        }
    }

    *ptr = i;
    if (!temp1)
        temp1 = temp2;
    return temp1;
}

node_t* GetPlusNode(node_t** token, int* ptr)
{
    node_t* temp1 = nullptr;
    node_t* temp2 = nullptr;
    node_t* tempnode = nullptr;
    int i = *ptr;

    if (TOKENNUM || TOKENBRACKETS || TOKENDEG || TOKENSCL || TOKENMUL)
    {
        temp1 = GetMulNode(token, &i);
    }

    while (TOKENNUM || TOKENMUL || TOKENDEG || TOKENBRACKETS || TOKENPLUS)
    {

        if (TOKENPLUS && token[i]->data.data == PLUS)
        {
            //    printf("PRIVET ZNAK PLUS\n");
            if (!temp1)
            {
                i++;
                temp1 = NodeCreate(PLUS, OPERATORCODE);

                NodeLeft(temp1, temp2);
                tempnode = GetExpressionNode(token, &i);
                NodeRight(temp1, tempnode);
                continue;
            }
            else
            {
                i++;
                //          printf("PRIVET\n");
                tempnode = NodeCreate(PLUS, OPERATORCODE);
                NodeLeft(tempnode, temp1);
                temp2 = GetMulNode(token, &i);
                temp1 = tempnode;
                NodeRight(temp1, temp2);
                continue;
            }
        }

        if (TOKENPLUS && token[i]->data.data == MINUS)
        {
            if (!temp1)
            {
                i++;
                temp1 = NodeCreate(MINUS, OPERATORCODE);
                NodeLeft(temp1, temp2);
                temp2 = GetExpressionNode(token, &i);
                NodeRight(temp1, temp2);
                continue;
            }
            else
            {
                i++;
                tempnode = NodeCreate(MINUS, OPERATORCODE);
                NodeLeft(tempnode, temp1);
                temp2 = GetMulNode(token, &i);
                temp1 = tempnode;
                NodeRight(temp1, temp2);
                continue;
            }
        }
    }

    *ptr = i;
    if (!temp1)
        temp1 = temp2;
    return temp1;
}

#define PRINT(a) fprintf(fout, a);

node_t* GetExpressionNode(node_t** token, int* ptr)
{
    node_t* node = nullptr;
    int i = *ptr;

    if (TOKENNUM)
    {
        node = GetNumNode(token, &i);
        (*ptr) = i;        i++;

        return node;
    }

    if (TOKENBRACKETS)
    {
        i++;
        *ptr = i;
        node = GetPlusNode(token, &i);
        i++;
        *ptr = i;
        return node;
    }

    if (TOKENEND)
        return node;

    return node;

}


node_t*  GetVarMeanNode(node_t** tokens, int* ptr)
{
    int i = *ptr;
    node_t* temp = tokens[i++];

    node_t* tempone = tokens[i++];
    node_t* temptwo = GetPlusNode(tokens, &i);

    NodeLeft(tempone, temp);
    NodeRight(tempone, temptwo);

    *ptr = i;

    return tempone;
}


node_t* GetComparisonNode(node_t** tokens, int* ptr)
{
    int i = *ptr;
    node_t* nodeleft = GetPlusNode(tokens, &i);
    i++;
    node_t* node = tokens[i++];
    node_t* noderight = GetPlusNode(tokens, &i);

    NodeLeft(node, nodeleft);
    NodeRight(node, noderight);

    *ptr = i;
    printf("COMPARISON\n");
    return node;
}

node_t* GetFunctionNode(node_t** tokens, int* ptr);

node_t* GetOperator(node_t** tokens, int* ptr)
{
    int i = *ptr;
    node_t* node = tokens[i++];
    node_t* tempcmp = nullptr;
    node_t* tempact = nullptr;

    switch (tokens[i-1]->data.data) {
        case BEGIN:
            (*ptr) = i;
            return node;

        case IF:
            NodeLeft(node, GetComparisonNode(tokens, &i));
            i++;
            NodeRight(node, GetFunctionNode(tokens, &i));
            i++;
            (*ptr) = i;
            return node;

        case WHILE:
            NodeLeft(node, GetComparisonNode(tokens, &i));
            i++;
            NodeRight(node, GetFunctionNode(tokens, &i));
            i++;
            (*ptr) = i;
            return node;

        case INPUT:
            NodeLeft(node, tokens[i++]);
            (*ptr) = i;
            return node;

        case OUTPUT:
            tempcmp = GetPlusNode(tokens, &i);
            NodeLeft(node, tempcmp);
            i++;
            (*ptr) = i;
            return node;

        case RETURN:
            /*tempcmp = GetPlusNode(tokens, &i);
            NodeLeft(node, tempcmp);
            i++;*/
            (*ptr) = i;
            return node;

        case CALL:
            NodeLeft(node, tokens[i++]);
            (*ptr) = i;
            return node;

        case SETWINDOW:
            NodeLeft(node, GetPlusNode(tokens, &i));
            i++;
            NodeRight(node, GetPlusNode(tokens, &i));
            i++;
            (*ptr) = i;
            return node;

        case SETPIXEL:
            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeLeft(node, tempcmp);
            NodeRight(node, GetPlusNode(tokens, &i));
            i++;

            (*ptr) = i;
            return node;

        case CIRCLE:
            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeLeft(node, tempcmp);

            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(node, tempcmp);

            (*ptr) = i;
            return node;

        case LINE:
            tempcmp = NodeCreate(EMPTY, FUNCTION);
            tempact = NodeCreate(EMPTY, FUNCTION);

            NodeLeft(tempact, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempact, GetPlusNode(tokens, &i));
            i++;

            NodeLeft(tempcmp, tempact);
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeLeft(node, tempcmp);

            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(node, tempcmp);

            (*ptr) = i;
            return node;

        case HLINE:
            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeLeft(node, tempcmp);

            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(node, tempcmp);

            (*ptr) = i;
            return node;

        case VLINE:
            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeLeft(node, tempcmp);

            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(node, tempcmp);

            (*ptr) = i;
            return node;

        case PARTCLEAR:
            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeLeft(node, tempcmp);

            tempcmp = NodeCreate(EMPTY, FUNCTION);
            NodeLeft(tempcmp, GetPlusNode(tokens, &i));
            i++;
            NodeRight(tempcmp, GetPlusNode(tokens, &i));
            i++;

            NodeRight(node, tempcmp);

            (*ptr) = i;
            return node;

        case SHOW:
            (*ptr) = i;
            return node;

        case END:
            (*ptr) = i;
            return node;

        case ENDPROGRAM:
            (*ptr) = i;
            return node;
    }

    return nullptr;
}

#define CHECKOP (tokens[i]->data.type == OPERATORS)
#define CHECKVAR (tokens[i]->data.type == VAR)

node_t* GetFunctionNode(node_t** tokens, int* ptr)
{
    int i = *ptr;
    node_t* node = nullptr;
    node_t* node1 = nullptr;
    node_t* node2 = nullptr;
    node_t* head = nullptr;

    while (!(CHECKOP && (tokens[i]->data.data == END)))
    {
        if (CHECKOP)
        {
            switch (tokens[i]->data.data)
            {
                case BEGIN:
                    printf("BEGIN\n");
                    node = NodeCreate(START, FUNCTION);
                    head = node;
                    break;

                case ENDPROGRAM:
                    printf("FINISH\n");
                    NodeRight(node, NodeCreate(FINISHPROGRAM, FUNCTION));
                    (*ptr = i);
                    return head;


                default:
                    printf("PROSTOOP\n");
                    node1 = NodeCreate(OPERATE, FUNCTION);
                    //if(tokens[i]->data.type == OPERATORS)
                        //i++;
                    node2 = GetOperator(tokens, &i);
                    NodeLeft(node1, node2);
                    NodeRight(node, node1);
                    node = node1;
                    i--;
                    break;
            }

            i++;
            continue;
        }

        if (CHECKVAR)
        {
            printf("VAR\n");
            node1 = NodeCreate(VARS, FUNCTION);
            node2 = GetVarMeanNode(tokens, &i);
            NodeLeft(node1, node2);
            NodeRight(node, node1);
            node = node1;
            i++;
            continue;
        }


    }

    if (tokens[i]->data.data == END)
        printf("END\n");
    node1 = NodeCreate(FINISH, FUNCTION);
    NodeRight(node, node1);

    *ptr = i;
    return head;
}


/**node_t* FileRead(FILE* fin, char** vars, int* varnum, int maxvar)
{
    char temp[VAR_MAX] = "";                                        //Read variables
    fscanf(fin, "%s", temp);

    *varnum = 0;
    free(vars);
    vars = (char**) calloc(maxvar, sizeof(char*));
    for (int i = 0; i < maxvar; i++)
        vars[i] = (char*) calloc(VAR_MAX, sizeof(char));

    if (strcmp(temp, "vars:") == 0)
    {
        while (fscanf(fin, "%*[, ]%[^, 0-9;]", temp) != 0)
        {
            strcpy(vars[(*varnum)++], temp);
        }

        fscanf(fin, "%*[;]");
    }
}*/

#define PRINT(a) fprintf(fout, a);
#define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "%s\n", #name);\
                break;

int Labelcounter = 0;

void CompileExpression(FILE* fout, node_t* node)
{
    if (!node)
        return;

    CompileExpression(fout, node->left);
    CompileExpression(fout, node->right);

    switch(node->data.type)
    {
        case CONST:
            fprintf(fout, "PUSH\t%d\n", node->data.data);
            break;

        case VAR:
            fprintf(fout, "POPREG\t");
            switch (node->data.data)
            {
#include "Registers.h"
            }
            break;

        case OPERATORCODE:
            switch (node->data.data)
            {
                case PLUS:
                    PRINT("ADD\n");
                    break;

                case MINUS:
                    PRINT("SUB\n");
                    break;

                case MUL:
                    PRINT("MUL\n");
                    break;

                case DIV:
                    PRINT("DIV\n");
                    break;

                case SINE:
                    PRINT("SIN\n");
                    break;

                case COSINE:
                    PRINT("COS\n");
                    break;

                case DEG:
                    PRINT("DEG\n");
                    break;

                case LN:
                    PRINT("LN\n");
                    break;

                case SQRT:
                    PRINT("SQRT\n");
                    break;
            }
            break;
    }
}


void CompileVar(FILE* fout, node_t* node)
{
    switch (node->data.data)
    {
        case EQUAL:
            break;

        default:
            PRINT("POPREG\t");
            switch (node->left->data.data)
            {
                #include "Registers.h"
            }
    }

    CompileExpression(fout, node->right);

    switch(node->data.data)
    {
        case EQUALITY:
            break;

        case EQUALPLUS:
            PRINT("ADD\n");
            break;

        case EQUALMINUS:
            PRINT("SUB\n");
            break;

        case EQUALMUL:
            PRINT("MUL\n");
            break;

        case EQUALDIV:
            PRINT("DIV\n");
            break;
    }

    PRINT("PUSHREG\t");
    switch(node->left->data.data)
    {
        #include "Registers.h"
    }
}


void CompileComparison(FILE* fout, node_t* node)
{
    CompileExpression(fout, node->left);
    CompileExpression(fout, node->right);

    switch(node->data.data)
    {
        case EQUALITY:
            fprintf(fout, "JNE\t");
            break;

        case NOTEQUAL:
            fprintf(fout, "JE\t");
            break;

        case MORE:
            fprintf(fout, "JNL\t");
            break;

        case LESS:
            fprintf(fout, "JNM\t");
            break;

        case NOTMORE:
            fprintf(fout, "JL\t");
            break;

        case NOTLESS:
            fprintf(fout, "JM\t");
            break;
    }
}

void CompileFunction(FILE* fout, node_t* node, char** func);

void CompileOperator(FILE* fout, node_t* node, char** func)
{
    int tempnum = 0;
    switch(node->data.data)
    {
        case INPUT:
            PRINT("IN\n");
            PRINT("PUSHREG\t");
            switch(node->left->data.data)
            {
#include "Registers.h"
            }
            break;

        case OUTPUT:
            CompileExpression(fout, node->left);
            PRINT("OUTPOP\n");
            break;

        case IF:
            tempnum = Labelcounter;

            CompileComparison(fout, node->left);
            fprintf(fout, "next%d\n", tempnum);

            printf("LABELCOUNTER\t%d\n", Labelcounter);
            Labelcounter++;
            CompileFunction(fout, node->right, func);

            printf("LABELCOUNTER\t%d\n", Labelcounter);
            fprintf(fout, "next%d:\n", tempnum);
            Labelcounter++;
            break;

        case WHILE:
            tempnum = Labelcounter;

            fprintf(fout, "label%d:\n", tempnum);
            CompileComparison(fout, node->left);

            Labelcounter++;
            fprintf(fout, "next%d\n", tempnum);
            CompileFunction(fout, node->right, func);

            fprintf(fout, "JUMP\tlabel%d\n", tempnum);
            fprintf(fout, "next%d:\n", tempnum);
            Labelcounter++;
            break;

        case SETWINDOW:
            CompileExpression(fout, node->left);
            CompileExpression(fout, node->right);

            fprintf(fout, "WINDOWSET\n");
            break;

        case SETPIXEL:
            CompileExpression(fout, node->right);
            CompileExpression(fout, node->left->right);
            CompileExpression(fout, node->left->left);

            fprintf(fout, "PIXEL\n");
            break;

        case CIRCLE:
            CompileExpression(fout, node->right->right);
            CompileExpression(fout, node->right->left);
            CompileExpression(fout, node->left->right);
            CompileExpression(fout, node->left->left);

            fprintf(fout, "CIRCLE\n");
            break;

        case LINE:
            CompileExpression(fout, node->right->right);
            CompileExpression(fout, node->right->left);
            CompileExpression(fout, node->left->right);
            CompileExpression(fout, node->left->left->right);
            CompileExpression(fout, node->left->left->left);

            fprintf(fout, "LINE\n");
            break;

        case VLINE:
            CompileExpression(fout, node->right->right);
            CompileExpression(fout, node->right->left);
            CompileExpression(fout, node->left->right);
            CompileExpression(fout, node->left->left);

            fprintf(fout, "VLINE\n");
            break;

        case PARTCLEAR:
            CompileExpression(fout, node->right->right);
            CompileExpression(fout, node->right->left);
            CompileExpression(fout, node->left->right);
            CompileExpression(fout, node->left->left);

            fprintf(fout, "PARTCLEAR\n");
            break;

        case HLINE:
            CompileExpression(fout, node->right->right);
            CompileExpression(fout, node->right->left);
            CompileExpression(fout, node->left->right);
            CompileExpression(fout, node->left->left);

            fprintf(fout, "HLINE\n");
            break;

        case SHOW:
            fprintf(fout, "SHOW\n");
            break;

        case CALL:
            fprintf(fout, "CALL\t%s\n", func[node->left->data.data]);
            break;

        case RETURN:
            fprintf(fout, "RET\n");
            break;
    }
};

void CompileFunction(FILE* fout, node_t* node, char** func)
{
    if(!node)
        return;

    switch(node->data.data)
    {
        case OPERATE:
            CompileOperator(fout, node->left, func);
            break;

        case VARS:
            CompileVar(fout, node->left);
            break;

        case FINISHPROGRAM:
            fprintf(fout, "END\n");
            break;
    }

    CompileFunction(fout, node->right, func);
}

#undef DEF_REG

void LaunchProgram(FILE* fin)
{
    char temp[STR_MAX] = "";
    fscanf(fin, "%[a-z:]", temp);
    int tempnum = 0;
    printf("PRIVET\t%s\n", temp);
    char** var = (char**) calloc(VAR_NUM, sizeof(char*));
    for (int i = 0; i < VAR_NUM; i++)
    {
        var[i] = (char*) calloc(VAR_MAX, sizeof(char));
    }
    int varnum = 0;
    printf("PRIVET\n");

    char** func = (char**) calloc(MAX_FUNC_NUM, sizeof(char*));
    for (int i = 0; i < MAX_FUNC_NUM; i++)
    {
        func[i] = (char*) calloc(STR_MAX, sizeof(char));
    }
    int funcnum = 0;
    printf("PRIVET\n");

    while(fscanf(fin, "%*[, \t]%[A-Za-z]", temp) != 0)
    {
        strcpy(var[varnum], temp);
        varnum++;
    }
    printf("PRIVET10\n");

    fscanf(fin, "%*[;]");

    fscanf(fin, "%s", temp);

    while(fscanf(fin, "%*[, \t]%[A-Za-z]", temp) != 0)
    {
        strcpy(func[funcnum], temp);
        funcnum++;
    }

    fscanf(fin, "%*[;]");
    printf("PRIVET\n");

    char str[READ] = "";

    int ptr1 = ftell(fin);
    fseek(fin, sizeof(char), SEEK_END);
    long ptr2 = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    fread(str, sizeof(char), ptr2, fin);

    //printf("%s\n", str);

    //printf("PTR1\t%ld\n", ptr1);
    printf("PRIVET1\n");
    node_t** tokens = Tokens(str, &ptr1, var, varnum, func, funcnum);

    for (int i = ptr1-10; i < ptr1 + 10; i++)
        printf("I\t%d\t%c\n", i, str[i]);

    ptr1++;
    for (int i = 1; i <= tokens[0]->data.data; i++)
        printf("TYPE\t%d\tDATA\t%d\tI\t%d\n", tokens[i]->data.type, tokens[i]->data.data, i);

    int ptr3 = 1;
    node_t* main = GetFunctionNode(tokens, &ptr3);

    FILE* fout = fopen("output.dot", "w");
    TreeGraph(fout, main);
    fclose(fout);

    FILE* fcompile = fopen("C:\\Temp\\compile_quadratic_equations.txt", "w");
    CompileFunction(fcompile, main, func);

    for (int i = 0; i < funcnum; i++)
    {
        ptr3++;
        ptr3++;
        printf("TOKEN\tTYPE\t%d\tDATA\t%d\n", tokens[ptr3]->data.type, tokens[ptr3]->data.data);
        fprintf(fout, "%s:\n", func[tokens[ptr3]->data.data]);
        ptr3++;
        main = GetFunctionNode(tokens, &ptr3);
        CompileFunction(fcompile, main, func);
    }

    fclose(fcompile);

}

void TreeVars(FILE* fout, node_t* node)
{
    if (!node)
        return;


}

void TreeRestore(FILE* fout, node_t* node)
{

}
/************************************************************************************************************/
void TreeCompile(FILE* fout, node_t* node)
{
    if (!node)
        return;

    TreeCompile(fout, node->left);
    TreeCompile(fout, node->right);

    switch(node->data.type)
    {
        case CONST:
            fprintf(fout, "PUSH\t%d\n", node->data.data);
            break;

        case VAR:
            fprintf(fout, "POPREG\t");
            switch (node->data.data)
            {
            #define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "%s\n", #name);\
                break;

            #include "Registers.h"

            #undef DEF_REG
            }
            break;

        case OPERATORCODE:
            switch (node->data.data)
            {
                case PLUS:
                    PRINT("ADD\n");
                    break;

                case MINUS:
                    PRINT("SUB\n");
                    PRINT("PUSH -1\n");
                    PRINT("MUL\n");
                    break;

                case MUL:
                    PRINT("MUL\n");
                    break;

                case DIV:
                    PRINT("PUSHREG\twild\n");
                    PRINT("PUSHREG\tcatmemes\n");
                    PRINT("POPREG\twild\n");
                    PRINT("POPREG\tcatmemes\n");
                    PRINT("DIV\n");
                    break;

                case SINE:
                    PRINT("SIN\n");
                    break;

                case COSINE:
                    PRINT("COS\n");
                    break;

                case DEG:
                    PRINT("POW\n");
                    break;

                case LN:
                    PRINT("LN\n");
                    break;

                case SQRT:
                    PRINT("SQRT\n");
                    break;
            }
            break;

        case VARMEAN:
            switch (node->data.data)
            {
                case EQUAL:
                    switch (node->left->data.data)
                    {
#define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "PUSHREG\t%s\n", #name);\
                break;

#include "Registers.h"

#undef DEF_REG
                    }
                    break;

                case EQUALPLUS:
                    switch (node->left->data.data)
                    {
#define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "POPREG\t%s\n", #name);\
                break;

#include "Registers.h"

#undef DEF_REG
                    }

                    fprintf(fout, "ADD\n");

                    switch (node->left->data.data)
                    {
#define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "PUSHREG\t%s\n", #name);\
                break;

#include "Registers.h"

#undef DEF_REG
                    }
                    break;

                case EQUALMUL:
                    switch (node->left->data.data)
                    {
#define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "POPREG\t%s\n", #name);\
                break;

#include "Registers.h"

#undef DEF_REG
                    }

                    fprintf(fout, "MUL\n");

                    switch (node->left->data.data)
                    {
#define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "PUSHREG\t%s\n", #name);\
                break;

#include "Registers.h"

#undef DEF_REG
                    }
                    break;

            }
            break;

        case OPERATORS:
            switch (node->data.data)
            {
                case OUTPUT:
                    fprintf(fout, "OUTPOP\n");
                    break;

                case INPUT:
                    fprintf(fout, "IN\n");
                    switch (node->left->data.data)
                    {
#define DEF_REG(name, num)\
            case num:\
                fprintf(fout, "PUSHREG\t%s\n", #name);\
                break;

#include "Registers.h"

#undef DEF_REG
                    }
                    break;

            }
            break;

        case FUNCTION:
            if (node->data.data == FINISHPROGRAM)
                PRINT("END\n");
            break;
    }
}

#endif //CATLANGUAGE_FRONTEND_H
