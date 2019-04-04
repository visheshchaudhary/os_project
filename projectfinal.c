#include<stdio.h>
#include<stdbool.h>
void findWaitingTime(int processes[], int n,
			int bt[], int wt[], int quantum)
{
    int i;
	int rem_bt[n];
	for (i = 0 ; i < n ; i++)
		rem_bt[i] = bt[i];
	int t = 0;
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
					t += quantum;
					rem_bt[i] -= quantum;
				}
				else
				{
					t = t + rem_bt[i];
					wt[i] = t - bt[i];
					rem_bt[i] = 0;
				}
			}
		}
		if (done == true)
		break;
	}
}
void findTurnAroundTime(int processes[], int n,
						int bt[], int wt[], int tat[])
{
    int i;
	for (i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}
void findavgTime(int processes[], int n, int bt[],int quantum)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;
	findWaitingTime(processes, n, bt, wt, quantum);
	findTurnAroundTime(processes, n, bt, wt, tat);
	int i;
	printf("Processes       Burst time     Waiting time   Turn around time\n");
	for (i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf("%d \t         %d\t          %d\t          %d\n",processes[i],bt[i],wt[i],tat[i]);
	}
	printf("\nAverage waiting time = %f ",(float)total_wt / (float)n);
	printf("\nAverage turn around time = %f ",(float)total_tat / (float)n);
}
int main()
{
    int i,j;
    printf("Enter the number of processes\n");
    int n1;
    scanf("%d",&n1);
	int processes[n1];
	int burst_time[n1];
	for(i=0;i<n1;i++)
    {
        processes[i]=(i+1);
    }
    for(i=0;i<n1;i++)
    {
        printf("Enter the burst time for process  %d ",i+1);
        scanf("%d",&burst_time[i]);
    }
    for(i=0;i<n1;i++)
    {
        int pos=i;
        for(j=i+1;j<n1;j++)
        {
            if(burst_time[j]<burst_time[pos])
                pos=j;
        }
        int temp;
        temp=burst_time[i];
        burst_time[i]=burst_time[pos];
        burst_time[pos]=temp;
        temp=processes[i];
        processes[i]=processes[pos];
        processes[pos]=temp;
    }
	printf("Enter the time quantum value\n");
	int quantum;
	scanf("%d",&quantum);
	findavgTime(processes, n1, burst_time, quantum);
	return 0;
}
