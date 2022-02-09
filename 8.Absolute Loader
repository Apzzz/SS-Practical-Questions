#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *fp,*outp;
    int i, addr1, l, j, staddr1;
    char name[10], name2[10], len[10], line[1000], name1[10], addr[10], rec[10], ch, staddr[10];
    fp = fopen("input.txt", "r");
    outp=fopen("output.txt","w");
    fscanf(fp, "%s", line);
    int count = 0, a = 0, b = 0, c = 0;
    for (i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == '^')
        {
            count++;
            continue;
        }
        if (count == 1)
        {
            name1[a] = line[i];
            a++;
        }
        else if (count == 2)
        {
            name2[b] = line[i];
            b++;
        }
        else if (count == 3)
        {
            len[c] = line[i];
            c++;
        }
    }

    name1[a] = '\0';
    name2[b] = '\0';
    len[c] = '\0';
    printf("Program Name : %s\n\n", name1);
    fprintf(outp,"Program Name : %s\n\n", name1);
   /* printf("Starting Address : %s\n\n", name2);
    fprintf(outp,"Starting Address : %s\n\n", name2);*/
    int x=0;
    do
    {
        fscanf(fp, "%s", line);
        if (line[0] == 'T')
        {
            count = 0;
            a = 0;
            for (i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == '^')
                {
                    count++;
                    continue;
                }
                if (count == 1)
                {
                    staddr[a] = line[i];
                    a++;
                }
                else if (count == 3)
                {
                    break;
                }
            }
            staddr[a] = '\0';
            staddr1 = strtol(staddr, NULL, 16);
            i = 12;
            if (x==0)
            {
                printf("\n%X\t", staddr1);
                fprintf(outp,"\n%X\t", staddr1);
            }
            while (line[i] != '\0')
            {
                
                if (line[i] != '^')
                {
                    x++;
                    int objc1=line[i];
                    int objc2=line[i+1];
                    objc1-=48;
                    if(objc1>10) objc1-=7;
                    objc2-=48;
                    if(objc2>10) objc2-=7;
                    int objc=objc1*16+objc2;
                    printf("%02X", objc);
                    fprintf(outp,"%02X", objc);
                    if(x%4==0)
                        {
                            printf(" ");
                            fprintf(outp," ");
                        }
                    staddr1++;
                    i = i + 2;
                }
                else
                    i++;
                if(x==16)
                {
                    printf("\n%X\t", staddr1);
                    fprintf(outp,"\n%X\t", staddr1);
                    x=0;
                    
                }
            }
        }
        else if (line[0] = 'E')
        {
            
            break;
        }
    } while (!feof(fp));
    fclose(fp);
    fclose(outp);
}
