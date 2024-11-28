# Biblioteca de Grafos

Este projeto implementa uma biblioteca para gerenciamento de rotas entre estações, baseada em grafos. A biblioteca oferece funcionalidades para adicionar, remover e encontrar caminhos entre nós, além de visualizar conexões e carregar dados a partir de arquivos CSV. O grafo é representado como não direcionado e ponderado.

## Funcionalidades

- **Representação do Grafo**: Representação utilizando listas de adjacência.
- **Adicionar e Remover Conexões**: Adiciona ou remove arestas e nós dinamicamente.
- **Busca de Caminhos**: Implementa o algoritmo de Dijkstra para encontrar o menor caminho entre dois nós.
- **Verificação de Conectividade**: Verifica se o grafo está totalmente conectado.
- **Importação de Dados CSV**: Carrega dados do grafo a partir de arquivos CSV.
- **Visualização de Conexões**: Mostra as conexões de uma estação específica.
- **Remoção de Nós e Conexões**: Suporta a exclusão de estações e suas conexões.

---

## Estrutura dos Arquivos

### `Graph.h`
Define as estruturas de dados principais e os protótipos das funções da biblioteca:
- Estrutura `graph`: Representa o grafo, armazenando listas de adjacência, nomes das estações e o número de caminhos.
- Estrutura `way`: Representa uma conexão (aresta) entre dois nós (estações) com um peso.
- Definição de constantes:
  - `MAXV`: Número máximo de nós no grafo.
  - `INF`: Representa o infinito, usado no cálculo de menores caminhos.

### `Graph.cpp`
Contém as implementações das funções definidas em `Graph.h`.  
Principais funções:
- **`newGraph`**: Cria um novo grafo vazio.
- **`addWay`**: Adiciona uma conexão entre dois nós com um peso específico.
- **`dkstr`**: Implementa o algoritmo de Dijkstra para encontrar o menor caminho.
- **`wayFinder`**: Busca caminhos alternativos entre duas estações.
- **`connected`**: Verifica se o grafo está conectado.
- **`removeNode`**: Remove uma estação e todas as suas conexões.
- **`readCSV`**: Lê dados de um arquivo CSV e popula o grafo.
- **`freeGraph` e `freeWayList`**: Gerenciam a liberação de memória.

### `Source.cpp`
Arquivo principal para execução do programa.  
Funcionalidades:
1. Criação de um grafo vazio.
2. Carregamento de dados de um arquivo CSV (`rotas.csv`).
3. Exibição de um menu interativo:
   - **Opção 1**: Encontrar um caminho entre duas estações.
   - **Opção 2**: Visualizar conexões de uma estação específica.
   - **Opção 0**: Encerrar o programa.

---

## Como Utilizar

1. **Pré-requisitos**:
   - Compilador C++ compatível com C++11 ou superior.
   - Biblioteca padrão de C++ e suporte a arquivos.

2. **Compilação**:
   Compile os arquivos `Graph.cpp` e `Source.cpp`:
   ```bash
   g++ -o main Source.cpp Graph.cpp
