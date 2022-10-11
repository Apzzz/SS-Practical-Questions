/*		
		EXPERIMENT NO: 4
		EXPERIMENT NAME: PAGE REPLACEMENT ALGORITHMS
		AIM: To simulate FIFO, LRU and LFU page replacement algorithms
		AUTHOR: SRUTHI SAGAR
		Date: 07/12/2021
*/

// ------PROGRAM------

#include <stdio.h>
#include <stdlib.h>

int n, frameno, page[50], frame[10], move=0, flag, count=0, count1, repindex, check[50], hit=0, coun[50], time[50], least, minTime, temp;

void display()
{
	for(int x=0; x<frameno; x++)
		printf("%d\t",frame[x]);
	printf("\n");
}

void clear()
{
	for(int i=0; i<frameno; i++)
		frame[i] =- 1;
}

void fifo()
{
	clear();
	printf("\nReference string\tFrames\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t\t",page[i]);
		flag=0;
		for(int j=0; j<frameno; j++)
		{
			if(page[i] == frame[j])
			{
				flag = 1;
				display();
				break;
			}
		}
		if(flag == 0)
		{
			frame[move] = page[i];
			move = (move+1)%frameno;
			count++;
			display();
		}
	}
	printf("Page faults in FIFO = %d\n", count);
}

void lru()
{
	clear();
	move = 0,count = 0;
	for(int j=0; j<50; j++)
		check[j] = 0;

	printf("\nReference string\tFrames\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t\t", page[i]);
		flag = 0;
		for(int j=0; j<frameno; j++)
		{
			if(page[i] == frame[j])
			{
				flag = 1;
				display();
				break;
			}
		}
		if(flag==0 && count<frameno)
		{
			frame[move] = page[i];
			move = (move+1)%frameno;
			count++;
			display();
		}
		else if(flag == 0)
		{
			count1 = 0;
			for(int j=i-1; j>=0; j--)
			{
				for(int k=0; k<frameno; k++)
				{
					if(page[j]==frame[k] && check[page[j]]==0)
					{
						check[page[j]] = 1;
						count1++;
						repindex = k;
						k = frameno;
					}
				}
				if(count1 == frameno) 
					break;
			}
			frame[repindex] = page[i];
			count++;
			display();
		}
		for(int j=0; j<50; j++)
			check[j] = 0;
	}
	printf("Page faults in LRU = %d\n", count);
}

void lfu()
{
	clear();
	printf("\nReference string\tFrames\n");
	for(int i=0; i<n; i++)
	{
		printf("%d\t\t\t",page[i]);
		coun[page[i]]++;
		time[page[i]] = i;
		flag = 1;
		least = frame[0];

		for(int j=0; j<frameno; j++)
		{
			if(frame[j]==-1 || frame[j]==page[i])
			{
				if(frame[j] != -1)
					hit++;
				flag = 0;
				frame[j] = page[i];
				break;
			}
			if(coun[least] > coun[frame[j]])
				least = frame[j];
		}
		if(flag)
		{
			minTime = 50;
			for(int j=0; j<frameno; j++)
			{
				if(coun[frame[j]]==coun[least] && time[frame[j]]<minTime)
				{
					temp = j;
					minTime = time[frame[j]];
				}
				coun[frame[temp]] = 0;
				frame[temp] = page[i];
			}
		}
		display();
	}
	printf("Page faults in LFU = %d\n", n-hit);
}

void main()
{
	int ch;
	printf("Enter the number of pages\n");
	scanf("%d",&n);

	printf("\nEnter the reference string\n");
	for(int i=0; i<n; i++)
		scanf("%d", &page[i]);

	printf("\nEnter the number of frames\n");
	scanf("%d", &frameno);

	printf("\n1.FIFO \n2.LRU \n3.LFU \n4.Exit\n");
	while(1)
	{
		printf("\nEnter your choice\n");
		scanf("%d", &ch);

		switch(ch)
		{
			case 1: 
				fifo(); 
				break;
			case 2: 
				lru(); 
				break;
			case 3: 
				lfu(); 
				break;
			case 4: 
				exit(0); 
			default: 
				printf("Invalid choice\n");
		}
	}
}

// ------OUTPUT------

// Enter the number of pages
// 12

// Enter the reference string
// 1 2 3 4 5 1 3 1 6 3 2 3

// Enter the number of frames
// 4

// 1.FIFO 
// 2.LRU 
// 3.LFU 
// 4.Exit

// Enter your choice
// 1

// Reference string	Frames
// 1			1	-1	-1	-1	
// 2			1	2	-1	-1	
// 3			1	2	3	-1	
// 4			1	2	3	4	
// 5			5	2	3	4	
// 1			5	1	3	4	
// 3			5	1	3	4	
// 1			5	1	3	4	
// 6			5	1	6	4	
// 3			5	1	6	3	
// 2			2	1	6	3	
// 3			2	1	6	3	
// Page faults in FIFO = 9

// Enter your choice
// 2

// Reference string	Frames
// 1			1	-1	-1	-1	
// 2			1	2	-1	-1	
// 3			1	2	3	-1	
// 4			1	2	3	4	
// 5			5	2	3	4	
// 1			5	1	3	4	
// 3			5	1	3	4	
// 1			5	1	3	4	
// 6			5	1	3	6	
// 3			5	1	3	6	
// 2			2	1	3	6	
// 3			2	1	3	6	
// Page faults in LRU = 8

// Enter your choice
// 3

// Reference string	Frames
// 1			1	-1	-1	-1	
// 2			1	2	-1	-1	
// 3			1	2	3	-1	
// 4			1	2	3	4	
// 5			5	2	3	4	
// 1			1	2	3	4	
// 3			1	2	3	4	
// 1			1	2	3	4	
// 6			6	2	3	4	
// 3			6	2	3	4	
// 2			6	2	3	4	
// 3			6	2	3	4	
// Page faults in LFU = 7

// Enter your choice
// 4