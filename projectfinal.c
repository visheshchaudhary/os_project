#include<stdio.h>
#include<stdbool.h>
void findWaitingTime(int p1[], int n,
			int bt[], int wt[], int quantum)
{
	int s=0;
	int seq[s];
    int i;
	int rem_bt[n];
	for (i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];
	int t = 3;
	printf("%2d to %2d     :\t__\n",0,3);
	while (1)
	{
		bool done = true;
		for (i = 0 ; i < n; i++)
		{
			if (rem_bt[i] > 0)
			{
				done = false;
				if (rem_bt[i] > quantum)
				{
					int t1=t;
					t += quantum;
					rem_bt[i] =rem_bt[i]-quantum;
					s=s+1;
					seq[i]=p1[i];
					printf("%2d to %2d     :\tP%d\n",t1,t,seq[i]);
				}
				else
				{
					int t2=t;
					t = t + rem_bt[i];
					wt[i] = t- bt[i];
					rem_bt[i] = 0;
					s=s+1;
					seq[i]=p1[i];
					printf("%2d to %2d     :\tP%d\n",t2,t,seq[i]);
				}
			}
		}
		if (done == true)
		break;
	}	
}
void findTurnAroundTime(int p1[], int n,
						int bt[], int wt[], int tat[])
{
    int i;
	for (i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}
void findavgTime(int p1[], int n, int bt[],int quantum)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;
	findWaitingTime(p1, n, bt, wt, quantum);
	findTurnAroundTime(p1, n, bt, wt, tat);
	int i;
	printf("Order of execution is : \n");
	printf("|  |  |  |");
	for(i=0;i<n;i++)
	printf("P%d |",p1[i]);
	printf("\nProcesses       Burst time     Waiting time   Turn around time\n");
	for (i=0; i<n; i++)
	{
		
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf("%d \t         %d\t          %d\t          %d\n",p1[i],bt[i],wt[i],tat[i]);
	}
	printf("\nAverage waiting time = %f ",(float)total_wt / (float)n);
	printf("\nAverage turn around time = %f ",(float)total_tat / (float)n);
}
int main()
{
    int i,j;
    printf("Enter the number of processes :\n");
    int n1;
    scanf("%d",&n1);
	int p[n1];
	int bt1[n1];
	for(i=0;i<n1;i++)
    {
        p[i]=(i+1);
    }
    for(i=0;i<n1;i++)
    {
        printf("Enter the burst time for P%d ",i+1);
        scanf("%d",&bt1[i]);
    }
    for(i=0;i<n1;i++)
    {
        int pos=i;
        for(j=i+1;j<n1;j++)
        {
            if(bt1[j]<bt1[pos])
                pos=j;
        }
        int temp;
        temp=bt1[i];
        bt1[i]=bt1[pos];
        bt1[pos]=temp;
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
	printf("Enter the time quantum value\n");
	int q;
	scanf("%d",&q);
	findavgTime(p, n1, bt1, q);
	return 0;
}
