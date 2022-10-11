#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input, *argtab, *deftab, *nametab, *output;
int expanding = 0;
char label[100], opcode[100], operand[100], mname[100], msadd[100], meadd[100];

void processline();
void getline();
void define();
void expand();

int main(int argc, char const *argv[])
{
    input = fopen("input.txt", "r+");
    deftab = fopen("deftab.txt", "w+");
    output = fopen("output.txt", "w+");
    nametab = fopen("nametab.txt", "w+");

    while (!feof(input))
    {
        getline();
        processline();
    }
    return 0;
}

void getline()
{
    if (expanding == 1)
        fscanf(deftab, "%s\t%s\t%s", label, opcode, operand);
    else
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
}

void processline()
{
    fseek(nametab, SEEK_SET, 0);
    int check = 0;
    fscanf(nametab, "%s\t%s\t%s", mname, msadd, meadd);
    // printf("a%s\t%s\t%s", mname, msadd, meadd);
    while (!feof(nametab))
    {
        if (strcmp(mname, opcode) == 0)
        {
            check = 1;
            // printf("xxx%s\t%s\t%s", mname, msadd, meadd);
            break;
        }
        fscanf(nametab, "%s\t%s\t%s", mname, msadd, meadd);
    }
    if (check == 1)
    {
        expand();
    }
    else if (strcmp(opcode, "MACRO") == 0)
    {
        define();
    }
    else
    {
        if (strcmp(opcode, "MEND") != 0)
            fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
    }
}

void define()
{
    // fseek(deftab, SEEK_END, 0);
    // fseek(nametab, SEEK_END, 0);
    fprintf(nametab, "%s\t%d\t", label, ftell(deftab));
    fprintf(deftab, "%s\t%s\t%s\n", label, opcode, operand);

    char Arggument[100][100];
    int i = 0, count = 0;
    for (int k = 0; k < strlen(operand); k++)
    {
        if (operand[k] == ',')
        {
            Arggument[count][i++] = '\0';
            count++;
            i = 0;
            continue;
        }
        Arggument[count][i++] = operand[k];
    }
    Arggument[count][i++] = '\0';
    count++;
    int level = 1;
    while (level > 0)
    {
        getline();
        int ii;
        for (ii = 0; ii < count; ii++)
        {
            if (strcmp(Arggument[ii], operand) == 0)
            {
                // printf("w");
                break;
            }
        }
        if (strcmp(opcode, "MEND") != 0)
            fprintf(deftab, "%s\t%s\t?%d\n", label, opcode, ii + 1);
        if (strcmp(opcode, "MACRO") == 0)
            level++;
        if (strcmp(opcode, "MEND") == 0)
        {
            level--;
            fprintf(deftab, "%s\t%s\t%s\n", label, opcode, operand);
        }
    }
    fprintf(nametab, "%d\n", ftell(deftab));
}

void expand()
{
    expanding = 1;
    int aadd = strtol(msadd, NULL, 10);
    // printf("%i",aadd);
    fseek(deftab, SEEK_SET, aadd);
    fscanf(deftab, "%s\t%s\t%s", label, opcode, operand);
    char Arggument[100][100];
    int i = 0, count = 0;
    for (int k = 0; k < strlen(operand); k++)
    {
        if (operand[k] == ',')
        {
            Arggument[count][i++] = '\0';
            count++;
            i = 0;
            continue;
        }
        Arggument[count][i++] = operand[k];
    }
    Arggument[count][i++] = '\0';
    count++;
    argtab = fopen("argtab.txt", "w+");
    for (int y = 0; y < count; y++)
    {
        fprintf(argtab, "%s\n", Arggument[y] + 1);
    }
    fprintf(output, "-\t%s\t%s\n", opcode, operand);
    while (strcmp(opcode, "MEND") != 0)
    {
        getline();
        processline();
    }

    expanding = 0;
}

/*
EX1 MACRO &A,&B
- LDA &A
- STA &B
- MEND -
EX2 MACRO &A,&B,&C
- LDA &A
- STA &C
- STA &B
- MEND -
SAMPLE START 1000
- EX1 N1,N2
N1 RESW 1
N3 RESW 1
- EX2 N1,N2
N2 RESW 1
- END -
*/
