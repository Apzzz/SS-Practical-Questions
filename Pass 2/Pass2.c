/*      
        EXPERIMENT NO: 6
        EXPERIMENT NAME: PASS 2 OF 2 PASS ASSEMBLER
        AIM: To implement pass 2 of a 2 pass assembler
        AUTHOR: APARNA DINESH
        Date: 16/12/2021
*/

// ------PROGRAM------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct struct1
{
    char a[100];
} arr[100];

struct struct2
{
    int len;
    int ind;
} leng[100];

void main()
{
    FILE *input, *optab, *length, *symbol, *output;
    int op1[10], txtlen, txtlen1, i, j = 0, len;
    char abc[10] = {'0','0','0','0'}, add[5], symadd[5], op[5], start[10], temp[30], line[20], label[20], mne[10], operand[10], symtab[10], opmne[10];

    input = fopen("input.txt", "r");
    length = fopen("length.txt", "r");
    optab = fopen("optab.txt", "r");
    symbol = fopen("symbol.txt", "r");
    output = fopen("output.txt", "w");

    leng[0].ind=0;
    leng[0].len=0;
    fscanf(input, "%s%s%s%s", add, label, mne, operand);

    if (strcmp(mne, "START") == 0)
    {
        strcpy(start, operand);
        fscanf(length, "%d", &len);
    }

    fprintf(output,"H^%s^%06d^%X",label,atoi(start),len);
    fscanf(input, "%s%s%s%s", add, label, mne, operand);
    int co = 0, co_len = 1, c=0;

    while (strcmp(mne, "END") != 0)
    {
        fscanf(optab, "%s%s", opmne, op);
        while (!feof(optab))
        {
            if (strcmp(mne, opmne) == 0)
            {
                while (!feof(symbol))
                {
                    fscanf(symbol, "%s%s", symadd, symtab);
                    if (strcmp(operand, symtab) == 0)
                    {
                        strcpy(arr[c].a, op);
                        strcat(arr[c++].a, symadd);
                        co += strlen(op);
                        co += strlen(symadd);
                        if (co >= 60)
                        {
                            leng[co_len].ind = c-1;
                            leng[co_len++].len = co - strlen(op) - strlen(symadd);
                            co = 0;
                            co+=strlen(op) + strlen(symadd);
                        }
                        break;
                    }
                }
                fseek(symbol,SEEK_SET,0);
                break;
            }
            else
                fscanf(optab, "%s%s", opmne, op);
        }
        fseek(optab,SEEK_SET,0);

        if ((strcmp(mne, "BYTE") == 0) || (strcmp(mne, "WORD") == 0))
        {
            if (strcmp(mne, "WORD") == 0)
            {
                strcpy(abc,"00000");
                strcpy(arr[c++].a, strcat(abc, operand));
                co += strlen(operand);
                co += 5;
                if (co >= 60)
                {
                    leng[co_len].ind = c-1;
                    leng[co_len++].len = co - strlen(operand) - 5;
                    co = 0;
                    co+=strlen(operand) + 5;
                }
            }
            else
            {
                len = strlen(operand);
                int aqw[100], asd = 0;
                char str[100];

                for (i = 2; i < len - 1; i++)
                    aqw[asd++] = (int)operand[i];
                int index = 0;

                for (i = 0; i < asd; i++)
                    index += sprintf(&str[index], "%d", aqw[i]);
                strcpy(arr[c++].a, str);
                co += strlen(str);
                if (co >= 60)
                {
                    leng[co_len].ind = c-1;
                    leng[co_len++].len = co - strlen(str);
                    co = 0;
                    co+=strlen(str);
                }
            }
        }
        fscanf(input, "%s%s%s%s", add, label, mne, operand);
    }

    if (co < 60)
    {
        leng[co_len].ind = c;
        leng[co_len++].len = co;
    }

    fprintf(output, "\n");
    int a = atoi(start);

    for (int i = 0; i < co_len - 1; i++)
    {
        a = a+leng[i].len/2;
        fprintf(output, "T^00%X", a+3096);
        fprintf(output, "^%X", leng[i+1].len/2);
        for (int j = leng[i].ind; j < leng[i+1].ind; j++)
            fprintf(output, "^%s", arr[j].a);
        fprintf(output, "\n");
    }
    
    fprintf(output, "E^%06d", atoi(start));
    fclose(input);
    fclose(optab);
    fclose(symbol);
    fclose(length);
    fclose(output);
}

// ------input.txt------

// -    PGM START   1000
// 1000 -   LDA ALPHA   
// 1003 -   ADD INCR    
// 1006 -   SUB ONE 
// 1009 -   STA BETA    
// 100C ALPHA   WORD    1   
// 100F INCR    RESW    1   
// 1012 ONE     WORD    1   
// 1015 BETA    RESW    1   
// 1018 -   END -

// ------optab.txt------

// START    -
// LDA      00
// ADD      18
// SUB      1C
// STA      0C
// END      -

// ------symbol.txt------

// 100C ALPHA   
// 100F INCR    
// 1012 ONE     
// 1015 BETA    

// ------length.txt------

// 24

// ------output.txt------

// H^PGM^001000^18
// T^001000^12^00100C^18100F^1C1012^0C1015^000001^000001
// E^001000
