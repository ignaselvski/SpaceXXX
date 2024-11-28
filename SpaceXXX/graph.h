#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <iostream>
#include <string>
#include <time.h>

#define MAXV 100
#define INF INT_MAX

typedef struct way {
    int target;
    int cost;
    struct way* next;
} way;

typedef struct {
    way* header;
} adlist;

typedef struct {
    adlist path[MAXV];
    int paths;
    char name[MAXV][50];
} graph;

// Function Prototypes
graph* newGraph(int paths);
void addWay(graph* A_graph, int begin, int end, int costt);
void wayView(graph* A_graph, int pastWay[], int A_path);
int dkstr(graph* A_graph, int begin, int end, int pastWay[]);
int wayIndex(graph* A_graph, const char* name);
void readCSV(graph* A_graph, const char* fileName);
void printPath(graph* A_graph, const char* name);
void removeNode(graph* A_graph, const char* name);
void dataC(graph* A_graph, int A_path, int flag[]);
void dataMinus(graph* A_graph, int A_path, int flag[]);
void wayFinder(graph* A_graph, int begin, int end);
int connected(graph* A_graph);
void connections(graph* A_graph, const char* name);
short menu();
void remove(graph* A_graph, int past[], int begin, int end);
void restore(graph* A_graph, int past[], int begin, int end, int costx);
void freeGraph(graph* A_graph);
void freeWayList(way* header);

#endif // GRAPH_H