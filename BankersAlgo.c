

#include<stdio.h>
#include<stdlib.h>

int n,m,A[10][10],M[10][10],N[10][10],W[1][10],pid,ch;
int a[10],b[10],c[10],kk,kkk;

void accept()
{
	printf("Enter the no of processes\n");
	scanf("%d",&n);

	printf("Enter the no of resources\n");
	scanf("%d",&m);

	printf("\nEnter the allocation matrix\n");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
			scanf("%d", &A[i][j]);
	}

	printf("\nEnter the maximum matrix\n");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<m; j++)
		{
			scanf("%d", &M[i][j]);
			N[i][j] = M[i][j] - A[i][j];
		}
	}

	printf("\nEnter the available array\n");
	for(int j=0; j<m; j++)
		scanf("%d", &W[0][j]);

	printf("\nNeed Matrix:\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			printf("%d ",N[i][j]);
		printf("\n");
	}
}

void res_req(int pid)
{
	int reqmat[1][10];
	int i;
	printf("Enter the request\n");
	for(i=0;i<m;i++)
		scanf("%d",&reqmat[0][i]);

	for(i=0;i<m;i++)
	{
		if(reqmat[0][i]>N[pid][i] || reqmat[0][i]>W[0][i])
		{
			printf("Resource can't be allocated\n");
			exit(0);
		}
	}
	for(i=0;i<m;i++)
	{
		W[0][i]-=reqmat[0][i];
		A[pid][i]+=reqmat[0][i];
		N[pid][i]-=reqmat[0][i];
	}
}

int safety()
{
	int i,j,k,d;
	int F[10],AV[1][10];
	int x=0,pflag=0,flag=0;
	for(i=0;i<n;i++) F[i]=0;
	for(i=0;i<m;i++) AV[0][i]=W[0][i];
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			if(F[i]==0)
			{
				flag=0;
				for(j=0;j<m;j++)
				{
					if(N[i][j]>AV[0][j])
						flag=1;
				}
				if(flag==0&&F[i]==0)
				{
					for(j=0;j<m;j++)
						AV[0][j]+=A[i][j];
					F[i]=1;
					pflag++;
					a[x++]=i;
				}
			}
		}
		if(pflag==n) { d=1; break;}
	}
	if(pflag!=n) d=0;

	pflag=flag=x=0;
	for(i=0;i<n;i++) F[i]=0;
	for(i=0;i<m;i++) AV[0][i]=W[0][i];
	for(k=n-1;k>=0;k--)
	{
		for(i=n-1;i>=0;i--)
		{
			if(F[i]==0)
			{
				flag=0;
				for(j=0;j<m;j++)
				{
					if(N[i][j]>AV[0][j])
						flag=1;
				}
				if(flag==0&&F[i]==0)
				{
					for(j=0;j<m;j++)
						AV[0][j]+=A[i][j];
					F[i]=1;
					pflag++;
					b[x++]=i;
				}
			}
		}
		if(pflag==n) { kk=1; break;}
	}
	if(pflag!=n) kk=0;

	pflag=flag=x=0;
	for(i=0;i<n;i++) F[i]=0;
	for(i=0;i<m;i++) AV[0][i]=W[0][i];
	for(k=n-1;k>=0;k--)
	{
		for(i=n-1;i>=0;i--)
		{
			if(F[i]==0)
			{
				flag=0;
				for(j=0;j<m;j++)
				{
					if(N[i][j]>AV[0][j])
						flag=1;
				}
				if(flag==0&&F[i]==0)
				{
					for(j=0;j<m;j++)
						AV[0][j]+=A[i][j];
					F[i]=1;
					pflag++;
					c[x++]=i;
					break;
				}
			}
		}
		if(pflag==n) { kkk=1; break;}
	}
	if(pflag!=n) kkk=0;

	if(d==1) return 1;
	else return 0;
}

int banker()
{
	int i, j;
	j=safety();
	if(j!=0)
	{
		printf("\nThe system is in safe state\n");
		printf("The safe sequences are:\n");

		for(i=0;i<n-1;i++)
			printf("P%d->",a[i]);
		printf("P%d\n",a[i]);
		if(kk!=0)
		{
			for(i=0;i<n-1;i++)
				printf("P%d->",b[i]);
			printf("P%d\n",b[i]);
		}
		if(kkk!=0)
		{
			for(i=0;i<n-1;i++)
				printf("P%d->",c[i]);
			printf("P%d\n",c[i]);
		}
	}
	else
	{
		printf("\nDeadlock occurs\n");
		return 0;
	}
}

void main()
{
	accept();
	if(banker())
	{
		while(1)
		{
			printf("\nIs there a resource request? (1/0) ");
			scanf("%d",&ch);
			if(ch==1)
			{
				printf("Enter the process id\n");
				scanf("%d",&pid);
				res_req(pid);

				if(!banker()) 
					exit(0);
			}
			else 
				break;
		}
	}
	else 
		exit(0);
}

