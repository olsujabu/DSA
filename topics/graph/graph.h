#ifndef GRAPH_H
#define GRAPH_H

typedef struct Graph {
  int **adj; // Хөршийн матриц, 0 бол холбосон ирмэг байхгүй, 1 бол ирмэгтэй
  int maxVertices; // Графын хэмжээ буюу нийт оройн тоо
} Graph;

/**
 * Шинэ граф үүсгэх
 * maxVertices - графт байж болох оройн тоо, adj матрицыг энэ хэмжээгээр үүсгэнэ
 * Үүссэн графын заагчийг буцаана
 */
Graph *createGraph(int maxVertices);

/**
 * Графын оройг хөрш оройн хамт жагсаан хэвлэх
 */
void printGraph(Graph *graph);

/**
 * src <-> dest хооронд ирмэг нэмэх
 * амжилттай бол 1, үгүй бол 0-г буцаана
 */
int addEdge(Graph *graph, int src, int dest);

/**
 * src <-> dest хооронд ирмэг устгах
 * амжилттай бол 1, үгүй бол 0-г буцаана
 */
int removeEdge(Graph *graph, int src, int dest);

/**
 * Өгөгдсөн src оройгоос Breadth-First (BF) traversal хийх
 */
void breadthFirst(Graph *graph, int src);

/**
 * Өгөгдсөн src оройгоос Depth-First (DF) traversal хийх
 */
void depthFirst(Graph *graph, int src);

/**
 * src -> dest хооронд байж болох хамгийн богино замыг олох
 * path 1 хэмжээст массивт замын оройг хадгална (гаралт), анхны утгыг -1 гэж
 * авна жишээ нь 2->5 орой хүртэлх богино замыг олох бол оролт нь [-1, -1, -1,
 * -1, -1] -> үр дүн нь [2, 3, 5, -1, -1] богино замын уртыг буцаана
 */
int findShortestPath(Graph *graph, int src, int dest, int *path);

/**
 * Төөрдөг байшинг дүрсэлж үзэх
 */
void visualizeMaze(Graph *graph, int rows, int cols);

/**
 * Графыг устгаж, санах ой чөлөөлөх
 */
void deleteGraph(Graph *graph);

#endif // GRAPH_H
