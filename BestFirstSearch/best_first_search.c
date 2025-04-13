#include <stdio.h>
#include <stdlib.h>

struct queue
{
    int size;
    int f, r;
    int *arr;
};

struct queue *createQueue(int size)
{
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->f = q->r = -1;
    q->size = size;
    q->arr = (int *)malloc(q->size * sizeof(int));

    return q;
}

void enqueue(struct queue *q, int data)
{
    if (q->r == q->size - 1)
    {
        printf("Queue full\n");
        return;
    }

    q->arr[++q->r] = data;
}

int dequeue(struct queue *q)
{
    if (q->f == q->r)
    {
        printf("Queue empty\n");
        return -1;
    }

    return q->arr[++q->f];
}

void sortQueue(struct queue *q, int h[])
{
    int index = q->f + 1;
    int minVal = h[q->arr[q->f + 1]];

    for (int i = q->f + 1; i <= q->r; i++)
    {
        if (minVal > h[q->arr[i]])
        {
            minVal = h[q->arr[i]];
            index = i;
        }
    }

    int temp = q->arr[index];
    q->arr[index] = q->arr[q->f + 1];
    q->arr[q->f + 1] = temp;
}

void best_FS(int v, int start, int dest, int G[v][v], int h[])
{
    struct queue *q = createQueue(50);
    int visited[v];
    for (int i = 0; i < v; i++)
    {
        visited[i] = 0;
    }

    enqueue(q, start);
    visited[start] = 1;

    while (q->f != q->r)
    {
        int a = dequeue(q);
        printf("%d ", a);

        for (int i = 0; i < v; i++)
        {
            if (G[a][i] == 1 && visited[i] == 0)
            {
                enqueue(q, i);
                visited[i] = 1;
            }
        }

        if (a == dest)
        {
            break;
        }
        sortQueue(q, h);
    }
}

int main()
{

    int v, e;
    printf("Enter number of node : ");
    scanf("%d", &v);
    printf("Enter number of edges  : ");
    scanf("%d", &e);

    int G[v][v];
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            G[i][j] = 0;
        }
    }
    printf("\n");

    for (int i = 0; i < e; i++)
    {
        int a, b;
        printf("Enter edge (start - end) : ");
        scanf("%d %d", &a, &b);
        G[a][b] = G[b][a] = 1;
    }

    printf("\n");

    int start, dest;
    printf("Start node and destination node : ");
    scanf("%d%d", &start, &dest);

    int h[v];

    printf("Enter heuristic values  \n");
    for (int i = 0; i < v; i++)
    {
        int val;
        printf("Heuristic value for %d -> %d : ", i, dest);
        scanf("%d", &val);

        h[i] = val;
    }

    printf("\n");
    printf("Best first search : \n");
    best_FS(v, start, dest, G, h);

    return 0;
}
