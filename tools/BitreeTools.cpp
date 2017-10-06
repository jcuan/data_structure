#include <stdlib.h>
#include "Bitree.h"
#include "BitreeTools.h"
#include <stdio.h>

//代码来自http://blog.csdn.net/robin_xu_shuai/article/details/53406205#

void BitreeTools::write2dot(Bitree tree, FILE *fw)
{
    if (tree == NULL)
        return;
    else
    {
        fprintf(fw, "%d [label = \"<f0> | <f1> %d | <f2> \", color = black, fontcolor = white, style = filled];\n", tree->value, tree->value);
    }
    if (tree->left)
    {
        fprintf(fw, "%d [label = \"<f0> | <f1> %d | <f2> \", color = black, fontcolor = white, style = filled];\n", tree->left->value, tree->left->value);
        fprintf(fw, "%d:f0:sw -> %d:f1;\n", tree->value, tree->left->value);
    }
    if (tree->right)
    {
        fprintf(fw, "%d [label = \"<f0> | <f1> %d | <f2> \", color = black, fontcolor = white, style = filled];\n", tree->right->value, tree->right->value);
        fprintf(fw, "%d:f2:se -> %d:f1;\n", tree->value, tree->right->value);
    }
    write2dot(tree->left, fw);
    write2dot(tree->right, fw);
}

void BitreeTools::visualization(Bitree tree, const char* filename)
{
    FILE *fw;
    if (NULL == (fw = fopen(filename, "w")))
    {
        printf("open file error");
        exit(0);
    }
    fprintf(fw, "digraph\n{\nnode [shape = Mrecord, style = filled, color = black, fontcolor = white];\n");
    write2dot(tree, fw);
    fprintf(fw, "}");
    fclose(fw);
}