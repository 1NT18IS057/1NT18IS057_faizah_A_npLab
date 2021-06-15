#include<stdio.h>
struct table
{
    unsigned cost[20];
    unsigned next_hop[20];
}router[10];
int main()
{
    int costmat[20][20];
    int nodes,i,j,k,count=0;
    printf("\nEnter the number of nodes : ");
    scanf("%d",&nodes);
    printf("\nEnter the cost matrix :\n");
    for(i=0;i<nodes;i++)
    {
        for(j=0;j<nodes;j++)
        {
            scanf("%d",&costmat[i][j]);
            costmat[i][i]=0;
            router[i].cost[j]=costmat[i][j];
            router[i].next_hop[j]=j;
        }
    }
        do
        {
            count=0;
            for(i=0;i<nodes;i++)
            	for(j=0;j<nodes;j++)
            		for(k=0;k<nodes;k++)
                			if(router[i].cost[j]>costmat[i][k]+router[k].cost[j])
                			{
                  			  router[i].cost[j]=router[i].cost[k]+router[k].cost[j];
                   			  router[i].next_hop[j]=k;
                   			  count++;
                			}
        }while(count!=0);
        for(i=0;i<nodes;i++)
        {
            printf("\n\nState value for router %d is\n",i+1);
	  printf("\t\nNode\tVia\tDistance\n");
            for(j=0;j<nodes;j++)
            {
                printf("\t\n%d\t%d\t%d ",j+1,router[i].next_hop[j]+1,router[i].cost[j]);
            }
        }
    printf("\n\n");

	printf("Final matrix:\n");
	for(i=0;i<nodes;i++)
	{
		for(j=0;j<nodes;j++)
		{
			printf("%d\t",router[i].cost[j]);
		}
	printf("\n");
	}

}
