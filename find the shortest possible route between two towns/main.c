//NAME:DOHA HMEID ,ID:1190120 ,SECTION:2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define S 75
#define INF 9999

//structure to hold data from file
typedef struct ed
{
    int start;//from
    int destination;//to
    char name[S];
    int weight;
} edgee;
//array of the data
edgee edges[1000];
int numberOfEgdes = 0;
int numberOfVertices = 0;

int readFile();
void printGraphInfo();
void countVertices();
void addEdge(int ar[numberOfVertices][numberOfVertices],int from, int to,int weight);
void printMatrix(int arr[numberOfVertices][numberOfVertices]);
void fillMatrix(int ar[numberOfVertices][numberOfVertices]);
int* dijikstra(int mat[][numberOfVertices], int numberOfVertices, int startnode,int finishnode);
int dijikstra2(int mat[][numberOfVertices], int numberOfVertices, int startnode,int finishnode);
void printPath(int *a1,int a2,int a3,int a4);

int main()
{
    int number,point1,point2,c=0,ans=0,j=0,m,u=0,totaldis=0;
     m = readFile();
    //printGraphInfo();
    countVertices();
    //2D matrix
    int adjacencyMatrix[numberOfVertices][numberOfVertices];
    //pointer to array to hold path/route
    int *a2r[numberOfVertices];
    int d2r[numberOfVertices];
    int s2r[numberOfVertices];
    int e2r[numberOfVertices];
int was;
    while(1)
    {
        printf("\n--------------------------------------------------------------------------\n");
        printf("Select an option: \n");
        printf("  1.Read the file and load the data\n");
        printf("  2.Enter 2 points to compute the shortest path between them\n");
        printf("  3.Print the route of the shortest distance to a file\n");
        printf("  4.Exit\n");
        if(c==0)
            printf("*******NOTE : YOU MUST READ THE FILE BEFORE PERFORMING ANY OPERATION\n");
        c++;
        printf("--------------------------------------------------------------------------\n");
        scanf("%d",&number);
was= 0;
        switch(number)
        {
        case 1:
            if(m==0)
            {
                printf("can't open the file\n");
                exit(1);
            }
            else if(m==1)
                printf("file opened successfully\n");
            //printGraphInfo();
            // printf("the number of vetices is %d \n",numberOfVertices-1);
            //to initialize the matrix
            for(int i=0; i<numberOfVertices; i++)
            {
                for(int j=0; j<numberOfVertices; j++)
                    adjacencyMatrix[i][j] = 0;
            }
            fillMatrix(adjacencyMatrix);
            //printMatrix(adjacencyMatrix);
            printf("Loading the data is done successfully\n");
            break;

        case 2:
            do
            {
                printf("Enter 2 points to compute the shortest path between them\n");
                if(u==0)
                    printf("Note : the upper limit to the points based on the data in the file you entered is %d\n",numberOfVertices-1);
                scanf("%d%d",&point1,&point2);
                u++;
                if(point1<0 || point2<0)
                {
                    printf("dijikstra method only works with positive numbers , ");
                    printf("please enter positive points\n");
                }

                else if(point1>numberOfVertices-1 || point2>numberOfVertices-1)
                {
                    printf("There is no path from source to destination vertex , ");
                    printf("the upper limit for the vertices in the data from file is %d\n",numberOfVertices-1);
                }

                else if(point1 == point2)
                {
                    printf("Source and destination vertices are same , ");
                    printf("so distance = 0\n");
                }

                else
                {
                    int flag1=0,flag2=0;
                    for(int ii=0; ii<numberOfEgdes+1 ; ii++)
                    {
                        if(point1 == edges[ii].start || point1 == edges[ii].destination)
                        {
                            flag1 = 1;
                        }

                        if(point2 == edges[ii].start || point2 == edges[ii].destination)
                        {
                            flag2 =1;
                        }

                    }
                    if(flag1 ==0 && flag2 ==0)
                    {
                        printf("the points u have entered is not in the data file ,");
                        printf("the distance to get them = infinity (they are not connected to any other node/vertex)\n");
                    }
                    else if(flag1 ==0 || flag2 ==0)
                    {
                        printf("one of the points u have entered is not in the data file ,");
                        printf("the distance to get them = infinity (they are not connected to any other node/vertex)\n");
                    }

                    else
                    {
                        int *r;
                        totaldis = dijikstra2(adjacencyMatrix,numberOfVertices,point1,point2);
                        d2r[j] = totaldis;
                        s2r[j] = point1;
                        e2r[j] = point2;
                        r = dijikstra(adjacencyMatrix,numberOfVertices,point1,point2);
                        a2r[j] = r;
                        printPath(r,s2r[j],e2r[j],d2r[j]);
                        j++;
                    }
                }

                printf("\nif you want to continue enter 1 ,otherwise enter -1\n\n");
                scanf("%d",&ans);

            }
            while(ans != -1);
            printf("\n************BYE!************\n");
            break;

        case 3:
            /*for(int t=0 ; t<j; t++)
            {
                printPath(a2r[t],s2r[t],e2r[t],d2r[t]);
            }*/
            printf("DONE , you can check the file \n");
            break;

        case 4 :
            exit(0);
            break;

        default :
            printf("you entered a wrong number (Invalid number) \n");
        }
    }

    return 0;
}

int readFile()
{
    FILE *in;
    in = fopen("segments.txt","r");
    int xo =0;
    if(in == NULL) //or if(!in)
    {
        xo=0;
        //  printf("can't open the file\n");
        //exit(1);
    }
    else
    {
        xo=1;
        //printf("file opened successfully\n");
        char line[50],*p1,p2[S],p3[S];
        while(fgets ( line, sizeof(line), in ) != NULL )
        {
            // printf(line);
            p1 = strtok(line," ");
            int j=0;

            while(p1 != NULL)
            {
                if( j==0 )
                {
                    edges[numberOfEgdes].start = atoi(p1);
                    // printf("1.%d\n",edges[numberOfEgdes].start);
                    j++;
                }

                else if( j==1 )
                {
                    edges[numberOfEgdes].destination = atoi(p1);
                    // printf("2.%d\n",edges[numberOfEgdes].destination);
                    j++;
                }

                else if( j==2 )
                {
                    strcpy(p2,p1);
                    j++;
                }

                else
                {

                    if(isdigit(p1[0]))
                    {
                        strcpy(edges[numberOfEgdes].name, p2);
                        // printf("3.%s\n",edges[numberOfEgdes].name);
                        edges[numberOfEgdes].weight = atoi(p1);
                        // printf("4.%d\n",edges[numberOfEgdes].weight);
                        j++;
                    }

                    else
                    {
                        strcpy(p3,p1);
                        strcat(p2,"_");
                        strcat(p2,p3);
                        j++;
                    }
                }
                p1 = strtok(NULL," ");
            }
            j=0;
            numberOfEgdes++;
        }
    }
    return xo;
}

void printGraphInfo()
{
    //printf("THERE ARE %d CITIES IN THE  GRAPH\n",numberOfEgdes);
    printf("HERE IS THE GRAPH\n");
    for(int i=0; i<numberOfEgdes ; i++)
    {
        printf("the distance from %d to %d (%s) = %d\n",edges[i].start,edges[i].destination,edges[i].name,edges[i].weight);
    }
}

void countVertices()
{
    int max = edges[0].start;
    for(int i=0 ; i<numberOfEgdes ; i++)
    {
        if(max < edges[i].start)
        {
            max = edges[i].start;
        }

    }

    for(int j=0 ; j<numberOfEgdes ; j++)
    {
        if(max < edges[j].destination)
        {
            max = edges[j].destination;
        }
    }
    numberOfVertices = max +1;
    // printf("the number of vetices is %d \n",numberOfVertices-1);
    // printf("the size of the matrix is %d*%d \n",numberOfVertices,numberOfVertices );
}

void addEdge(int ar[numberOfVertices][numberOfVertices],int from, int to,int weight)
{
    ar[from][to] = weight;
    ar[to][from] = weight;
}

void fillMatrix(int ar[numberOfVertices][numberOfVertices])
{

    for(int i=0 ; i<numberOfEgdes ; i++)
    {
        addEdge(ar,edges[i].start,edges[i].destination,edges[i].weight);
    }
}

void printMatrix(int arr[numberOfVertices][numberOfVertices])
{
    int i, j;
    for(i=0; i<numberOfVertices; i++)
    {
        for(j=0; j<numberOfVertices; j++)
        {
            if(arr[i][j] != 0)
                printf(" %d %d %d \n",i,j, arr[i][j]);
        }
        printf("\n");
    }
}

int* dijikstra(int mat[][numberOfVertices], int numberOfVertices, int startnode,int finishnode)
{

    int cost[numberOfVertices][numberOfVertices];
    int distance[numberOfVertices];
    int pred[numberOfVertices];
    int visited[numberOfVertices];
    int count, mindistance, nextnode;

    for(int i=0; i<numberOfVertices; i++)
    {
        for(int j=0; j<numberOfVertices; j++)
        {
            if( mat[i][j]==0 ) //no edge
                cost[i][j]=INF;
            else
                cost[i][j]=mat[i][j];
        }
    }

    for(int i=0; i<numberOfVertices; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count < numberOfVertices-1)
    {
        mindistance=INF;
        for(int i=0; i<numberOfVertices; i++)
        {
            if(distance[i] < mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        }
        visited[nextnode]=1;
        for(int i=0; i<numberOfVertices; i++)
        {
            if(!visited[i])
                if(mindistance+cost[nextnode][i] < distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
        }
        count++;
    }

    int array[numberOfVertices];
    for(int q=0; q<numberOfVertices; q++)
    {
        array[q] = 0;
    }

    int k=0;
    for(int i=0; i<numberOfVertices; i++)
    {
        if(i!=startnode && i== finishnode)
        {
            printf("\nDistance from %d to %d = %dkm",startnode,i,distance[i]);
            printf("\nPath = %d", i);
            int j=i;
            array[k] = i;
            k++;
            do
            {
                j=pred[j];
                array[k] = j;
                k++;
                printf(" <-%d", j);
            }
            while(j!=startnode);
        }
    }
    printf("\n");
printf("here is the route: ");
    for(int i=numberOfVertices ; i>0 ; i--)
    {
        if(array[i] != 0)
        {

            for(int c=0; c<numberOfEgdes; c++)
            {
                if(edges[c].start == array[i] && edges[c].destination== array[i-1])
                {
                    printf(" <- %s", edges[c].name);
                }
                if(edges[c].start == array[i-1] && edges[c].destination==array[i])
                {
                    printf(" <- %s", edges[c].name);
                }

            }

        }
    }
    printf("\n");
    int *a =array;
    return a;

}

int dijikstra2(int mat[][numberOfVertices], int numberOfVertices, int startnode,int finishnode)
{

    int cost[numberOfVertices][numberOfVertices];
    int distance[numberOfVertices];
    int pred[numberOfVertices];
    int visited[numberOfVertices];
    int count, mindistance, nextnode;

    for(int i=0; i<numberOfVertices; i++)
    {
        for(int j=0; j<numberOfVertices; j++)
        {
            if( mat[i][j]==0 ) //no edge
                cost[i][j]=INF;
            else
                cost[i][j]=mat[i][j];
        }
    }

    for(int i=0; i<numberOfVertices; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count < numberOfVertices-1)
    {
        mindistance=INF;
        for(int i=0; i<numberOfVertices; i++)
        {
            if(distance[i] < mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }
        }
        visited[nextnode]=1;
        for(int i=0; i<numberOfVertices; i++)
        {
            if(!visited[i])
                if(mindistance+cost[nextnode][i] < distance[i])
                {
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
        }
        count++;
    }
    int dis=0;
    for(int i=0; i<numberOfVertices; i++)
    {
        if(i!=startnode && i== finishnode)
        {
            //printf("\nDistance from %d to %d = %dkm",startnode,i,distance[i]);
            dis = distance[i];
        }
    }
    return dis;
}

void printPath(int *ar,int s,int e,int d)
{
    FILE *out;
    out = fopen("route.txt","a");
    fprintf(out,"\nDistance from %d to %d = %dkm\n",s,e,d);
    fprintf(out,"the path is: ");
    for(int i=numberOfVertices-1 ; i>0 ; i--)
    {
        if(ar[i] != 0)
        {
            for(int c=0; c<numberOfEgdes-1; c++)
            {
                if(edges[c].start == ar[i] && edges[c].destination == ar[i-1])
                {
                    fprintf(out," <- %s", edges[c].name);
                }
                if(edges[c].start == ar[i-1] && edges[c].destination == ar[i])
                {
                    fprintf(out," <- %s", edges[c].name);
                }
            }
        }
    }
    fprintf(out,"\n\n");
    fclose(out);
}
