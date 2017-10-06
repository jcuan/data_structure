#include <stdio.h>

class BitreeTools
{
  public:
    //写到文件里
    static void write2dot(Bitree tree, FILE *fw);
    static void visualization(Bitree tree, const char *filename);
};