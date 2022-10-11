
#include<stdio.h>
#include<stdlib.h>

int file[20], start[20], len[20], block[20][20], n, st, l, flag;

void clear()
{
	for(int i=0; i<50; i++)
		file[i] = 0;
}

void sequential()
{
	printf("\nEnter the no of files\n");
	scanf("%d", &n);

	for(int i=0; i<n; i++)
	{
		flag = 0;

		printf("\nEnter the starting block and length of file %d\n", i+1);
		scanf("%d%d", &st, &l);

		for(int k=st; k<st+l; k++)
		{
			if(file[k] == 0)
				flag++;
		}

		if(flag == l)
		{
			for(int k=st; k<st+l; k++)
				file[k] = 1;
			start[i] = st;
			len[i] = l;
		}
		else
		{
			printf("File %d cannot be allocated\n", i+1);
			start[i] = -1;
			len[i] = 0;
			i--;
		}
	}

	printf("\n\nFile\tStart\tLength\n");

	for(int i=0; i<n; i++)
	{
		if(start[i] != -1)
			printf("%d\t%d\t%d\n", i+1, start[i], len[i]);
	}
}

void indexed()
{
	printf("\nEnter the no of files\n");
	scanf("%d", &n);

	for(int i=0; i<n; i++)
	{
		flag = 0;

		printf("\nEnter the index block and length of file %d\n", i+1);
		scanf("%d%d", &st, &l);

		printf("Enter the blocks\n");
		for(int k=0; k<l; k++)
		{
			scanf("%d", &block[i][k]);
			if(file[block[i][k]]==0)
				flag++;
		}

		if(file[st] == 0)
			flag++;

		if(flag == l+1)
		{
			for(int k=0; k<l; k++)
				file[block[i][k]] = 1;

			file[st] = 1;
			start[i] = st;
			len[i] = l;
		}
		else
		{
			printf("File %d cannot be allocated\n", i+1);
			start[i] = -1;
			len[i] = 0;
			i--;
		}
	}

	printf("\n\nFile\tIndex\tLength\tBlocks\n");

	for(int i=0; i<n; i++)
	{
		if(start[i] != -1)
			printf("%d\t%d\t%d\t", i+1, start[i], len[i]);

		for(int k=0; k<len[i]; k++)
				printf("%d ", block[i][k]);
		printf("\n");
	}	
}

void linked()
{
	printf("\nEnter the no of files\n");
	scanf("%d", &n);

	for(int i=0; i<n; i++)
	{
		flag = 0;

		printf("\nEnter the starting block and length of file %d\n", i+1);
		scanf("%d%d", &st, &l);

		printf("Enter the blocks\n");
		for(int k=0; k<l; k++)
		{
			scanf("%d", &block[i][k]);
			if(file[block[i][k]]==0)
				flag++;
		}

		if(file[st] == 0)
			flag++;

		if(flag == l+1)
		{
			for(int k=0; k<l; k++)
				file[block[i][k]] = 1;

			file[st] = 1;
			start[i] = st;
			len[i] = l;
		}
		else
		{
			printf("File %d cannot be allocated\n", i+1);
			start[i] = -1;
			len[i] = 0;
			i--;
		}
	}

	printf("\n\nFile\tStart\tLength\tBlocks\n");

	for(int i=0; i<n; i++)
	{
		if(start[i] != -1)
			printf("%d\t%d\t%d\t", i+1, start[i], len[i]);

		int k;
		printf("%d->", start[i]);
		for(k=0; k<len[i]-1; k++)
				printf("%d->", block[i][k]);
		printf("%d\n", block[i][k]);
	}	
}

void main()
{
	int ch;

	while(1)
	{
		printf("\n1.Sequential \n2.Indexed \n3.Linked \n4.Exit \n");
		printf("\nEnter your choice\n");
		scanf("%d", &ch);

		if(ch == 4)
			exit(0);

		switch(ch)
		{
			case 1:
				clear();
				sequential();
				break;

			case 2:
				clear();
				indexed();
				break;

			case 3:
				clear();
				linked();
				break;

			case 4:
				exit(0);

			default:
				printf("Invalid choice\n");
		}
	}
}

