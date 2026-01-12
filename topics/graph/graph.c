#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Graph *createGraph(int maxVertices)
{
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  graph->maxVertices = maxVertices;
  graph->adj = (int **)malloc(maxVertices * sizeof(int *));
  for (int i = 0; i < maxVertices; i++)
  {
    graph->adj[i] = (int *)calloc(maxVertices, sizeof(int));
  }
  return graph;
}

void printGraph(Graph *graph)
{
  printf("#Graph {\n");
  for (int i = 0; i < graph->maxVertices; i++)
  {
    printf("#\t%d -> ", i);
    for (int j = 0; j < graph->maxVertices; j++)
    {
      if (graph->adj[i][j])
        printf("%d ", j);
    }
    printf("\n");
  }
  printf("#}\n");
}

int addEdge(Graph *graph, int src, int dest)
{
  if (src < 0 || src >= graph->maxVertices || dest < 0 || dest >= graph->maxVertices)
  {
    return 0;
  }
  graph->adj[src][dest] = 1;
  graph->adj[dest][src] = 1;
  return 1;
}

int removeEdge(Graph *graph, int src, int dest)
{
  if (src < 0 || src >= graph->maxVertices || dest < 0 || dest >= graph->maxVertices)
  {
    return 0;
  }
  graph->adj[src][dest] = 0;
  graph->adj[dest][src] = 0;
  return 1;
}

void breadthFirst(Graph *graph, int src)
{
  bool *visited = (bool *)calloc(graph->maxVertices, sizeof(bool));
  int *queue = (int *)malloc(graph->maxVertices * sizeof(int));
  int front = 0, rear = 0;

  visited[src] = true;
  queue[rear++] = src;

  while (front < rear)
  {
    int current = queue[front++];
    printf("%d ", current);

    for (int i = 0; i < graph->maxVertices; i++)
    {
      if (graph->adj[current][i] && !visited[i])
      {
        visited[i] = true;
        queue[rear++] = i;
      }
    }
  }

  free(visited);
  free(queue);
}

void depthFirst(Graph *graph, int src)
{
  bool *visited = (bool *)calloc(graph->maxVertices, sizeof(bool));
  int *stack = (int *)malloc(graph->maxVertices * sizeof(int));
  int top = 0;

  stack[top++] = src;

  while (top > 0)
  {
    int current = stack[--top];

    if (!visited[current])
    {
      visited[current] = true;
      printf("%d ", current);

      for (int i = graph->maxVertices - 1; i >= 0; i--) // neighbor handling
      {
        if (graph->adj[current][i] && !visited[i])
        {
          stack[top++] = i;
        }
      }
    }
  }

  free(visited);
  free(stack);
}

int findShortestPath(Graph *graph, int src, int dest, int *path)
{
  bool *visited = (bool *)calloc(graph->maxVertices, sizeof(bool));
  int *parent = (int *)malloc(graph->maxVertices * sizeof(int));
  int *queue = (int *)malloc(graph->maxVertices * sizeof(int));
  int front = 0, rear = 0;

  for (int i = 0; i < graph->maxVertices; i++)
  {
    parent[i] = -1;
  }

  visited[src] = true;
  queue[rear++] = src;

  while (front < rear)
  {
    int current = queue[front++];

    if (current == dest)
    {
      break;
    }

    for (int i = 0; i < graph->maxVertices; i++)
    {
      if (graph->adj[current][i] && !visited[i])
      {
        visited[i] = true;
        parent[i] = current;
        queue[rear++] = i;
      }
    }
  }

  if (!visited[dest])
  {
    free(visited);
    free(parent);
    free(queue);
    return 0;
  }

  int pathLength = 0;
  int *tempPath = (int *)malloc(graph->maxVertices * sizeof(int));
  int current = dest;

  while (current != -1)
  {
    tempPath[pathLength++] = current;
    current = parent[current];
  }

  for (int i = 0; i < pathLength; i++)
  {
    path[i] = tempPath[pathLength - 1 - i];
  }

  free(visited);
  free(parent);
  free(queue);
  free(tempPath);

  return pathLength - 1;
}

void visualizeMaze(Graph *graph, int rows, int cols)
{
  // Санамж: Төөрдөг байшин зурах логикийг хэрэгжүүлсэн тул үүнийг өөрчилж болохгүй
  int *openings = (int *)calloc(cols, sizeof(int));
  // Дээд хана
  printf("#");
  for (int j = 0; j < cols; j++)
  {
    printf("+----");
    if (j == cols - 1)
    {
      printf("+");
    }
  }
  printf("\n");

  for (int i = 0; i < rows; i++)
  {
    printf("#");
    if (i > 0)
    {
      printf("|");
    }
    else
    {
      printf(" ");
    }
    for (int j = 0; j < cols; j++)
    {
      int cell = i * cols + j;
      if (cell < 10)
      {
        printf(" ");
      }
      printf(" %d ", cell);
      if (j < cols)
      {
        if (graph->adj[cell][cell + 1] || (i == rows - 1 && j == cols - 1))
        {
          printf(" ");
        }
        else
        {
          printf("|");
        }
      }
      openings[j] = 0;
      if (cell + cols < graph->maxVertices)
      {
        openings[j] = graph->adj[cell][cell + cols];
      }
    }
    printf("\n");

    // Доод хана
    printf("#");
    for (int j = 0; j < cols; j++)
    {
      if (openings[j] == 1)
      {
        printf("+    ");
      }
      else
      {
        printf("+----");
      }
      if (j == cols - 1)
      {
        printf("+");
      }
    }
    printf("\n");
  }
  free(openings);
}

void deleteGraph(Graph *graph)
{
  for (int i = 0; i < graph->maxVertices; i++)
    free(graph->adj[i]);
  free(graph->adj);
  free(graph);
}
