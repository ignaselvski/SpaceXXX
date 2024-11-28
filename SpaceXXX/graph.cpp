#include "graph.h"

graph* newGraph(int paths) {
    graph* A_graph = (graph*)malloc(sizeof(graph));
    if (A_graph == NULL) {
        std::cerr << "Memory allocation failed for graph!" << std::endl;
        exit(1);
    }
    A_graph->paths = 0;

    for (int c = 0; c < paths; c++) {
        A_graph->path[c].header = nullptr;
        strcpy_s(A_graph->name[c], "");
    }
    return A_graph;
}

void freeWayList(way* header) {
    while (header != NULL) {
        way* temp = header;
        header = header->next;
        free(temp);
    }
}

void freeGraph(graph* A_graph) {
    if (A_graph == NULL) return;

    // Free each path's way list
    for (int i = 0; i < A_graph->paths; i++) {
        freeWayList(A_graph->path[i].header);
    }

    // Free the graph structure itself
    free(A_graph);
}

void addWay(graph* A_graph, int begin, int end, int costt) {
    if (begin < 0 || end < 0 || begin >= MAXV || end >= MAXV) {
        return;
    }

    // Check if way already exists
    way* now = A_graph->path[begin].header;
    while (now != NULL) {
        if (now->target == end) {
            return;
        }
        now = now->next;
    }

    // Add way to begin node
    way* newW = (way*)malloc(sizeof(way));
    if (newW == NULL) {
        std::cerr << "Memory allocation failed for way!" << std::endl;
        exit(1);
    }
    newW->target = end;
    newW->cost = costt;
    newW->next = A_graph->path[begin].header;
    A_graph->path[begin].header = newW;

    // Add symmetric way (undirected graph)
    now = A_graph->path[end].header;
    while (now != NULL) {
        if (now->target == begin) {
            return;
        }
        now = now->next;
    }

    newW = (way*)malloc(sizeof(way));
    if (newW == NULL) {
        std::cerr << "Memory allocation failed for way!" << std::endl;
        exit(1);
    }
    newW->target = begin;
    newW->cost = costt;
    newW->next = A_graph->path[end].header;
    A_graph->path[end].header = newW;
}

void wayView(graph* A_graph, int pastWay[], int A_path) {
    if (pastWay[A_path] == -1) {
        std::wcout << "\n\t" << A_graph->name[A_path] << std::endl;
        return;
    }
    wayView(A_graph, pastWay, pastWay[A_path]);
    std::wcout << "\n\t" << A_graph->name[A_path] << std::endl;
}

int dkstr(graph* A_graph, int begin, int end, int pastWay[]) {
    int size[MAXV] = { 0 }, flag[MAXV] = { 0 };

    // Ensure that A_graph->paths is valid
    if (A_graph->paths <= 0) {
        return INF; // Or handle the error appropriately
    }

    for (int c = 0; c < A_graph->paths; c++) {
        size[c] = INF;
        pastWay[c] = -1;
    }
    size[begin] = 0;

    for (int c = 0; c < A_graph->paths; c++) {
        int x = -1;
        for (int c1 = 0; c1 < A_graph->paths; c1++) {
            if (!flag[c1] && (x == -1 || size[c1] < size[x])) {
                x = c1;
            }
        }

        if (x == -1 || size[x] == INF) {
            break;
        }

        flag[x] = 1;

        way* now = A_graph->path[x].header;
        while (now != NULL) {
            int aEnd = now->target;
            int costx = now->cost;
            if (!flag[aEnd] && size[x] + costx < size[aEnd]) {
                size[aEnd] = size[x] + costx;
                pastWay[aEnd] = x;
            }
            now = now->next;
        }
    }

    return size[end];
}

int wayIndex(graph* A_graph, const char* name) {
    for (int c = 0; c < A_graph->paths; c++) {
        if (strcmp(A_graph->name[c], name) == 0) {
            return c;
        }
    }
    return -1;
}

void readCSV(graph* A_graph, const char* fileName) {
    FILE* file = nullptr;

    // Open the file using fopen_s
    errno_t err = fopen_s(&file, fileName, "r");
    if (err != 0 || file == nullptr) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    char fullLine[256];
    while (fgets(fullLine, sizeof(fullLine), file)) {
        char nameOne[50];
        int indexOne, indexZero, costx;
        char* context = nullptr;
        char* code = strtok_s(fullLine, ",", &context);
        strcpy_s(nameOne, code);

        indexOne = wayIndex(A_graph, nameOne);
        if (indexOne == -1 && A_graph->paths < MAXV) {
            indexOne = A_graph->paths;
            strcpy_s(A_graph->name[A_graph->paths++], nameOne);
        }
        while ((code = strtok_s(nullptr, ",", &context)) != NULL) {
            char nameZero[50];
            strcpy_s(nameZero, code);
            code = strtok_s(nullptr, ",", &context);
            int fullCost = atoi(code);

            if (fullCost == 1) {
                costx = 1;
            }
            else if (fullCost == 6) {
                costx = 6;
            }
            else if (fullCost == 3) {
                costx = 3;
            }
            else {
                continue;
            }
            indexZero = wayIndex(A_graph, nameZero);
            if (indexZero == -1 && A_graph->paths < MAXV) {
                indexZero = A_graph->paths;
                strcpy_s(A_graph->name[A_graph->paths++], nameZero);
            }
            if (indexOne != -1 && indexZero != -1) {
                addWay(A_graph, indexOne, indexZero, costx);
            }
        }
    }
    fclose(file);
}

void printPath(graph* A_graph, const char* name) {
    for (int c = 0; c < A_graph->paths; c++) {
        if (strcmp(A_graph->name[c], name) == 0) {
            std::wcout << name << " tem conexão com: ";
            way* wayOne = A_graph->path[c].header;
            while (wayOne != NULL) {
                std::wcout << A_graph->name[wayOne->target]
                    << " com peso de: " << wayOne->cost << std::endl;
                wayOne = wayOne->next;
            }
            return;
        }
    }
    std::wcout << "\n\t Estação não encontrada.\n" << std::endl;
}

void remove(graph* A_graph, int past[], int begin, int end) {
    int now = end;
    while (now != begin) {
        int last = past[now];
        way** wayP = &A_graph->path[last].header;
        while (*wayP != NULL) {
            if ((*wayP)->target == now) {
                way* temp = *wayP;
                *wayP = (*wayP)->next;
                free(temp);
                break;
            }
            wayP = &(*wayP)->next;
        }
        now = last;
    }
}

// Restore a path between nodes
void restore(graph* A_graph, int past[], int begin, int end, int costx) {
    int now = end;
    while (now != begin) {
        int last = past[now];
        addWay(A_graph, last, now, costx);
        now = last;
    }
}

// Remove a specific node from the graph
void removeNode(graph* A_graph, const char* name) {
    int nodeIndex = wayIndex(A_graph, name);
    if (nodeIndex == -1) {
        system("CLS");
        std::wcout << "\n\t Estação não encontrada." << std::endl;
        return;
    }

    // Remove connections to this node from other nodes
    for (int c = 0; c < A_graph->paths; c++) {
        way** wayP = &A_graph->path[c].header;
        while (*wayP != NULL) {
            if ((*wayP)->target == nodeIndex) {
                way* temp = *wayP;
                *wayP = (*wayP)->next;
                free(temp);
            }
            else {
                wayP = &(*wayP)->next;
            }
        }
    }

    // Free the node's own connections
    way* wayOne = A_graph->path[nodeIndex].header;
    while (wayOne != NULL) {
        way* temp = wayOne;
        wayOne = wayOne->next;
        free(temp);
    }
    A_graph->path[nodeIndex].header = NULL;

    // Shift remaining nodes
    for (int c = nodeIndex; c < A_graph->paths - 1; c++) {
        strcpy_s(A_graph->name[c], A_graph->name[c + 1]);
        A_graph->path[c] = A_graph->path[c + 1];
    }
    A_graph->paths--;
    system("CLS");
    std::wcout << "\n\t A estação :" << name << " foi removida com sucesso.\n\t" << std::endl;
}

// Depth-first search to mark connected nodes (forward traversal)
void dataC(graph* A_graph, int A_path, int flag[]) {
    flag[A_path] = 1;
    way* wayOne = A_graph->path[A_path].header;
    while (wayOne != NULL) {
        if (!flag[wayOne->target]) {
            dataC(A_graph, wayOne->target, flag);
        }
        wayOne = wayOne->next;
    }
}

// Depth-first search to mark connected nodes (reverse traversal)
void dataMinus(graph* A_graph, int A_path, int flag[]) {
    flag[A_path] = 1;
    way* wayOne = A_graph->path[A_path].header;
    while (wayOne != NULL) {
        if (!flag[wayOne->target]) {
            dataMinus(A_graph, wayOne->target, flag);
        }
        wayOne = wayOne->next;
    }
}

// Find alternative paths between two nodes
void wayFinder(graph* A_graph, int begin, int end) {
    int past[MAXV];
    int mainWay = dkstr(A_graph, begin, end, past);

    if (mainWay != INF) {
        system("CLS");
        std::wcout << "\n\t Caminho principal:\n\t";
        wayView(A_graph, past, end);
        std::wcout << "\n\t Custo da viagem: " << mainWay << std::endl;

        remove(A_graph, past, begin, end);

        for (int c = 0; c < 10; c++) {
            int altWay = dkstr(A_graph, begin, end, past);
            if (altWay != INF) {
                std::wcout << "\n\t Outro caminho encontrado :" << std::endl;
                wayView(A_graph, past, end);
                std::wcout << "\n\t Custo Total: " << altWay << std::endl;
                remove(A_graph, past, begin, end);
            }
        }
    }
    else {
        std::wcout << "\n\t Não foi possível encontrar caminhos entre as estações: \n\t"
            << A_graph->name[begin] << " e " << A_graph->name[end] << std::endl;
    }
    readCSV(A_graph, "rotas.csv");
}

// Check if the graph is fully connected
int connected(graph* A_graph) {
    int flag[MAXV] = { 0 };

    dataC(A_graph, 0, flag);

    for (int c = 0; c < A_graph->paths; c++) {
        if (flag[c] == 0) {
            return 0;
        }
    }
    graph* B_graph = newGraph(MAXV);
    for (int c = 0; c < A_graph->paths; c++) {
        way* wayOne = A_graph->path[c].header;
        while (wayOne != NULL) {
            addWay(B_graph, wayOne->target, c, wayOne->cost);
            wayOne = wayOne->next;
        }
    }
    memset(flag, 0, sizeof(flag));
    dataMinus(B_graph, 0, flag);

    for (int c = 0; c < A_graph->paths; c++) {
        if (flag[c] == 0) {
            return 0;
        }
    }
    return 1;
}

// Show connections for a specific node
void connections(graph* A_graph, const char* name) {
    for (int c = 0; c < A_graph->paths; c++) {
        if (strcmp(A_graph->name[c], name) == 0) {
            system("CLS");
            std::wcout << "\n\t A estação " << name << " está conectada a: ";
            way* wayOne = A_graph->path[c].header;
            while (wayOne != NULL) {
                std::wcout << A_graph->name[wayOne->target]
                    << " Peso de: " << wayOne->cost << std::endl;
                wayOne = wayOne->next;
            }
            return;
        }
    }
    std::wcout << " \n\t Não encontrada." << std::endl;
    system("PAUSE");
    return;
}

// Display menu options
short menu() {
    short a;
    std::wcout << "________________________________________________________________________________" << std::endl;
    std::wcout << "\n\t 1 - Encontrar um caminho \n" << std::endl;
    std::wcout << "\n\t 2 - Mostrar conexões de uma estação \n" << std::endl;
    std::wcout << "\n\t 0 - Sair." << std::endl;
    std::cin >> a;
    return a;
}
