/*		
		EXPERIMENT NO - 1
		CPU SCHEDULING
		Date: 25/11/2021
*/

//------PROGRAM------



#include<stdio.h>
#include <stdlib.h>

int process[10], arrival[10], burst[10], bt[10], prio[10], turnaround[10], waiting[10], ct[10], tq, n;
float avgtt, avgwt;
int readyq[100], front = -1, rear = -1;

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void sort(int k)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-1; j++)
		{
			if(arrival[j] > arrival[j+1])
			{
				swap(&arrival[j], &arrival[j+1]);
				swap(&burst[j], &burst[j+1]);
				swap(&process[j], &process[j+1]);

				if(k == 3)
					swap(&prio[j], &prio[j+1]);
			}
			else if(arrival[j] == arrival[j+1])
			{
				switch(k)
				{
					case 1:
						if(process[j] > process[j + 1])
						{
							swap(&burst[j], &burst[j+1]);
							swap(&process[j], &process[j+1]);
						}
						break;
					case 2:
						if(burst[j] > burst[j+1])
						{
							swap(&burst[j], &burst[j+1]);
							swap(&process[j], &process[j+1]);
						}
						break;
					case 3:
						if(process[j] > process[j + 1])
						{
							swap(&burst[j], &burst[j+1]);
							swap(&process[j], &process[j+1]);
							swap(&prio[j], &prio[j+1]);
						}
						break;
					case 4:
						if(process[j] > process[j + 1])
						{
							swap(&burst[j], &burst[j+1]);
							swap(&process[j], &process[j+1]);
						}
						break;

				}
			}
		}
	}
}

void display(int k)
{
	if(k == 3)
	{
		printf("\nProcess    Arrival Time    Burst Time    Priority    Waiting Time    Turnaround Time\n");
		for(int i=0; i<n; i++)
			printf("   P%i\t\t%i\t\t%i\t\t%i\t\t%i\t\t%i\n", process[i], arrival[i], burst[i], prio[i], waiting[i], turnaround[i]);
	}
	else
	{ 
		printf("\nProcess    Arrival Time    Burst Time    Waiting Time    Turnaround Time\n");
		for(int i=0; i<n; i++)
			printf("   P%i\t\t%i\t\t%i\t\t%i\t\t%i\n", process[i], arrival[i], burst[i], waiting[i], turnaround[i]);
	}

	if(k == 4)
		printf("\nTime quantum = %d", tq);

	printf("\nAverage turnaround time = %.2f\n", avgtt);
	printf("Average waiting time = %.2f\n", avgwt);
}

void avg()
{
	avgtt = avgwt = 0;

	for(int i=0; i<n; i++)
	{
		avgtt += turnaround[i];
		avgwt += waiting[i];
	}

	avgtt /= n;
	avgwt /= n;
}

void fcfs()
{
	int current = 0;
	avgtt = avgwt = 0;

	for(int i=0; i<n; i++)
	{
		if(current >= arrival[i])
		{
			waiting[i] = current - arrival[i];
			current += burst[i];
		}
		else
		{
			current++;
			i--;
		}
	}

	for(int i=0; i<n; i++)
		turnaround[i] = burst[i] + waiting[i];

	avg();
	display(1);
}

void sjf()
{
	int temp, ind, small;

	ct[0] = arrival[0] + burst[0];
	turnaround[0] = ct[0] - arrival[0];
	waiting[0] = turnaround[0] - burst[0];

	for(int i=1; i<n; i++)
	{
		temp = ct[i-1];
		small = burst[i];

		for(int j=i; j<n; j++)
		{
			if(temp >= arrival[j] && small >= burst[j])
			{
				small = burst[j];
				ind = j;
			}
		}

		ct[ind] = temp + burst[ind];
		turnaround[ind] = ct[ind] - arrival[ind];
		waiting[ind] = turnaround[ind] - burst[ind];

		swap(&process[ind], &process[i]);
		swap(&arrival[ind], &arrival[i]);
		swap(&burst[ind], &burst[i]);
		swap(&ct[ind], &ct[i]);
		swap(&waiting[ind], &waiting[i]);
		swap(&turnaround[ind], &turnaround[i]);
	}
	avg();
	display(2);
}

int psort(int a[], int m)
{
	for(int i=0; i<m; i++)
	{
		for(int j=i+1; j<m; j++)
		{
			if(prio[a[j]] < prio[a[i]])
				swap(&a[j], &a[i]);
		}
	}
	return a[0];
}

int remain()
{
	int s = 0;
	for(int i=0; i<n; i++)
		s += bt[i];

	return s;
}

void priority()
{
	int sum=0, current=0, r=0, j=0, temp[20];

	for(int i=0; i<n; i++)
	{
		sum += burst[i];
		waiting[i] = -1;
		bt[i] = burst[i];
	}

	while(remain())
	{
		r = 0;

		for(int k=0; k<n; k++)
		{
			if(current >= arrival[k] && bt[k] > 0)
			{
				temp[r] = k;
				r++;
			}
		}

		if(r > 0)
		{
			if(r == 1)
				j = temp[0];
			else
				j = psort(temp, r);

			waiting[j] = current - arrival[j];
			turnaround[j] = waiting[j] + burst[j];
			current += burst[j];
			bt[j] = 0;
		}
		else
			current++;
	}
	avg();
	display(3);
}

void push(int item)
{
	if(front == -1)
		front = 0;
	rear += 1;
	readyq[rear] = item;
}

int pop()
{
	int item = readyq[front];
	front += 1;
	return item;
}

void roundrobin()
{
	int current = 0, r = 0, first[20], f = 0, t = 0;
	for(int i=0; i<n; i++)
	{
		waiting[i] = -1;
		bt[i] = burst[i];
		first[i] = -1;
	}
	while(remain() > 0)
	{
		for (int k=0; k<n; k++)
		{
			if(current >= arrival[k] && bt[k] > 0 && first[k] == -1)
			{
				push(k);
				first[k] = 0;
				r++;
			}
		}
		if(f == 1)
			push(t);

		if(bt[readyq[front]] <= tq && bt[readyq[front]] > 0 && r > 0)
		{
			current += bt[readyq[front]];
			bt[readyq[front]] = 0;
			turnaround[readyq[front]] = current - arrival[readyq[front]];
			waiting[readyq[front]] = turnaround[readyq[front]] - burst[readyq[front]];

			t = pop();
			r--;
			f = 0;
		}
		else if(bt[readyq[front]] > 0 && r > 0)
		{
			current += tq;
			bt[readyq[front]] -= tq;
			t = pop();
			f = 1;
		}
		else
			current++;
	}

	avg();
	display(4);
}

void main()
{
	int ch;

	while(1)
	{
		printf("\n1.FCFS \n2.SJF \n3.Priority \n4.Round Robin \n5.Exit \n");
		printf("\nEnter your choice\n");
		scanf("%d", &ch);

		if(ch == 5)
			exit(0);

		printf("\nEnter the no of processes\n");
		scanf("%d", &n);

		for(int i=0; i<n; i++)
			process[i] = i+1;

		printf("Enter the arrival time of processes\n");
		for(int i=0; i<n; i++)
			scanf("%d", &arrival[i]);

		printf("Enter the burst time of processes\n");
		for(int i=0; i<n; i++)
			scanf("%d", &burst[i]);

		switch(ch)
		{
			case 1:
				sort(1);
				fcfs();
				break;

			case 2:
				sort(2);
				sjf();
				break;

			case 3:
				printf("Enter the priorities\n");
				for(int i=0; i<n; i++)
					scanf("%d", &prio[i]);

				sort(3);
				priority();
				break;

			case 4:
				sort(4);
				printf("Enter the time quantum\n");
				scanf("%d", &tq);
				roundrobin();
				break;

			case 5:
				exit(0);

			default:
				printf("Invalid choice\n");
		}
	}
}

// ------OUTPUT------

// 1.FCFS 
// 2.SJF 
// 3.Priority 
// 4.Round Robin 
// 5.Exit 

// Enter your choice
// 1

// Enter the no of processes
// 4
// Enter the arrival time of processes
// 0 1 5 6
// Enter the burst time of processes
// 2 2 3 4

// Process    Arrival Time    Burst Time    Waiting Time    Turnaround Time
//    P1			0				2				0				2
//    P2			1				2				1				3
//    P3			5				3				0				3
//    P4			6				4				2				6
// Average turnaround time = 3.50
// Average waiting time = 0.75

// 1.FCFS 
// 2.SJF 
// 3.Priority 
// 4.Round Robin 
// 5.Exit 

// Enter your choice
// 2

// Enter the no of processes
// 4
// Enter the arrival time of processes
// 1 2 3 5
// Enter the burst time of processes
// 3 2 1 2

// Process    Arrival Time    Burst Time    Waiting Time    Turnaround Time
//    P1			1				3				0				3
//    P3			3				1				1				2
//    P4			5				2				0				2
//    P2			2				2				5				7
// Average turnaround time = 3.50
// Average waiting time = 1.50

// 1.FCFS 
// 2.SJF 
// 3.Priority 
// 4.Round Robin 
// 5.Exit 

// Enter your choice
// 3

// Enter the no of processes
// 5     
// Enter the arrival time of processes
// 0 2 2 4 3
// Enter the burst time of processes
// 2 1 8 4 5
// Enter the priorities
// 2 1 4 2 3

// Process    Arrival Time    Burst Time    Priority    Waiting Time    Turnaround Time
//    P1			0				2			2				0				2
//    P2			2				1			1				0				1
//    P3			2				8			4				10				18
//    P5			3				5			3				0				5
//    P4			4				4			2				4				8
// Average turnaround time = 6.80
// Average waiting time = 2.80

// 1.FCFS 
// 2.SJF 
// 3.Priority 
// 4.Round Robin 
// 5.Exit 

// Enter your choice
// 4

// Enter the no of processes
// 5
// Enter the arrival time of processes
// 0 2 2 4 3
// Enter the burst time of processes

// 2 1 8 4 5
// Enter the time quantum
// 3

// Process    Arrival Time    Burst Time    Waiting Time    Turnaround Time
//    P1			0				2				0				2
//    P2			2				1				0				1
//    P3			2				8				10				18
//    P5			3				5				9				14
//    P4			4				4				10				14

// Time quantum = 3
// Average turnaround time = 9.80
// Average waiting time = 5.80

// 1.FCFS 
// 2.SJF 
// 3.Priority 
// 4.Round Robin 
// 5.Exit 

// Enter your choice
// 5

