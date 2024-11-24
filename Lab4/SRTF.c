#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#define SORT_BY_ARRIVAL 0 
#define SORT_BY_PID 1 
#define SORT_BY_BURST 2 
#define SORT_BY_START 3 
#define SORT_BY_REMAINING 4

typedef struct{ 
    int iPID; 
    int iArrival, iRemainingTime, iBurst; 
    int iStart, iFinish, iWaiting, iResponse, iTaT; 
} PCB; 
 
void inputProcess(int n, PCB P[]);
 
void printProcess(int n, PCB P[]);
 
void exportGanttChart (int n, PCB P[]);
 
void pushProcess(int *n, PCB P[], PCB Q);
 
void removeProcess(int *n, int index, PCB P[]);
 
int swapProcess(PCB *P, PCB *Q);
 
int partition (PCB P[], int low, int high, int iCriteria);
 
void quickSort(PCB P[], int low, int high, int iCriteria);
 
void calculateAWT(int n, PCB P[]);
 
void calculateATaT(int n, PCB P[]); 

int compareProcess(PCB P, PCB Q, int iCriteria);

int main() 
{ 
    PCB Input[10]; 
    PCB ReadyQueue[10]; 
    PCB TerminatedArray[10]; 
    PCB GanttChart[10];
    srand(time(NULL));
    int iNumberOfProcess = 0; 
    printf("Please input number of Process: "); 
    scanf("%d", &iNumberOfProcess);
    int iRemain = iNumberOfProcess, iReady = 0, iTerminated = 0, iGanttChart = 0; 
 
    inputProcess(iNumberOfProcess, Input); 
    quickSort(Input, 0, iNumberOfProcess - 1, SORT_BY_ARRIVAL); 
    int timePoint = 0; 
 
    while(iTerminated < iNumberOfProcess)
    { 
        if(iReady == 0)
        {
            if(iRemain > 0 && timePoint <= Input[0].iArrival)
                timePoint = Input[0].iArrival;
            pushProcess(&iReady, ReadyQueue, Input[0]);
            removeProcess(&iRemain, 0, Input);
        }
        while(iRemain > 0 && Input[0].iArrival == timePoint)
        {
            pushProcess(&iReady, ReadyQueue, Input[0]);
            removeProcess(&iRemain, 0, Input);
        }
        quickSort(ReadyQueue, 0, iReady - 1, SORT_BY_REMAINING);

        if(iGanttChart == 0 || GanttChart[iGanttChart - 1].iPID != ReadyQueue[0].iPID)
        {
            pushProcess(&iGanttChart, GanttChart, ReadyQueue[0]);
            GanttChart[iGanttChart - 1].iStart = timePoint;
        }
        ReadyQueue[0].iStart = ReadyQueue[0].iStart == -1 ? timePoint : ReadyQueue[0].iStart;

        int timePointPre = timePoint;
        if(iRemain > 0)
        {
            timePoint = Input[0].iArrival < (ReadyQueue[0].iRemainingTime + timePoint) ? Input[0].iArrival : (ReadyQueue[0].iRemainingTime + timePoint);
        }
        else timePoint += ReadyQueue[0].iRemainingTime;
        ReadyQueue[0].iRemainingTime -= (timePoint - timePointPre);

        if(ReadyQueue[0].iRemainingTime == 0)
        {
            ReadyQueue[0].iFinish = timePoint;
            ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
            ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;
            ReadyQueue[0].iWaiting = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival - ReadyQueue[0].iBurst;
            pushProcess(&iTerminated, TerminatedArray, ReadyQueue[0]);
            removeProcess(&iReady, 0, ReadyQueue);
        }

        if(iGanttChart > 0)
            GanttChart[iGanttChart - 1].iFinish = timePoint;
    } 
 
    printf("\n===== SRTF Scheduling =====\n"); 
    printProcess(iTerminated, TerminatedArray);
    exportGanttChart(iGanttChart, GanttChart); 
 
    quickSort(TerminatedArray, 0, iTerminated - 1, SORT_BY_PID); 
 
    calculateAWT(iTerminated, TerminatedArray); 
    calculateATaT(iTerminated, TerminatedArray); 

    return 0; 
}

 
void inputProcess(int n, PCB P[])
{
    for (int i = 0; i < n; i++)
    {
        printf("Process %d\n", i + 1);
        P[i].iArrival = rand() % 21;
        printf("Arrival Time: %d \t", P[i].iArrival);
        P[i].iBurst = rand() % 11 + 2;
        printf("Burst Time: %d\n", P[i].iBurst);
        P[i].iRemainingTime = P[i].iBurst;
        P[i].iPID = i + 1;
        P[i].iStart = -1;
        P[i].iFinish = 0;
        P[i].iWaiting = 0;
        P[i].iResponse = 0;
        P[i].iTaT = 0;
    }
}
 
void printProcess(int n, PCB P[])
{
    printf("------\n");
    printf("PID\tArrival\tBurst\tStart\tFinish\tResponse\tWaiting\tTaT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t\t%d\t%d\n",
               P[i].iPID,
               P[i].iArrival,
               P[i].iBurst,
               P[i].iStart,
               P[i].iFinish,
               P[i].iResponse,
               P[i].iWaiting,
               P[i].iTaT);
    printf("------\n");
}
 
void exportGanttChart (int n, PCB P[])
{
    printf("\nGantt Chart:\n");
    if (P[0].iStart > 0)
        printf("0\t");

    for (int i = 0; i < n - 1; i++)
    {
        printf("%d\t", P[i].iStart);
        if (P[i].iFinish < P[i + 1].iStart)
            printf("%d\t", P[i].iFinish);
    }
    printf("%d\t%d\n", P[n - 1].iStart, P[n - 1].iFinish);

    if (P[0].iStart > 0)
        printf("| IDLE\t");
    for (int i = 0; i < n - 1; i++)
    {
        printf("|  P%d\t", P[i].iPID);
        if (P[i].iFinish < P[i + 1].iStart)
            printf("| IDLE\t");
    }
    printf("|  P%d\t|\t\n", P[n - 1].iPID);

    printf("\n");
}
 
void pushProcess(int *n, PCB P[], PCB Q)
{
    P[*n] = Q;
    (*n)++;
}
 
void removeProcess(int *n, int index, PCB P[])
{
    for(int i = index; i < *n; i++)
    {
        P[i] = P[i + 1];
    }
    (*n) = (*n) - 1;
}
 
int swapProcess(PCB *P, PCB *Q)
{
    PCB temp = *P;
    *P = *Q;
    *Q = temp;
    return 1;
}
 
int partition (PCB P[], int low, int high, int iCriteria)
{
    int i = low - 1;
    for (int j = low; j < high; j++)
        if (compareProcess(P[j], P[high], iCriteria) < 0)
            swapProcess(&P[++i], &P[j]);

    swapProcess(&P[i + 1], &P[high]);

    return i + 1;
}
 
void quickSort(PCB P[], int low, int high, int iCriteria)
{
    if (low < high)
    {
        int pi = partition(P, low, high, iCriteria);
        quickSort(P, low, pi - 1, iCriteria);
        quickSort(P, pi + 1, high, iCriteria);
    }
}
 
void calculateAWT(int n, PCB P[])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += P[i].iWaiting;

    printf("Average Waiting Time: %.2f\n", (float)sum / n);
}
 
void calculateATaT(int n, PCB P[])
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += P[i].iTaT;

    printf("Average Turnaround Time: %.2f\n", (float)sum / n);
}

int compareProcess(PCB P, PCB Q, int iCriteria)
{
    int result = 0;
    switch (iCriteria)
    {
    case SORT_BY_BURST:
        result = P.iBurst - Q.iBurst;
        if(result != 0) 
            break;
    case SORT_BY_REMAINING:
        result = P.iRemainingTime - Q.iRemainingTime;
        if(result != 0)
            break;
    case SORT_BY_ARRIVAL:
        result = P.iArrival - Q.iArrival;
        if(result != 0)
            break;
    case SORT_BY_PID:
        result = P.iPID - Q.iPID;
        break;
    default:
        break;
    }
    return result;
}

