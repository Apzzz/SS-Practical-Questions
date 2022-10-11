/*      
        EXPERIMENT NO: 
        EXPERIMENT NAME: SINGLE PASS ASSEMBLER
        AIM: To implement single pass assembler
        AUTHOR: SRUTHI SAGAR
        Date: 13/01/2022
*/

// ------PROGRAM------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	FILE *f1, *f2, *f3, *f4, *f5, *f6;
	int lc, sa, i = 0, j = 0, m[10], pgmlen, len, k, len1, l = 0;
	char name[10], opnd[10], la[10], mne[10], s1[10], mne1[10], opnd1[10], sym[10], symaddr[10], obj1[10], obj2[10], s2[10], q[10], s3[10];

	f1 = fopen("input.txt", "r");
	f2 = fopen("optab.txt", "r");
	f3 = fopen("symtab.txt", "w+");
	f4 = fopen("symtab1.txt", "w+");
	f5 = fopen("output.txt", "w+");
	f6 = fopen("result.txt", "w+");

	fscanf(f1, "%s%s%s", la, mne, opnd);
	if (strcmp(mne, "START") == 0)
	{
		sa = atoi(opnd);
		strcpy(name, la);
		lc = sa;
	}
	strcpy(s1, "*");

	fscanf(f1, "%s%s%s", la, mne, opnd);
	while (strcmp(mne, "END") != 0)
	{
		if (strcmp(la, "-") == 0)
		{
			fscanf(f2, "%s%s", mne1, opnd1);
			while (!feof(f2))
			{
				if (strcmp(mne1, mne) == 0)
				{
					m[i] = lc + 1;
					fprintf(f3, "%s\t%s\n", opnd, s1);
					fprintf(f5, "%s\t0000\n", opnd1);
					lc = lc + 3;
					i = i + 1;
					break;
				}
				else
					fscanf(f2, "%s%s", mne1, opnd1);
			}
		}
		else
		{
			fseek(f3, SEEK_SET, 0);
			fscanf(f3, "%s%s", sym, symaddr);

			while (!feof(f3))
			{
				if (strcmp(sym, la) == 0)
				{
					fprintf(f4, "%s\t%06X\n", la, lc + 3096);
					fprintf(f5, "%06x\t%x\n", m[j++] + 3096, lc + 3096);
					i = i + 1;
					break;
				}
				else
				fscanf(f3, "%s%s", sym, symaddr);
			}
			if (strcmp(mne, "RESW") == 0)
				lc = lc + 3 * atoi(opnd);
			else if (strcmp(mne, "BYTE") == 0)
			{
				strcpy(s2, "-");
				len = strlen(opnd);
				lc = lc + len - 2;
				for (k = 2; k < len; k++)
				{
					q[l] = opnd[k];
					l = l + 1;
				}
				fprintf(f5, "%s\t%s\n", q, s2);
				break;
			}
			else if (strcmp(mne, "RESB") == 0)
				lc = lc + atoi(opnd);
			else if (strcmp(mne, "WORD") == 0)
			{
				strcpy(s3, "#");
				lc = lc + 3;
				fprintf(f5, "%s\t%s\n", opnd, s3);
				break;
			}
		}

		fseek(f2, SEEK_SET, 0);
		fscanf(f1, "%s%s%s", la, mne, opnd);
	}

	fseek(f5, SEEK_SET, 0);
	pgmlen = lc - sa;
	fprintf(f6, "H^%s^%06d^%06X\n", name, sa, pgmlen);
	fprintf(f6, "T^");
	fprintf(f6, "00%d^0%x", sa, pgmlen);
	fscanf(f5, "%s%s", obj1, obj2);

	while (!feof(f5))
	{
		if (strcmp(obj2, "0000") == 0)
			fprintf(f6, "^%s%s", obj1, obj2);
		else if (strcmp(obj2, "-") == 0)
		{
			fprintf(f6, "^");
			len1 = strlen(obj1);
			for (k = 0; k < len1; k++)
				fprintf(f6, "%d", obj1[k]);
		}
		else if (strcmp(obj2, "#") == 0)
		{
			fprintf(f6, "^");
			fprintf(f6, "%s", obj1);
		}
		fscanf(f5, "%s%s", obj1, obj2);
	}

	fseek(f5, SEEK_SET, 0);
	fscanf(f5, "%s%s", obj1, obj2);
	while (!feof(f5))
	{
		if (strcmp(obj2, "0000") != 0)
		{
			if (strcmp(obj2, "-") != 0)
			{
				if (strcmp(obj2, "#") != 0)
				{
					fprintf(f6, "\n");
					fprintf(f6, "T^%s^02^00%s", obj1, obj2);
				}
			}
		}
		fscanf(f5, "%s%s", obj1, obj2);
	}
	fprintf(f6, "\nE^00%d", sa);

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	fclose(f5);
	fclose(f6);
}

// ------input.txt------

// COPY	START	1000
// -		LDA		ALPHA
// -		STA		BETA
// ALPHA	RESW	1
// BETA	RESW	1
// -		END		-

// ------optab.txt------

// LDA		00
// STA		23
// LDCH	15
// STCH	18

// ------symbtab1.txt------

// ALPHA	001006
// BETA	001009

// ------result.txt------

// H^COPY^001000^00000C
// T^001000^0c^000000^230000
// T^001001^02^001006
// T^001004^02^001009
// E^001000