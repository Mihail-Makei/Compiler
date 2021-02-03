#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Config.h"
#include "Differentiator.h"
#include "MyTree.h"
#include "Frontend.h"

int main() {
    FILE* fin = fopen("Cat.txt", "r");
    LaunchProgram(fin);
    fclose(fin);
    return 0;
    /**char text[1000] = "";
    int length = 0;

    char** var = (char**) calloc(VAR_NUM, sizeof(char*));
    for (int i = 0; i < VAR_NUM; i++)
    {
        var[i] = (char*) calloc(VAR_MAX, sizeof(char));
    }

    strcpy(var[0], "x");
    printf("%s\n", var[0]);
    strcpy(var[1], "y");
    printf("%s\n", var[1]);
    strcpy(var[2], "z");
    printf("%s\n", var[2]);
    strcpy(var[3], "d");


    FILE* fin = fopen("input.txt", "r");
    fseek(fin, sizeof(char), SEEK_END);
    length = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    fread(text, sizeof(char), length, fin);
    fclose(fin);

    printf("%s\n", text);

    int ptr = 0;
    node_t** tokens = Tokens(text, &ptr, var, 3);

    for (int i = 1; i <= tokens[0]->data.data; i++)
        printf("TYPE\t%d\tDATA\t%d\t%d\n", tokens[i]->data.type, tokens[i]->data.data, i);

    ptr = 1;
    node_t* tree = GetFunctionNode(tokens, &ptr);

    FILE* fout = fopen("output.dot", "w");
    TreeGraph(fout, tree);
    fclose(fout);

    FILE* fcompile = fopen("C:\\Temp\\compile.txt", "w");
    CompileFunction(fout, tree);
    fclose(fcompile);
    return 0;*/
}