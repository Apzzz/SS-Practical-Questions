/*		
		EXPERIMENT NO: 5
		EXPERIMENT NAME: PASS 1 OF 2 PASS ASSEMBLER
		AIM: To implement pass 1 of a 2 pass assembler
		AUTHOR: APARNA DINESH
		Date: 09/12/2021
*/

// ------PROGRAM------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	char opcode[10], operand[10], label[10], mnemonic[10], code[10];
	FILE *input, *optab, *symbol, *output;
	int locctr, start, length;

	input = fopen("/home/nwlab6/Sruthi/Exp-5/input.txt", "r");
	optab = fopen("/home/nwlab6/Sruthi/Exp-5/optab.txt", "r");
	symbol = fopen("/home/nwlab6/Sruthi/Exp-5/symbol.txt", "w");
	output = fopen("/home/nwlab6/Sruthi/Exp-5/output.txt", "w");

	fscanf(input, "%s\t%s\t%s", label, opcode, operand);
	if(strcmp(opcode, "START") == 0)
	{
		start = atoi(operand);
		locctr = start;
		fprintf(output, "\t%s\t%s\t%X\n", label, opcode, locctr + 3096);
		fscanf(input, "%s\t%s\t%s", label, opcode, operand);
	}
	else
		locctr = 0;

	while(strcmp(opcode, "END") != 0)
	{
		fprintf(output, "%X\t", locctr + 3096);
		if(strcmp(label, "-") != 0)
			fprintf(symbol, "%s\t%X\n", label, locctr + 3096);

		fseek(optab, SEEK_SET, 0);
		fscanf(optab, "%s\t%s", code, mnemonic);

		while(strcmp(code, "END") != 0)
		{
			if(strcmp(opcode, code) == 0)
			{
				locctr += 3;
				break;
			}
			fscanf(optab, "%s\t%s", code, mnemonic);
		}

		if(strcmp(opcode, "WORD") == 0)
			locctr += 3;
		else if(strcmp(opcode, "RESW") == 0)
			locctr += 3*(atoi(operand));
		else if(strcmp(opcode, "RESB") == 0)
			locctr += atoi(operand);
		else if(strcmp(opcode, "BYTE") == 0)
		{
			char ch = operand[0];
			if(strcmp(&ch, "X") == 0)
				locctr += 1;
			else
				locctr += strlen(operand) - 3;
		}

		fprintf(output, "%s\t%s\t%s\t\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }
    fprintf(output, "\t%s\t%s\t%s\n", label, opcode, operand);
    length = locctr - start;

    printf("Length of code = %X\n", length);
    fclose(input);
    fclose(optab);
    fclose(symbol);
    fclose(output);
}

// ------input.txt------

// PGM		START	1000
// -		LDA		ALPHA
// -		ADD 	INCR
// -		SUB		ONE
// -		STA 	BETA
// ALPHA	WORD	1
// INCR	RESW	1
// ONE		WORD	1
// BETA	RESW	1
// -		END		-

// ------optab.txt------

// START	-
// LDA		00
// ADD		18
// SUB		1C
// STA		0C
// END		-

// ------symbol.txt------

// ALPHA	100C
// INCR	100F
// ONE		1012
// BETA	1015

// ------output.txt------

// 		PGM		START	1000
// 1000	-		LDA		ALPHA	
// 1003	-		ADD		INCR	
// 1006	-		SUB		ONE	
// 1009	-		STA		BETA	
// 100C	ALPHA	WORD	1	
// 100F	INCR	RESW	1	
// 1012	ONE		WORD	1	
// 1015	BETA	RESW	1	
// 		-		END		-

// ------OUTPUT------

// Length of code = 18
